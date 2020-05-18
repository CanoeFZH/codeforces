#include <bits/stdc++.h>

using namespace std;

typedef pair <int, int> pii;

const int N = 200010;

vector<pii> G[N];
int deg[N], color[N];
int r;

int nextColor(int x) {
    return x % r + 1;
}

void dfs(int u, int f, int c) {
    for(auto p: G[u]) {
        int v = p.first;
        if (v == f) continue;
        int e = p.second;
        c = nextColor(c);
        color[e] = c;
        dfs(v, u, c);
    }
}

int main() {
    int n, k, u, v;
    cin >> n >> k;
    memset(deg, 0, sizeof(deg));

    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        G[u].push_back({v, i});
        G[v].push_back({u, i});
        deg[u]++, deg[v]++;
    }

    sort(deg + 1, deg + n + 1);
    r = deg[n - k];
    dfs(1, 0, 0);
    cout << r << endl;
    for (int i = 1; i < n; i++) {
        cout << color[i] << " ";
    }
    cout << endl;
    return 0;
}