#include <bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define vti vector<int>
#define vtv vector<vti>
#define msi map<string, int>
#define fow(i,a,b) for(int i = a; i<b; i++)
#define rep(i,a,b) for(int i = a; i<=b; i++)
#define red(i,a,b) for(int i = a; i>=b; i++)
#define db(x) cout << #x << " = " << x << endl
#define el cout << endl
#define getBit(n,i) ((n>>i)&1)
#define MAX 100000

typedef long long ll;
using namespace std;

struct Block{
    int cnt[7];

    Block(){
        fow(i,0,7) cnt[i] = 0;
    }
};

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

/// Global variable and input ///
vector<Block> blocks;
vti a;
int q,l[MAX],r[MAX],k[MAX],blockSize,blockCount,M;

void input(){
    cin >> q;
    M = 0;
    fow(i,0,q){
        cin >> l[i] >> r[i] >> k[i];
        M = max(r[i],M);
    }
}

void init(){
    blockSize = round(sqrt(++M));
    blockCount = ceil((float)M/blockSize);

    int p,c = 0;
    fow(i,0,blockCount){
        Block block;
        fow(j,0,blockSize){
            p = getPrimeAtom(c++);
            a.push_back(p);
            block.cnt[p%7]++;
        }
        blocks.push_back(block);
    }
}

int get(int left, int right, int value){
    int blockL = left/blockSize;
    int blockR = right/blockSize;

    int sum = 0;
    if(blockL == blockR){
        rep(i,left,right){
            if(a[i]==value%7) sum++;
        }
        return sum;
    }


    fow(i,blockL+1,blockR){
        sum += blocks[i].cnt[value%7];
    }

    if(blockL*blockSize == left){
        sum += blocks[blockL].cnt[value%7];
    }else{
        fow(i,left,(blockL+1)*blockSize){
            if(a[i]==value%7) sum++;
        }
    }

    if((right+1)%blockSize==0){
        sum += blocks[blockR].cnt[value%7];
    }else{
        rep(i,blockR*blockSize,right){
            if(a[i]==value%7) sum++;
        }
    }

    return sum;
}

/// Process ///
void process(){
    fow(i,0,q){
        cout << get(l[i], r[i], k[i]) << endl;
    }
}

int main(){
    fast_io;
    input();
    init();
    process();
    return 0;
}
