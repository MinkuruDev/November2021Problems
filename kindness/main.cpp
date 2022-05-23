#include <bits/stdc++.h>
#define repeat(i,a,b) for(int i = a; i<b; i++)

using namespace std;

int calc(string s){
    int cnt[26];
    repeat(i,0,26){
        cnt[i] = 0;
    }

    repeat(i,0,s.length()){
        cnt[s[i] - 'a']++;
    }
    int sum = s.length();
    int total = 0;

    repeat(i,0,s.length()){
        total += cnt[s[i]-'a']*(sum - cnt[s[i]-'a']);
        //sum--; cnt[s[i]-'a']--;
    }

    return total / 2;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> s;

    cout << calc(s);

    return 0;
}

