#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
 
void solve() {
 
    int n,q;
    cin>>n>>q;
 
    vector<string>v(n+1);
 
    for(int i=1; i<=n; i++){
        string s;
        cin>>s;
        s = '#'+s;
        v[i] = s;
    }
 
    vector<vector<ll>> pf(n+1,vector<ll>(n+1));
 
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            pf[i][j] = (v[i][j] == '*');
 
            pf[i][j] += (pf[i-1][j]+pf[i][j-1]-pf[i-1][j-1]);
        }
    }
 
    while(q--){
 
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
 
        ll ans = pf[x2][y2] - pf[x1-1][y2]-pf[x2][y1-1]+pf[x1-1][y1-1];
 
        cout<<ans<<endl;
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
