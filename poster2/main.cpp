#include <bits/stdc++.h>
#define MAX 10000000

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t,n,l,r;
    int max = 0;
    int cnt = 0;

    cin >> t;
    cout << t;
    for(int i = 0; i<t; i++){
        cin >> n;
        cout << n;
        bool check[n+1];
        int wall[1000];

        for(int j = 1; i<=n; j++){
            cin >> l >> r;
            cout << l << r;
            max = r > max ? r : max;
            for(int k = l; k<=r; k++){
                wall[k] = j;
            }
        }

        for(int j = 1; j<=max; j++)
            check[wall[j]] = true;

        cnt = 0;
        for(int j = 1; i<=n; j++)
            cnt += check[j];

        cout << cnt << endl;
    }

    return 0;
}


