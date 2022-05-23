#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define vti vector<int>
#define vtv vector<vti>
#define msi map<string, int>
#define fow(i,a,b) for(int i = a; i<b; i++)
#define rep(i,a,b) for(int i = a; i<=b; i++)
#define red(i,a,b) for(int i = a; i>=b; i++)
#define db(x) cout << #x << " = " << x << endl;
#define el cout << endl
#define getBit(n,i) ((n>>i)&1)
#define MAX 10000

typedef long long ll;
using namespace std;

/// Global variable and input ///
ll n,k,sum,a[36];
map<ll,int> cnt1, cnt2;
void input(){
    cin >> n >> k;
    ll temp;
    fow(i,0,n){
        cin >> temp;
        temp -= k;
        a[i] = temp;
    }
}

void backTracking(int low, int high, bool include, ll s, bool ismap1){
    if(include) s+= a[low];

    if(low==high){
        if(s==0) sum++;

        if(ismap1) cnt1[s]++;
        else cnt2[s]++;
    }else{
        backTracking(low+1, high, true, s, ismap1);
        backTracking(low+1, high, false, s, ismap1);
    }
}

// for debugging
void backTracking(int low, int high, bool include, ll s, bool ismap1, string track){
    if(include){
        s+= a[low];
        track += "1";
    }else
        track += "0";
    if(low==high){
        if(s==0) sum++;
        db(track); db(s);
        if(ismap1) cnt1[s]++;
        else cnt2[s]++;
    }else{
        backTracking(low+1, high, true, s, ismap1, track);
        backTracking(low+1, high, false, s, ismap1, track);
    }
}

/// Process
void process(){
    sum = 0;
    int mid = (n-1)/2;

    backTracking(0, mid, true, 0, true);
    backTracking(0, mid, false, 0, true);
    backTracking(mid+1, n-1, true, 0, false);
    backTracking(mid+1, n-1, false, 0, false);

    for(auto it: cnt1){
        sum += (it.second * cnt2[-it.first]);
    }

    cout << sum - 1 - cnt1[0] - cnt2[0] << endl;
}

void test(){
    sum = 0;
    backTracking(0, n-1, true, 0, true, "");
    backTracking(0, n-1, false, 0, true, "");
    cout << sum - 2 << endl;
}

int main(){
    fast_io;
    input();
    //test();
    process();
    return 0;
}
