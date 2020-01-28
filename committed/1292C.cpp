#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

int n, root;

vector<vector<int> > tree, parent, subtree;
vector<vector<long long> > dp;

void dfs(int u) {
    subtree[root][u] = 1;
    for(auto &v: tree[u]) {
        if (v == parent[root][u]) {
            continue;
        }

        parent[root][v] = u;
        dfs(v);
        subtree[root][u] += subtree[root][v];
    }
}

long long getDP(int u, int v) {
    if (u == v) {
        return 0;
    }

    if (dp[u][v] != -1) {
        return dp[u][v];
    }
    
    long long res = subtree[u][v] * subtree[v][u] + max(getDP(parent[v][u], v), getDP(u, parent[u][v]));
    return dp[u][v] = res;
}

void input() {
    cin >> n;

    tree.assign(n, vector<int>());

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
}

void solve() {
    parent.assign(n, vector<int>(n, -1));
    subtree.assign(n, vector<int>(n, -1));
    for (int u = 0; u < n; u++) {
        root = u;
        dfs(u);
    }

    dp.assign(n, vector<long long>(n, -1LL));
    long long ans = 0;
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            ans = max(ans, getDP(u, v));
        }
    }

    cout << ans << endl;
}

int main() {
    input();
    solve();

    return 0;
}