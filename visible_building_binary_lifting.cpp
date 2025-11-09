//cnt of next increasing greater elements

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    if (!(cin >> n >> q)) return 0;
    vector<int> h(n+1);
    for (int i = 1; i <= n; ++i) cin >> h[i];

    // 1) nextGreater: first index j>i with h[j] > h[i], or n+1 if none
    vector<int> nextG(n+2, n+1);
    vector<int> st; // stack of indices, decreasing heights
    for (int i = n; i >= 1; --i) {
        while (!st.empty() && h[st.back()] <= h[i]) st.pop_back();
        nextG[i] = st.empty() ? n+1 : st.back();
        st.push_back(i);
    }
    nextG[n+1] = n+1;

    // 2) binary lifting table
    int LOG = 1;
    while ((1 << LOG) <= n+1) ++LOG;
    vector<vector<int>> up(LOG, vector<int>(n+2, n+1));
    for (int i = 1; i <= n+1; ++i) up[0][i] = nextG[i];
    for (int k = 1; k < LOG; ++k) {
        for (int i = 1; i <= n+1; ++i) {
            up[k][i] = up[k-1][ up[k-1][i] ];
        }
    }

    // 3) answer queries
    while (q--) {
        int a, b; cin >> a >> b;
        int pos = a;
        int ans = 1; // a itself is visible
        for (int k = LOG-1; k >= 0; --k) {
            if (up[k][pos] <= b) {
                ans += (1 << k);
                pos = up[k][pos];
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
