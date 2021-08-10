#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Reference: https://blog.naver.com/kks227/221028710658
struct SA{
    int n, d;
    string S;
    vector<int> sa, pos, lcp;

    SA(){}

    void findSA(){
        for(int i=0; i<n; ++i){
            sa[i] = i;
            pos[i] = S[i];
        }
        for(d=1; ; d<<=1){
            auto cmp = [&](int i, int j){
                if(pos[i]!=pos[j]) return pos[i] < pos[j];
                i += d; j += d;
                return (i<n && j<n) ? (pos[i] < pos[j]) : (i>j);
            };
            sort(sa.begin(), sa.end(), cmp);
            vector<int> tmp(n, 0);
            for(int i=0; i<n-1; ++i)
                tmp[i+1] = tmp[i] + cmp(sa[i], sa[i+1]);
            for(int i=0; i<n; ++i)
                pos[sa[i]] = tmp[i];
            if(tmp[n-1] == n-1) break;
        }
    }

    void findLCP(){
        for(int i=0, k=0; i<n; ++i, k=max(k-1, 0)){
            if(pos[i] == n-1) continue;
            for(int j=sa[pos[i]+1]; S[i+k]==S[j+k]; ++k);
            lcp[pos[i]] = k;
        }
    }

    void init(string _S){
        S = _S;
        n = S.size();
        d = 0;
        sa.resize(n, 0);
        pos.resize(n, 0);
        lcp.resize(n, 0);
        findSA();
        findLCP();
    }
} sa;
/////////////////////////////////////////////////////////////////////////////////////////////////////////

string S;

int main(){
    cin >> S;
    sa.init(S);
}
