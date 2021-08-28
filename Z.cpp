#include <bits/stdc++.h>
using namespace std;
#define MAX_N 100005

int N;
int Z[MAX_N], L, R;
string S;

int main() {

    cin >> S;
    N = S.size();

    for(int i=1; i<N; ++i){
        if(i > R){
            L = R = i;
            while(R < N && S[R-L] == S[R]) ++R;
            Z[i] = R-L; --R;
        }else{
            if(Z[i-L] <= R-i) Z[i] = Z[i-L];
            else{
                L = i;
                while(R < N && S[R-L] == S[R]) ++R;
                Z[i] = R-L; --R;
            }
        }
    }

    for(int i=0; i<N; ++i) cout << Z[i] << endl;
}
