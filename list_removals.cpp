//You are given a list consisting of n integers. Your task is to remove elements from the list at given positions, and report the removed elements.

#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n=0): n(n), bit(n+1,0) {}

    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    int sum(int idx) {
        int r = 0;
        for (; idx > 0; idx -= idx & -idx) r += bit[idx];
        return r;
    }

    // find smallest index pos such that sum(pos) >= k
    int find_kth(int k) {
        int pos = 0;
        // get largest power of two <= n
        int pw = 1;
        while (pw << 1 <= n) pw <<= 1;
        
        for (int step = pw; step > 0; step >>= 1) {
            if (pos + step <= n && bit[pos + step] < k) {
                k -= bit[pos + step];
                pos += step;
            }
        }
        return pos + 1; // 1-based index
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<long long> a(n+1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<int> p(n+1);
    for (int i = 1; i <= n; ++i) cin >> p[i];

    Fenwick fw(n);
    for (int i = 1; i <= n; ++i) fw.add(i, 1); // all alive

    for (int i = 1; i <= n; ++i) {
        int k = p[i];
        int pos = fw.find_kth(k);     // original index of k-th alive
        cout << a[pos] << (i==n?'\n':' ');
        fw.add(pos, -1);              // remove it
    }
    return 0;
}
