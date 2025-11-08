#include<bits/stdc++.h>
using namespace std;
#define ll long long
 
const int mx = 2e5+7;
int a[mx];
ll sum[4*mx];
int n,q;
 
void build_seg(int node, int low, int high){
 
    if(low==high){
        sum[node] = a[low];
        return;
    }
 
    int left = 2*node;
    int right = left+1;
    int mid = (low+high)/2;
 
    build_seg(left, low, mid);
    build_seg(right, mid+1, high);
 
    sum[node] = sum[left] + sum[right];
}
 
 
void update(int node, int low, int high, int idx, int val){
 
    if(low==high){
        sum[node] = val;
        return;
    }
 
    int left = 2*node;
    int right = left+1;
    int mid = (low+high)/2;
 
    if(idx<=mid)
        update(left,low,mid,idx,val);
    else
        update(right,mid+1,high,idx,val);
 
    sum[node] = sum[left]+sum[right];
}
 
 
ll query(int node, int low, int high, int l, int r){
 
 
    int left = 2*node;
    int right = left+1;
    int mid = (low+high)/2;
 
    if(high<l or low>r)
        return 0;
 
    if(low>=l and high<=r)
        return sum[node];
 
    return query(left,low,mid,l,r) + query(right,mid+1,high,l,r);
}
 
 
void solve(){
    cin>>n>>q;
 
    for(int i=1; i<=n; i++)
        cin>>a[i];
 
    build_seg(1,1,n);
 
    while(q--){
        int k;
        cin>>k;
 
        if(k==1){
            int idx, val;
            cin>>idx>>val;
            update(1,1,n,idx,val);
        }
 
        else{
            int l,r;
            cin>>l>>r;
 
            ll x = query(1,1,n,l,r);
            cout<<x<<endl;
        }
    }
}
 
int main(){
 
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    solve();
 
    return 0;
}
