#include <bits/stdc++.h>
#define MAX 50000

using namespace std;

int st1[MAX*4], st2[MAX*4], height[MAX];

void update(int id, int low, int high, int index, int value){
    if(index<low || index>high) return;

    if(low == high){
        st1[id] = value;
        st2[id] = value;
        return;
    }

    int mid = ((low + high) >> 1);
    int id2 = id << 1;
    update(id2, low, mid, index, value);
    update(id2+1, mid+1, high, index, value);

    st1[id] = max(st1[id2], st1[id2+1]);
    st2[id] = min(st2[id2], st2[id2+1]);
}

void quickBuild(int id, int low, int high){
    if(low == high){
        st1[id] = height[low];
        st2[id] = height[high];
        return;
    }

    int mid = ((low + high) >> 1);
    int id2 = id << 1;
    quickBuild(id2, low, mid);
    quickBuild(id2+1, mid+1, high);

    st1[id] = max(st1[id2], st1[id2+1]);
    st2[id] = min(st2[id2], st2[id2+1]);
}

int getMax(int id, int low, int high, int left, int right){
    if(high<left || low>right) return 0;

    if(low>=left && high<=right) return st1[id];

    int mid = (low + high) >> 1;
    int id2 = id << 1;
    return max(getMax(id2, low, mid, left, right),
               getMax(id2+1, mid+1, high, left, right));
}

int getMin(int id, int low, int high, int left, int right){
    if(high<left || low>right) return (int) INFINITY;

    if(low>=left && high<=right) return st2[id];

    int mid = (low + high) >> 1;
    int id2 = id << 1;
    return min(getMin(id2, low, mid, left, right),
               getMin(id2+1, mid+1, high, left, right));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n,q;
    cin >> n >> q;
    int h;

    for(int i=1; i<=n; i++){
        cin >> height[i];
    }
    quickBuild(1,1,n);

    int l,r;
    for(int i=0; i<q; i++){
        cin >> l >> r;
        cout << getMax(1,1,n,l,r) - getMin(1,1,n,l,r) << endl;
    }

    return 0;
}

