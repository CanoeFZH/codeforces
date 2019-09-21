#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int N = (int)2e5 + 123;

vector<int> g[N];
int n, m, a[N];
long long dp[N], answer, max_path;
bool loop[N], visited[N];

void dfs(int u, int fa) {
    visited[u] = true;
    dp[u] = a[u];
    for(auto v: g[u]) {
        if (v == fa) {
            continue;
        }

        if (visited[v]) {
            loop[u] = 1;
        } else {
            dfs(v, u);
            loop[u] |= loop[v];
            dp[u] = max(dp[u], dp[v] + a[u]);
        } 
    }

    if (loop[u]) {
        answer += a[u];
    } else {
        max_path = max(max_path, dp[u]);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[v].push_back(u);
        g[u].push_back(v);
    }

    int s;
    scanf("%d", &s);
    dfs(s, s);
    printf("%lld\n", answer + max_path);
    return 0;
}
