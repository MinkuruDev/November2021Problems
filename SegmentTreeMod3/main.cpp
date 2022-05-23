#include <bits/stdc++.h>
#define vti vector<int>
#define repeat(i,a,b) for(int i = a; i<b; i++)

using namespace std;

class Node{
    public:
        int surplus0, surplus1, surplus2;

        Node(){
            surplus0 = 1;
            surplus1 = 0;
            surplus2 = 0;
        }

        Node(const Node &other){
            surplus0 = other.surplus0;
            surplus1 = other.surplus1;
            surplus2 = other.surplus2;
        }

        Node(int s0, int s1, int s2){
            surplus0 = s0;
            surplus1 = s1;
            surplus2 = s2;
        }

        Node operator+(const int &i){
            int sur = i%3;
            if(sur == 0) return *this;

            Node result(0,0,0);

            if(sur == 1){
                result.surplus0 = surplus2;
                result.surplus1 = surplus0;
                result.surplus2 = surplus1;
            }else{
                result.surplus0 = surplus1;
                result.surplus1 = surplus2;
                result.surplus2 = surplus0;
            }

            return result;
        }

        Node operator+(const Node &other){
            Node result(0,0,0);

            result.surplus0 = surplus0 + other.surplus0;
            result.surplus1 = surplus1 + other.surplus1;
            result.surplus2 = surplus2 + other.surplus2;

            return result;
        }


};

class SegmentTree{
    private:
        static const int MAX_SIZE = 5000;
        Node ST[MAX_SIZE*4];
        int lazy[MAX_SIZE*4];
        vti buildArr;
        int sz;
        void build(int id, int low, int high){
            if(low == high){
                ST[id] = Node(1,0,0);
                return;
            }

            int mid = (low + high) >> 1;
            int id2 = id << 1;
            build(id2, low, mid);
            build(id2+1, mid+1, high);

            // ST[id] = max(ST[id2], ST[id2+1]);
            ST[id] = ST[id2] + ST[id2+1];
        }

    public:
        SegmentTree(){
            sz = MAX_SIZE;
        }

        SegmentTree(int sz){
            this->sz = sz;
        }

        SegmentTree(vti initArr){
            sz = initArr.size() - 1;
            buildArr = initArr;

            build(1,1,sz);
        }

        void build(){
            build(1,1,sz);
        }

        void update(int id, int low, int high, int index, int value){
            // classic update
            if(index<low || index>high) return;

            if(low == high){
                // ST[id] = value;
                // ST[id] += value;
                return;
            }

            int mid = ((low + high) >> 1);
            int id2 = id << 1;
            update(id2, low, mid, index, value);
            update(id2+1, mid+1, high, index, value);

            ST[id] = ST[id2] + ST[id2+1];
            // ST[id] = max(ST[id2], ST[id2+1]);
        }

        /*void down(int id){
            if(lazy[id] == 0) return;

            int temp = lazy[id];
            lazy[id] = 0;
            int id2 = id << 1;

            lazy[id2] += temp;
            ST[id2] += temp;

            lazy[id2+1] += temp;
            ST[id2+1] += temp;
        }*/

        void updateLazy(int id, int low, int high, int left, int right, int value){
            if(low > right || high < left) return;

            if(low >= left && high <=right){
                ST[id] = ST[id] + value;
                lazy[id] += value;
                return;
            }

            // down(id);

            int mid = ((low + high) >> 1);
            int id2 = id << 1;
            updateLazy(id2, low, mid, left, right, value);
            updateLazy(id2+1, mid+1, high, left, right, value);

            /// down
            // ST[id] = max(ST[id2], ST[id2+1]);
            // ST[id] = SI[id2] + ST[id2+1];

            /// not down
            // ST[id] = max(ST[id2], ST[id2+1]) + lazy[id];
            ST[id] = ST[id2] + ST[id2+1] + lazy[id];
        }

        Node get(int id, int low, int high, int left, int right){
            if(low > right || high < left) return Node(0,0,0); // for sum or max of positive int
            // if(low > right || high < left) return -(int)INFINITY; // for max only

            if(low >= left && high <=right){
                return ST[id];
            }

            // down(id)

            int mid = ((low + high) >> 1);
            int id2 = id << 1;

            /// down
            // return max(get(id2, low, mid, left, right),
            //            get(id2+1, mid+1, high, left, right));
            // return get(id2, low, mid, left, right) + get(id2+1, mid+1, high, left, right);

            /// not down
            // return max(get(id2, low, mid, left, right),
               //         get(id2+1, mid+1, high, left, right)) + lazy[id];
            return get(id2, low, mid, left, right) + get(id2+1, mid+1, high, left, right) + lazy[id];
        }

        void print(int id, int low, int high){
            if(low == high){
                printf("%d %d %d     ", ST[id].surplus0, ST[id].surplus1, ST[id].surplus2);
                return;
            }

            int mid = ((low + high) >> 1);
            int id2 = id << 1;

            print(id2, low, mid);
            print(id2+1, mid+1, high);
        }

};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n,q;
    cin >> n >> q;
    SegmentTree st(n);
    st.build();
    //st.print(1,1,n); cout << endl;
    // st.updateLazy(1,1,n,1,n,3);
    int t,l,r;

    while(q--){
        cin >> t >> l >> r;
        l++;r++;
        if(t==0){
            st.updateLazy(1,1,n,l,r,1);
            //st.print(1,1,n); cout << endl;
        }else{
            cout << st.get(1,1,n,l,r).surplus0 << endl;
            //st.print(1,1,n); cout << endl;
        }
    }

    return 0;
}

