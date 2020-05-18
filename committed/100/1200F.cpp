#include <cstdlib>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

const int N = 1024;
const int M = 2521;
const int MOD = 2520;

vector<int> E[N];
int k[N], ans[N][M], n;
bool visit[N][M];
pair<int, int> pre[N][M];

int dfs(int u, int value) {
    if (ans[u][value]) {
        return ans[u][value];
    }

    visit[u][value] = true;
    int next = (value + k[u]) % MOD;
    int v = E[u][next % E[u].size()];
    if (ans[v][next]) {
        return ans[u][value] = ans[v][next];
    }

    if (!visit[v][next]) {
        pre[v][next] = make_pair(u, value);
        return ans[u][value] = dfs(v, next);
    } else {
        set <int> s;
        pair<int, int> now = make_pair(u, value);
        while(now != make_pair(v, next)) {
            s.insert(now.first);
            now = pre[now.first][now.second];
        }

        s.insert(now.first);
        return ans[u][value] = s.size();
    }
}

int main() {

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &k[i]);
        k[i] = (k[i] % MOD + MOD) % MOD;
    }

    for (int i = 1; i <= n; i++) {
        int t;
        scanf("%d", &t);
        for (int j = 1; j <= t; j++) {
            int v;
            scanf("%d", &v);
            E[i].push_back(v);
        }
    }

    int q;
    scanf("%d", &q);
    while(q--) {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", dfs(x, (y % MOD + MOD) % MOD));
    }
    return 0;
}

