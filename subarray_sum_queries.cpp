
//After each update, print the maximum subarray sum. Empty subarrays (with sum 0) are allowed.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    ll sum, pref, suf, best;
    Node(ll v = LLONG_MIN) {
        if (v == LLONG_MIN) { // invalid default
            sum = pref = suf = best = LLONG_MIN;
        } else {
            sum = pref = suf = best = v;
        }
    }
};

Node mergeNode(const Node &L, const Node &R) {
    if (L.sum == LLONG_MIN) return R;
    if (R.sum == LLONG_MIN) return L;
    Node P;
    P.sum = L.sum + R.sum;
    P.pref = max(L.pref, L.sum + R.pref);
    P.suf  = max(R.suf, R.sum + L.suf);
    P.best = max({L.best, R.best, L.suf + R.pref});
    return P;
}

struct SegTree {
    int n;
    vector<Node> st;
    SegTree(int _n): n(_n), st(4*n + 5, Node(LLONG_MIN)) {}

    void build(int p, int l, int r, const vector<ll> &a) {
        if (l == r) {
            st[p] = Node(a[l]); // a is 1-based
            return;
        }
        int m = (l + r) >> 1;
        build(p<<1, l, m, a);
        build(p<<1|1, m+1, r, a);
        st[p] = mergeNode(st[p<<1], st[p<<1|1]);
    }

    void update(int p, int l, int r, int idx, ll val) {
        if (l == r) {
            st[p] = Node(val);
            return;
        }
        int m = (l + r) >> 1;
        if (idx <= m) update(p<<1, l, m, idx, val);
        else update(p<<1|1, m+1, r, idx, val);
        st[p] = mergeNode(st[p<<1], st[p<<1|1]);
    }

    // helper wrappers
    void build(const vector<ll> &a) { build(1, 1, n, a); }
    void update(int idx, ll val) { update(1, 1, n, idx, val); }
    ll answer() {
        // empty subarray allowed
        return max(0LL, st[1].best);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<ll> a(n+1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    SegTree seg(n);
    seg.build(a);
    while (m--) {
        int k; ll x;
        cin >> k >> x;
        seg.update(k, x);
        cout << seg.answer() << '\n';
    }
    return 0;
}
