#include <bits/stdc++.h>
#define MAX 100000

using namespace std;

int main(){
    //ios_base::sync_with_stdio(false);
    //cin.tie(0);

    int wall[MAX],l[MAX],r[MAX];
    int t,n;
    int M = 0;
    int cnt = 0;

    cin >> t;
    // cout << t << endl;;
    for(int i = 0; i<t; i++){
        cin >> n;
        // cout << n << endl;
        bool check[n+1];

        for(int j = 1; j<=n; j++){
            cin >> l[j] >> r[j];
            M = M > r[j] ? M : r[j];
            // cout << l << " " << r << endl;
        }

        for(int j = 1; j<=M; j++)
            wall[j] = false;

        for(int j = 1; j<=n; j++){
            for(int k=l[j]; k<=r[j]; k++){
                wall[k] = j;
            }
        }

        for(int j = 1; j<=M; j++)
            check[wall[j]] = true;

        cnt = 0;
        for(int j = 1; j<=n; j++)
            if(check[j]) cnt++;

        cout << cnt << endl;
    }

    return 0;
}

