#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std; 

const int N = 4e5 + 10;
const int OO = 1e9;
const int B = 18;

int depth[N], f[N], s[N], d[N], jump[B + 1][N];
vector<int> E[N];

void add_edge(int u, int v) {
    E[u].push_back(v);
    E[v].push_back(u);
}

int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}

void dfs(int u, int p = 0) {
    for(auto &v: E[u]) {
        if (v == p) {
            continue;
        }
        depth[v] = depth[u] + 1;
        jump[0][v] = u;
        for (int i = 1; i <= B; i++) {
            jump[i][v] = jump[i - 1][jump[i - 1][v]];
        }
        dfs(v, u);
    }
}

int la(int u, int x) {
    for(int i = B; ~i; i--) {
        if ((x >> i) & 1) {
            u = jump[i][u];
        }
    }
    return u;
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    u = la(u, depth[u] - depth[v]);
    if (u == v) {
        return u;
    }

    for(int i = B; ~i; i--) {
        if (jump[i][u] != jump[i][v]) {
            u = jump[i][u];
            v = jump[i][v];
        }
    }

    return jump[0][u];
}

int walk(int u, int v, int k) {
    int c = lca(u, v);
    if (k <= depth[u] - depth[c]) {
        return la(u, k);
    }

    int excess = k - (depth[u] - depth[c]);
    return la(v, depth[v] - depth[c] - excess);
}

bool query(int u, int v, int k) {
    if (depth[u] + depth[v] - 2 * depth[lca(u, v)] <= 2 * k) {
        return true;
    }

    return find(walk(u, v, k)) == find(walk(v, u, k));
}

int main() {
    int n, k, r;
    scanf("%d %d %d", &n, &k, &r);
    for(int i = 1, u, v; i < n; i++) {
        scanf("%d %d", &u, &v);
        add_edge(u, i + n);
        add_edge(v, i + n);
    }

    for (int i = 1; i < 2 * n; i++) {
        f[i] = i;
    }

    fill(d, d + 2 * n, +OO);
    queue<int> Q;
    for (int i = 1, x; i <= r; i++) {
        scanf("%d", &x);
        d[x] = 0;
        Q.push(x);
    }
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        if (d[u] == k) {
            break;
        }
        for(auto &v: E[u]) {
            f[find(v)] = find(u);
            if (d[v] == +OO) {
                d[v] = d[u] + 1;
                Q.push(v);
            }
        }
    }

    dfs(1);
    int u, v, q;
    for(scanf("%d", &q); q; q--) {
        scanf("%d %d", &u, &v);
        puts(query(u, v, k) ? "YES" : "NO");
    }
    return 0;
}