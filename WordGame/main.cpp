#include <bits/stdc++.h>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    map<string, int> m;
    int n;
    cin >> n;
    string previous, current;
    cin >> previous;
    m[previous] = 1;
    bool flag = true;

    for(int i = 2; i<=n; i++){
        cin >> current;
        if(current[0] != previous[previous.length() - 1] || m[current]){
            cout << "NO\n" << i;
            flag = false;
            break;
        }

        m[current] = 1;
        previous = current;
    }

    if(flag){
        cout << "YES";
    }

    return 0;
}

