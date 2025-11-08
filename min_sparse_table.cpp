#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
 
const int N = 2e5+7;
int a[N], spt[N][20], lg2[N];
int n;
 
void build(){
   for(int i = 1; i<=n; i++)
      spt[i][0] = a[i];
 
   for(int j = 1; j<20; j++){
      for(int i = 1; i + (1<<j) - 1 <= n; i++){
         spt[i][j] = min(spt[i][j-1],spt[i+(1<<(j-1))][j-1]);
      }
   }
}
 
void solve(){
    cin>>n;
    int q; cin>>q;
    for(int i = 1; i<=n; i++)
      cin>>a[i];
 
   build();
 
   while(q--){
      int l, r; cin>>l>>r;
      int len = r-l+1;
      int p = lg2[len];
 
      int x = min(spt[l][p],spt[r-(1<<p)+1][p]);
      cout << x << endl;
   }
}
 
int32_t main(){
   ios::sync_with_stdio(false);
   cin.tie(NULL); cout.tie(NULL);
 
   lg2[1] = 0;
   for(int i = 2; i<N; i++)
      lg2[i] = lg2[i/2] + 1;
  
   //int t; cin >> t; while(t--)
   solve();
 
   return 0;
}
