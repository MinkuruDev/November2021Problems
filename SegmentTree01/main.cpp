#include <bits/stdc++.h>
#define MAX (50000*4+1)

using namespace std;

int ST[MAX],lazy[MAX];

void updateMany(int id, int l, int r, int u, int v, int val){
    if(l>v || r<u) return;

    if(l == r){
        ST[id] += val;
        return;
    }

    int mid = (l+r)/2;
    updateMany(id*2,l,mid,u,v,val);
    updateMany(id*2+1,mid+1,r,u,v,val);

    ST[id] = max(ST[id*2],ST[id*2+1]);
}

void down(int id){
    int t = lazy[id];

    ST[id*2] += t;
    lazy[id*2] += t;

    ST[id*2+1] += t;
    lazy[id*2+1] += t;

    lazy[id] = 0;
}

void updateLazy(int id, int l, int r, int u, int v, int val){
    if(l>v || r<u) return;

    if(l>=u && r<=v){
        lazy[id] += val;
        ST[id] += val;
        return;
    }

    //down(id);
    int mid = (l+r)/2;
    updateLazy(id*2,l,mid,u,v,val);
    updateLazy(id*2+1,mid+1,r,u,v,val);

    ST[id] = max(ST[id*2],ST[id*2+1]) + lazy[id];
}

int get(int id, int l, int r, int u, int v){
    if(l>v || r<u) return -(int)INFINITY;

    if(l>=u && r<=v) return ST[id];

    //down(id);
    int mid = (l+r)/2;
    return max(get(id*2,l,mid,u,v), get(id*2+1,mid+1,r,u,v)) + lazy[id];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n,m;
    cin >> n >> m;
    for(int i = 0; i<4*n; i++){
        ST[i] = 0;
    }

    int u,v,k;
    for(int i = 0; i<m; i++){
        cin >> u >> v >> k;
        updateLazy(1,1,n,u,v,k);
    }

    int q;
    cin >> q;
    for(int i = 0; i<q; i++){
        cin >> u >> v;
        cout << get(1,1,n,u,v) << endl;
    }
    return 0;
}

