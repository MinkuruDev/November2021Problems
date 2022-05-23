#include <bits/stdc++.h>
#define vti vector<int>
#define repeat(i,a,b) for(int i = a; i<b; i++)

using namespace std;

class SegmentTree{
    private:
        static const int MAX_SIZE = 5000;
        vti ST[MAX_SIZE*4];
        int lazy[MAX_SIZE*4];
        vti buildArr;
        int sz;

        vti mergeVector(vti vti1, vti vti2){
            vti result;

            auto itr1 = vti1.begin();
            auto itr2 = vti2.begin();
            auto end1 = vti1.end();
            auto end2 = vti2.end();

            while(itr1 < end1 && itr2 < end2){
                if(*itr1 < *itr2){
                    result.push_back(*itr1);
                    itr1++;
                }else{
                    result.push_back(*itr2);
                    itr2++;
                }
            }

            while(itr1 < end1){
                result.push_back(*itr1);
                itr1++;
            }
            while(itr2 < end2){
                result.push_back(*itr2);
                itr2++;
            }

            return result;
        }

        void build(int id, int low, int high){
            if(low == high){
                ST[id].push_back(buildArr[low]);
                return;
            }

            int mid = (low + high) >> 1;
            int id2 = id << 1;
            build(id2, low, mid);
            build(id2+1, mid+1, high);

            // ST[id] = max(ST[id2], ST[id2+1]);
            //merge(ST[id2].begin(), ST[id2].end(), ST[id2+1].begin(), ST[id2+1].end(), ST[id].begin());
            ST[id] = mergeVector(ST[id2], ST[id2+1]);
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


        int get(int id, int low, int high, int left, int right, int value){
            if(low > right || high < left) return 0; // for sum or max of positive int
            // if(low > right || high < left) return -(int)INFINITY; // for max only

            if(low >= left && high <=right){
                return ST[id].size() - (upper_bound(ST[id].begin(), ST[id].end(), value) - ST[id].begin());
            }

            // down(id)

            int mid = ((low + high) >> 1);
            int id2 = id << 1;

            /// down
            // return max(get(id2, low, mid, left, right),
            //            get(id2+1, mid+1, high, left, right));
            return get(id2, low, mid, left, right, value) + get(id2+1, mid+1, high, left, right, value);

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

    int n,q;
    cin >> n;
    vti a(n+1);
    a[0] = 0;
    repeat(i,0,n){
        cin >> a[i+1];
    }
    SegmentTree st(a);
    int l,r,v;

    cin >> q;
    while(q--){
        cin >> l >> r >> v;
        cout << st.get(1,1,n,l,r,v) << endl;
    }

    return 0;
}

