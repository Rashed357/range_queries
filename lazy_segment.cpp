#include <bits/stdc++.h>
using namespace std;
 
const int mx = 2e5 + 7;
long long tree[4 * mx], lazy[4 * mx];
int n, q;
 
// Build the segment tree
void build(vector<int>& arr, int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1]; // Placeholder, not used here
    }
}
 
// Apply the pending updates
void propagate(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += lazy[node] * (end - start + 1); // Apply lazy value
        if (start != end) {
            lazy[2 * node] += lazy[node];     // Propagate to left child
            lazy[2 * node + 1] += lazy[node]; // Propagate to right child
        }
        lazy[node] = 0; // Clear the lazy value for the current node
    }
}
 
// Update range [l, r] with value x
void update(int node, int start, int end, int l, int r, int x) {
    propagate(node, start, end); // Apply any pending updates
 
    if (start > r || end < l) {
        return; // No overlap
    }
 
    if (start >= l && end <= r) {
        lazy[node] += x; // Mark the lazy value
        propagate(node, start, end); // Apply immediately
        return;
    }
 
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r, x);
    update(2 * node + 1, mid + 1, end, l, r, x);
}
 
// Query the value at index k
long long query(int node, int start, int end, int k) {
    propagate(node, start, end); // Apply any pending updates
 
    if (start == end) {
        return tree[node];
    }
 
    int mid = (start + end) / 2;
    if (k <= mid) {
        return query(2 * node, start, mid, k);
    } else {
        return query(2 * node + 1, mid + 1, end, k);
    }
}
 
void solve() {
    cin >> n >> q;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
 
    // Build the segment tree
    build(arr, 1, 1, n);
 
    while (q--) {
        int type;
        cin >> type;
 
        if (type == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            update(1, 1, n, l, r, x);
        } else if (type == 2) {
            int k;
            cin >> k;
            cout << query(1, 1, n, k) << '\n';
        }
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    solve();
    return 0;
}
