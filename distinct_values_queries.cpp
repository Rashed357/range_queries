//You are given an array of n integers and q queries of the form: how many distinct values are there in a range [a,b]?


#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n=0): n(n), bit(n+1,0) {}
    void add(int idx, int val){
        for(; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    int sumPrefix(int idx){
        int s = 0;
        for(; idx > 0; idx -= idx & -idx) s += bit[idx];
        return s;
    }
    int rangeSum(int l, int r){
        return sumPrefix(r) - sumPrefix(l-1);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    if(!(cin >> n >> q)) return 0;

    vector<long long> a(n+1);
    vector<long long> vals; vals.reserve(n);
    for(int i = 1; i <= n; ++i){
        cin >> a[i];
        vals.push_back(a[i]);
    }

    // coordinate compress
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = (int)vals.size();
    vector<int> ac(n+1);
    for(int i = 1; i <= n; ++i){
        ac[i] = int(lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin()) + 1; // 1..m
    }

    struct Query { int l, r, id; };
    vector<Query> queries(q);
    for(int i = 0; i < q; ++i){
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    sort(queries.begin(), queries.end(), [](const Query &A, const Query &B){
        return A.r < B.r;
    });

    Fenwick fw(n);
    vector<int> last(m+1, 0); // last position for each compressed value
    vector<int> ans(q);
    int ptr = 0;

    for(int i = 1; i <= n; ++i){
        int val = ac[i];
        if(last[val] != 0) fw.add(last[val], -1);
        fw.add(i, +1);
        last[val] = i;

        while(ptr < q && queries[ptr].r == i){
            ans[queries[ptr].id] = fw.rangeSum(queries[ptr].l, queries[ptr].r);
            ++ptr;
        }
    }

    for(int i = 0; i < q; ++i) cout << ans[i] << '\n';
    return 0;
}
