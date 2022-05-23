#include <bits/stdc++.h>
#define repeat(i,a,b) for(int i = a; i<=b; i++)

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n,s;
    cin >> n;
    int cnt = 0, temp;
    repeat(i,1,n){
        int h = (int) n/i;
        repeat(j,1,h){
            cnt += (int) h/j;
        }
    }

    cout << cnt;

    return 0;
}

