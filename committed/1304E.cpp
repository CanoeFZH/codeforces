#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

const int N = 1e5 + 10;
const int B = 17;

vector<int> E[N];
int f[N][B + 1], h[N];

void dfs(int u) {
    for(auto v: E[u]) {
        if(v != f[u][0]) {
            f[v][0] = u;
            h[v] = h[u] + 1;
            dfs(v);
        }
    }
}

int LCA(int u, int v) {
    if (h[u] < h[v]) {
        swap(u, v);
    }
    for (int i = B; i >= 0; i--) {
        if ((h[u] - h[v]) >> i) {
            u = f[u][i];
        }
    }
    if (u == v) {
        return u;
    }

    for (int i = B; i >= 0; i--) {
        if (f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }
    return f[u][0];
}

int d(int u, int v) {
    return h[u] + h[v] - 2 * h[LCA(u, v)];
}

bool condition_matched(int du, int dv) {
    return du <= dv && du % 2 == dv % 2;
}

bool condition_matched(int u, int v, int a, int b, int k) {
    return condition_matched(d(a, b), k) ||
           condition_matched(d(a, u) + d(b, v) + 1, k) ||
           condition_matched(d(a, v) + d(b, u) + 1, k);
}

int main() {
    int n, q;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs(1);

    for(int i = 1; i <= B; i++) {
        for (int j = 1; j <= n; j++) {
            f[j][i] = f[f[j][i - 1]][i - 1];
        }
    }

    for(scanf("%d", &q); q; q--) {
        int x, y, a, b, k;
        scanf("%d%d%d%d%d", &x, &y, &a, &b, &k);
        printf("%s\n", condition_matched(x, y, a, b, k) ? "YES" : "NO");
    }
    return 0;
}