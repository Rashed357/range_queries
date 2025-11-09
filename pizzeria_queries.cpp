//The pizza price p_k in building k becomes x.
//You are in building k and want to order a pizza. What is the minimum price?
//p_a+|a-b|.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)4e18;

struct SegTree {
    int n;
    vector<ll> st;
    SegTree(int _n=0){ init(_n); }
    void init(int _n){
        n = _n;
        st.assign(4*n+5, INF);
    }
    void build(int p, int l, int r, const vector<ll>& a){
        if(l==r){ st[p] = a[l]; return; }
        int m=(l+r)>>1;
        build(p<<1,l,m,a);
        build(p<<1|1,m+1,r,a);
        st[p] = min(st[p<<1], st[p<<1|1]);
    }
    ll query(int p, int l, int r, int i, int j){
        if(i>r || j<l) return INF;
        if(i<=l && r<=j) return st[p];
        int m=(l+r)>>1;
        return min(query(p<<1,l,m,i,j), query(p<<1|1,m+1,r,i,j));
    }
    void update(int p, int l, int r, int idx, ll val){
        if(l==r){ st[p]=val; return; }
        int m=(l+r)>>1;
        if(idx<=m) update(p<<1,l,m,idx,val);
        else update(p<<1|1,m+1,r,idx,val);
        st[p] = min(st[p<<1], st[p<<1|1]);
    }

    // convenience wrappers:
    void build(const vector<ll>& a){ build(1,1,n,a); }
    ll query(int l, int r){ if(l>r) return INF; return query(1,1,n,l,r); }
    void update(int idx, ll val){ update(1,1,n,idx,val); }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    if(!(cin >> n >> q)) return 0;
    vector<ll> p(n+1);
    for(int i=1;i<=n;i++) cin >> p[i];

    // prepare arrays valL = p[i]-i, valR = p[i]+i
    vector<ll> valL(n+1), valR(n+1);
    for(int i=1;i<=n;i++){
        valL[i] = p[i] - (ll)i;
        valR[i] = p[i] + (ll)i;
    }

    SegTree segL(n), segR(n);
    segL.build(valL);
    segR.build(valR);

    while(q--){
        int t; cin >> t;
        if(t==1){
            int k; ll x; cin >> k >> x;
            p[k] = x;
            segL.update(k, p[k] - (ll)k);
            segR.update(k, p[k] + (ll)k);
        } else {
            int k; cin >> k;
            ll ansL = segL.query(1,k);
            if(ansL < (ll)4e18) ansL += (ll)k;
            ll ansR = segR.query(k,n);
            if(ansR < (ll)4e18) ansR -= (ll)k;
            cout << min(ansL, ansR) << '\n';
        }
    }
    return 0;
}
