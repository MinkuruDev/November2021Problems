#include <bits/stdc++.h>
#define MAX 100000
using namespace std;

int ST[MAX * 4];
int divable[MAX * 4];

void updateMany(int id, int l, int r, int u, int v){
    if(l>v || r<u) return;

    if(l==r){
        ST[id] = ST[id] + 1;
        divable[id] = (ST[id] % 3 == 0);
        return;
    }

    int m = (l + r) / 2;
    updateMany(id*2,l,m,u,v);
    updateMany(id*2+1,m+1,r,u,v);

    divable[id] = divable[id*2] + divable[id*2+1];
}

int get(int id, int l, int r, int u, int v){
    if(l>v || r<u) return 0;

    if(l>=u && r<=v) return divable[id];

    int m = (l + r) / 2;
    return get(id*2,l,m,u,v) + get(id*2+1,m+1,r,u,v);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n,q;
    cin >> n;
    cin >> q;
    updateMany(1,1,n,1,n);
    updateMany(1,1,n,1,n);
    updateMany(1,1,n,1,n);
    int t,l,r;

    for(int i = 0; i<q; i++){
        cin >> t >> l >> r;
        r++;l++;
        if(t == 0){
            updateMany(1,1,n,l,r);
        }else{
            cout << get(1,1,n,l,r) << endl;
        }
    }

    return 0;
}
