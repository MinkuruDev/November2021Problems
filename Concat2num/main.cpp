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

struct StrNum{
    string value;

    StrNum(){
        value = "0";
    }

    StrNum(string s){
        value = s;
    }

    bool operator<(const StrNum other){
        if(value.length() < other.value.length()) return true;
        else if(value.length() > other.value.length()) return false;
        else return value < other.value;
    }

    bool operator>(const StrNum other){
        if(value.length() > other.value.length()) return true;
        else if(value.length() < other.value.length()) return false;
        else return value > other.value;
    }

    StrNum operator+(const StrNum other){
        return StrNum(value + other.value);
    }
};

/// Global variable and input ///
int t,n;
StrNum l,r;
vector<StrNum> a;
void input(){

}

int upper_equal(int i){
    int low = 0, high = n-1, mid;

    while(low < high){
        mid = (low + high) / 2;
        if(a[i] + a[mid] < l){
            low = mid + 1;
        }else{
            high = mid;
        }
    }

    if(a[i] + a[high] < l) return -1;
    return high;
}

int lower_equal(int i){
    int low = 0, high = n-1, mid;

    while(low < high){
        mid = (low + high + 1) / 2;
        if(a[i] + a[mid] > r){
            high = mid - 1;
        }else{
            low = mid;
        }
    }

    if(a[i] + a[low] > r) return -1;
    return low;
}

/// Process ///
void process(){
    cin >> t;
    while(t--){
        cin >> n >> l.value >> r.value;
        a.clear();
        fow(i,0,n){
            StrNum temp;
            cin >> temp.value;
            a.push_back(temp);
        }

        sort(a.begin(), a.end());
        int sum = 0;
        fow(i,0,n){
            int low  = upper_equal(i);
            int high = lower_equal(i);
            // db(low); db(high);

            if(high == -1 || low == -1 || low > high) continue;

            sum += high - low + 1;
        }
        cout << sum << endl;
    }
}

int main(){
    fast_io;
    input();
    process();
    return 0;
}
