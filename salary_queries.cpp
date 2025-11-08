//! k x: change the salary of employee k to x
//? a b: count the number of employees whose salary is between a \ldots b

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n=0): n(n), bit(n+1,0) {}
    void add(int i, int delta){
        for(; i<=n; i += i & -i) bit[i] += delta;
    }
    int sum(int i){
        int s = 0;
        for(; i>0; i -= i & -i) s += bit[i];
        return s;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    if(!(cin >> n >> q)) return 0;
    vector<ll> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];

    // Read queries first to collect update values for compression
    struct Query { char t; int k; ll x; ll y; };
    vector<Query> queries;
    queries.reserve(q);
    vector<ll> to_compress;
    to_compress.reserve(n + q);

    for(int i=1;i<=n;i++) to_compress.push_back(a[i]);

    for(int i=0;i<q;i++){
        char t; cin >> t;
        if(t == '!'){
            int k; ll x; cin >> k >> x;
            queries.push_back({t, k, x, 0});
            to_compress.push_back(x);
        } else {
            ll L, R; cin >> L >> R;
            queries.push_back({t, 0, L, R});
            // note: we DO NOT need to push L and R into compression
            // it's enough to compress existing salary values (initial + updates).
        }
    }

    // build compression
    sort(to_compress.begin(), to_compress.end());
    to_compress.erase(unique(to_compress.begin(), to_compress.end()), to_compress.end());
    int m = (int)to_compress.size();

    Fenwick bit(m);
    auto idx_of = [&](ll val)->int{
        // index in BIT (1-based) for an existing compressed value
        int pos = int(lower_bound(to_compress.begin(), to_compress.end(), val) - to_compress.begin());
        return pos + 1;
    };

    // initialize BIT with initial salaries
    for(int i=1;i<=n;i++){
        int id = idx_of(a[i]);
        bit.add(id, 1);
    }

    // process queries
    for(auto &qu: queries){
        if(qu.t == '!'){
            int k = qu.k;
            ll newv = qu.x;
            // remove old
            int old_id = idx_of(a[k]);
            bit.add(old_id, -1);
            // add new
            int new_id = idx_of(newv);
            bit.add(new_id, +1);
            a[k] = newv;
        } else {
            ll L = qu.x, R = qu.y;
            // pos_b = # compressed values <= R
            int pos_b = int(upper_bound(to_compress.begin(), to_compress.end(), R) - to_compress.begin()); // 0..m
            int pos_a = int(lower_bound(to_compress.begin(), to_compress.end(), L) - to_compress.begin()); // # values < L
            // fenwick uses 1-based indexes; sum(pos) where pos could be 0..m is fine (sum(0)=0)
            int ans = bit.sum(pos_b) - bit.sum(pos_a);
            cout << ans << '\n';
        }
    }
    return 0;
}
