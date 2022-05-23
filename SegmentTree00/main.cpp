#include <bits/stdc++.h>
#define MAX 50000

using namespace std;

class SegmentTree{
    public:
    int ST[MAX * 4 + 1];

    SegmentTree(){
        for(int i = 0; i<=MAX * 4; i++){
            ST[i] = 0;
        }
    };

    SegmentTree(int size){
        for(int i = 0; i<size * 4 + 1; i++){
            ST[i] = 0;
        }
    };

    ~SegmentTree(){};

    void update(int id, int low, int high, int index, int value){
        if(index < low || index > high) return;

        if(low == high){
            ST[id] += value;
            return;
        }

        int mid = low + (high - low) / 2;
        update(id*2, low, mid, index, value);
        update(id*2 + 1, mid + 1, high, index, value);

        ST[id] = max(ST[id*2], ST[id*2 + 1]);
    }

    void updateMany(int id, int low, int high, int left, int right, int value){
        if(right < low || left > high) return;

        if(low == high){
            ST[id] += value;
            return;
        }

        int mid = low + (high - low) / 2;
        updateMany(id*2, low, mid, left, right, value);
        updateMany(id*2+1, mid+1, high, left, right, value);

        ST[id] = max(ST[id*2], ST[id*2 + 1]);
    }

    int findMax(int id, int low, int high, int left, int right){
        if(right < low || left > high) return -(int)INFINITY;

        if(low >=left && high<=right) return ST[id];

        int mid = low + (high - low)/2;
        return max(findMax(id*2, low, mid, left, right), findMax(id*2+1, mid+1, high, left, right));
    }

};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m;
    SegmentTree st(n);

    int left, right, value;
    for(int i = 0; i<m; i++){
        cin >> left >> right >> value;
        st.updateMany(1,1,n,left,right,value);
    }

    /*
    for(int i = 1; i<=n*4; i++){
        cout << st.ST[i] << " ";
    }
    */

    cin >> q;
    for(int i = 0; i<q; i++){
        cin >> left >> right;
        cout << st.findMax(1,1,n,left,right) << endl;
    }

    return 0;
}

