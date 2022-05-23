#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define vti vector<int>
#define vtv vector<vti>
#define msi map<string, int>
#define fow(i,a,b) for(int i = a; i<b; i++)
#define rep(i,a,b) for(int i = a; i<=b; i++)
#define red(i,a,b) for(int i = a; i>=b; i++)
#define db(x) cout << #x << " = " << x << endl;
#define getBit(n,i) ((n>>i)&1)
#define MAX 10000

typedef long long ll;
using namespace std;

/// Global variable and input ///
string s;
int sz;
vector<string> strings;
void input(){
    cin >> sz;
    cin >> s;
}

/// Process
void process(){
    int m = INT_MAX;
    string temp = "";
    fow(i,0,sz){
        if(s[i] == '#'){
            strings.push_back(temp);
            m = temp.length() < m ? temp.length() : m;
            temp = "";
        }else{
            temp += bitset<7>(s[i]).to_string();
        }
    }
    strings.push_back(temp);
    m = temp.length() < m ? temp.length() : m;

    int n = strings.size();
    int zero = 0, one = 0;
    fow(i,0,n){
        fow(j,0,m){
            if(strings[i][j] == '0') zero++;
            else one++;
        }
    }

    cout << n << " " << m << endl;
    printf("%.9f",(double)one/zero);
}

int main(){
    fast_io;
    input();
    process();
    return 0;
}
