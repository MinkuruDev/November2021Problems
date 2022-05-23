#include <bits/stdc++.h>
#define MAX 10000
#define vti vector<int>
#define repeat(i,a,b) for(int i = a; i<b; i++)

using namespace std;

class Node{
    public:
    int primeAtom[8];

    Node(){}

    Node operator+(const Node other){
        Node result;
        repeat(i,1,8){
            result.primeAtom[i] = primeAtom[i] + other.primeAtom[i];
        }

        return result;
    }
};

int checkPrime(int n){
    int s = (int) sqrt(n);
    repeat(i,2,s+1){
        if(n%i==0) return i;
    }

    return 1;
}

int getPrimeAtom(int n){
    int cnt = 0;
    while(true){
        int p = checkPrime(n);
        if(p<2){
            return ++cnt;
        }

        while(n%p==0) n/=p;
        cnt++;
        if(p>n) break;
    }
    return cnt;
}

class SegmentTree{
    private:
        static const int MAX_SIZE = 10000;
        Node ST[MAX_SIZE*4];
        vti buildArr;
        int sz;

        void build(int id, int low, int high){
            if(low == high){
                ST[id].primeAtom[buildArr[low]] = 1;
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

        int get(int id, int low, int high, int left, int right, int k){
            if(low > right || high < left) return 0; // for sum or max of positive int
            // if(low > right || high < left) return -(int)INFINITY; // for max only

            if(low >= left && high <=right){
                return ST[id].primeAtom[k];
            }

            // down(id)

            int mid = ((low + high) >> 1);
            int id2 = id << 1;

            /// down
            // return max(get(id2, low, mid, left, right),
            //            get(id2+1, mid+1, high, left, right));
            return get(id2, low, mid, left, right, k) + get(id2+1, mid+1, high, left, right, k);

            /// not down
            // return max(get(id2, low, mid, left, right),
               //         get(id2+1, mid+1, high, left, right)) + lazy[id];
            // return ST[id] + (low-high+1) * lazy[id]
        }

};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vti a(MAX + 1);
    repeat(i,2,MAX + 1){
        a[i] = getPrimeAtom(i);
        //cout << getPrimeAtom(i) << " ";
    }
    //cout << "done";

    SegmentTree st(a);
    int q,l,r,k;
    cin >> q;
    while(q--){
        cin >> l >> r >> k;
        cout << st.get(1,1,MAX,l,r,k) << endl;
    }

    return 0;
}

