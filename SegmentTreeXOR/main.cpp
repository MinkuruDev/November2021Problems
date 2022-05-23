#include <bits/stdc++.h>
#define vti vector<int>
#define repeat(i,a,b) for(int i = a; i<b; i++)

using namespace std;

class SegmentTree{
    private:
        static const int MAX_SIZE = 50000;
        int ST[MAX_SIZE*4], lazy[MAX_SIZE*4];
        vti buildArr;
        int sz;
        void build(int id, int low, int high){
            if(low == high){
                ST[id] = buildArr[low];
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

        void update(int id, int low, int high, int index, int value){
            // classic update
            if(index<low || index>high) return;

            if(low == high){
                ST[id] = value;
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

        void down(int id, int low, int high){
            if(lazy[id] == 0) return;

            int temp = lazy[id]; // 1 in this case
            lazy[id] = 0;
            int id2 = id << 1;
            int mid = ((low + high) >> 1);

            lazy[id2] ^= temp;
            //if(lazy[id2])
            ST[id2] = (mid - low + 1) - ST[id2];

            lazy[id2+1] ^= temp;
            //if(lazy[id2+1])
            ST[id2+1] = (high - mid) - ST[id2+1];
        }

        void updateLazy(int id, int low, int high, int left, int right, int value){
            if(low > right || high < left) return;

            if(low == high){
                ST[id] ^= value;
                lazy[id] ^= value;
                return;
            }

            if(low >= left && high <=right){
                lazy[id] ^= value;
                // if(lazy[id])
                ST[id] = (high - low + 1) - ST[id];
                return;
            }

            down(id, low, high);

            int mid = ((low + high) >> 1);
            int id2 = id << 1;
            updateLazy(id2, low, mid, left, right, value);
            updateLazy(id2+1, mid+1, high, left, right, value);

            /// down
            // ST[id] = max(ST[id2], ST[id2+1]);
            ST[id] = ST[id2] + ST[id2+1];

            /// not down
            // ST[id] = max(ST[id2], ST[id2+1]) + lazy[id];
            // st[id] += (low-high+1) * lazy[id];
            // if(lazy[id])
               // ST[id] = (right - left + 1) - ST[id];
        }

        int get(int id, int low, int high, int left, int right){
            if(low > right || high < left) return 0; // for sum or max of positive int
            // if(low > right || high < left) return -(int)INFINITY; // for max only

            if(low >= left && high <=right){
                return ST[id];
            }

            down(id, low, high);

            int mid = ((low + high) >> 1);
            int id2 = id << 1;

            /// down
            // return max(get(id2, low, mid, left, right),
            //            get(id2+1, mid+1, high, left, right));
            return get(id2, low, mid, left, right) + get(id2+1, mid+1, high, left, right);

            /// not down
            // return max(get(id2, low, mid, left, right),
               //         get(id2+1, mid+1, high, left, right)) + lazy[id];
            //return ST[id] + (low-high+1) * lazy[id]
        }

        void print(int id, int low, int high){
            if(low == high){
                cout << ST[id] << " ";
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
    //cin.tie(NULL);
    //cout.tie(NULL);

    int n,q;
    cin >> n >> q;
    SegmentTree st(n);
    int t,l,r;
    repeat(i,0,q){
        cin >> t >> l >> r;

        if(t==0){
            st.updateLazy(1,1,n,l,r,1);
        }else{
            cout << st.get(1,1,n,l,r) << endl;
        }
        //st.print(1,1,n);
        //cout << endl;
    }

    return 0;
}

