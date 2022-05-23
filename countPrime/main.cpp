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

int getPrimeAtom(int n);

struct Node{
    int primeAtom[8];

    Node(){}

    Node(int n){
        rep(i,1,7){
            primeAtom[i] = 0;
        }

        primeAtom[getPrimeAtom(n)] = 1;
    }

    Node operator+(const Node other){
        Node result;
        rep(i,1,7){
            result.primeAtom[i] = primeAtom[i] + other.primeAtom[i];
        }

        return result;
    }
};

/// Global variable and input ///
vector<Node> prefixSum(MAX + 1);
int q,l[MAX],r[MAX],k[MAX],M;
void input(){
    cin >> q;
    M = 0;
    fow(i,0,q){
        cin >> l[i] >> r[i] >> k[i];
        M = r[i] > M ? r[i] : M;
    }
}

int checkPrime(int n){
    int s = (int) sqrt(n);
    rep(i,2,s){
        if(n%i==0) return i;
    }

    return 1;
}

int getPrimeAtom(int n){
    int cnt = 0;
    while(true){
        int p = checkPrime(n);
        if(p<2){
            return ++cnt;
        }

        while(n%p==0) n/=p;
        cnt++;
        if(p>n) break;
    }
    return cnt;
}

void build(){
    Node zero;
    rep(i,1,7){
        zero.primeAtom[i] = 0;
    }
    prefixSum[0] = zero;
    Node current = zero;
    rep(i,1,M){
        current = current + Node(i);
        prefixSum[i] = current;
    }
}

int get(int l, int r, int v){
    return prefixSum[r].primeAtom[v] - prefixSum[l-1].primeAtom[v];
}

/// Process
void process(){
    fow(i,0,q){
        cout << get(l[i],r[i],k[i]) << endl;
    }
}

void test(){
    Node node(94);
    rep(i,1,7){
        db(node.primeAtom[i]);
    }
    cout << get(94,664,2) << endl;
    rep(i,94,664){
        if(getPrimeAtom(i) == 1) cout << i << " ";
    }
}

int main(){
    fast_io;
    input();
    build();
    //test();
    process();
    return 0;
}
