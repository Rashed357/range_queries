// There are n hotels on a street. For each hotel you know the number of free rooms. Your task is to assign hotel rooms for groups of tourists. All members of a group want to stay in the same hotel.
// The groups will come to you one after another, and you know for each group the number of rooms it requires. You always assign a group to the first hotel having enough rooms. After this, the number of free rooms in the hotel decreases.


#include<bits/stdc++.h>
using namespace std;
#define ll long long
 
const int mx = 2e5+7;
int a[mx];
ll tree[4*mx];
int n,q,ans;
 
void build_seg(int node, int low, int high){
 
    if(low==high){
        tree[node] = a[low];
        return;
    }
 
    int left = 2*node;
    int right = left+1;
    int mid = (low+high)/2;
 
    build_seg(left, low, mid);
    build_seg(right, mid+1, high);
 
    tree[node] = max(tree[left] , tree[right]);
}
 
 
void update(int node, int low, int high, int val){
 
    if(low==high){
        if(tree[node]<val){
            ans = 0;
            return;
        }
 
        tree[node] -= val;
        ans = low;
        return;
    }
 
    int left = 2*node;
    int right = left+1;
    int mid = (low+high)/2;
 
    if(val<=tree[left])
        update(left,low,mid,val);
    else 
        update(right,mid+1,high,val);
    
    tree[node] = max(tree[left],tree[right]);
}
 
 
ll query(int node, int low, int high, int l, int r){
 
 
    int left = 2*node;
    int right = left+1;
    int mid = (low+high)/2;
 
    if(high<l or low>r)
        return INT_MAX;
 
    if(low>=l and high<=r)
        return tree[node];
 
    return max(query(left,low,mid,l,r) , query(right,mid+1,high,l,r));
}
 
 
void solve(){
    cin>>n>>q;
 
    for(int i=1; i<=n; i++)
        cin>>a[i];
 
    build_seg(1,1,n);
 
    while(q--){
        
        int r;
        cin>>r;
 
        update(1,1,n,r);
        cout<<ans<<endl;
    }
}
 
int main(){
 
    ios::sync_with_stdio(false);
    cin.tie(0);
 
    solve();
 
    return 0;
}
