#include <bits/stdc++.h>
#define TUNA 1
#define EEL 2
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int previous = 0, current;
    //                                   M min  glM globalMax
    long n, tunaCount = 0, eelCount = 0, M = 0, glM = 0;
    cin >> n;
    for(auto i = 0; i<n; i++){
        cin >> current;
        if(current == previous){
            if(current == TUNA){
                tunaCount++;
            }else{
                eelCount++;
            }
        }else{
            M = tunaCount < eelCount ? tunaCount : eelCount;
            if(current == TUNA){
                tunaCount = 1;
            }else{
                eelCount = 1;
            }
            glM = glM > M ? glM:M;
        }
        previous = current;
    }
    M = tunaCount < eelCount ? tunaCount : eelCount;
    glM = glM > M ? glM:M;

    cout << glM * 2;
    return 0;
}

