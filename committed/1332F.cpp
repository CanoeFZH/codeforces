#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int N = 300007;
const int MOD = 998244353;

long long dp[N][2], f[N];

vector<int> E[N];

long long multiply(long long u, long long v) {
  u = (u % MOD + MOD) % MOD;
  v = (v % MOD + MOD) % MOD;
  return u * v % MOD;
}

void dfs(int u, int p) {
  dp[u][0] = dp[u][1] = f[u] = 1;
  for (auto v : E[u]) {
    if (v == p) {
      continue;
    }

    dfs(v, u);

    dp[u][0] = multiply(dp[u][0], 2 * dp[v][1] + 2 * dp[v][0] - f[v]);
    dp[u][1] = multiply(dp[u][1], dp[v][1] + 2 * dp[v][0] - f[v]);
    f[u] = multiply(f[u], dp[v][0] + dp[v][1] - f[v]);
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  int n;
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    E[u].push_back(v);
    E[v].push_back(u);
  }

  dfs(1, 0);
  cout << (dp[1][0] + dp[1][1] - f[1] - 1 + 2 * MOD) % MOD << endl;
  return 0;
}