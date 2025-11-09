#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll NEG_INF = (ll)-9e18;

struct Node {
    ll sum;
    ll pref;
    Node(ll s = 0, ll p = NEG_INF) : sum(s), pref(p) {}
};

int n, q;
vector<ll> a;
vector<Node> seg; // size 4*n

Node mergeNode(const Node &L, const Node &R) {
    Node res;
    res.sum = L.sum + R.sum;
    res.pref = max(L.pref, L.sum + R.pref);
    return res;
}

void build(int idx, int l, int r) {
    if (l == r) {
        seg[idx] = Node(a[l], a[l]);
        return;
    }
    int mid = (l + r) >> 1;
    build(idx<<1, l, mid);
    build(idx<<1|1, mid+1, r);
    seg[idx] = mergeNode(seg[idx<<1], seg[idx<<1|1]);
}

void update(int idx, int l, int r, int pos, ll val) {
    if (l == r) {
        seg[idx] = Node(val, val);
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(idx<<1, l, mid, pos, val);
    else update(idx<<1|1, mid+1, r, pos, val);
    seg[idx] = mergeNode(seg[idx<<1], seg[idx<<1|1]);
}

Node query(int idx, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return Node(0, NEG_INF); // neutral
    if (ql <= l && r <= qr) return seg[idx];
    int mid = (l + r) >> 1;
    Node left = query(idx<<1, l, mid, ql, qr);
    Node right = query(idx<<1|1, mid+1, r, ql, qr);
    return mergeNode(left, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    a.assign(n+1, 0); // 1-based
    for (int i = 1; i <= n; ++i) cin >> a[i];
    seg.assign(4*n + 5, Node());
    build(1, 1, n);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int k; ll u; cin >> k >> u;
            update(1, 1, n, k, u);
        } else {
            int L, R; cin >> L >> R;
            Node res = query(1, 1, n, L, R);
            cout << max(0LL, res.pref) << '\n';
        }
    }
    return 0;
}
