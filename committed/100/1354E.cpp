#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int N = 5e3 + 7;

int n, m, a[3], total[2], c[N], res[N], dp[N][N];
bool exist;
vector<int> E[N];
vector<vector<int>> path[2];

bool read() {
  if (!(cin >> n >> m)) {
    return false;
  }
  for (int i = 0; i < 3; i++) {
    cin >> a[i];
  }

  for (int i = 0; i < n; i++) {
    E[i].clear();
  }

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    E[u].push_back(v);
    E[v].push_back(u);
  }

  return true;
}

void dfs(int u) {
  for (int i = 0; i < 2; i++) {
    total[i] += c[u] == i;
  }

  path[c[u]].back().push_back(u);

  for (auto v : E[u]) {
    if (c[v] == -1) {
      c[v] = c[u] ^ 1;
      dfs(v);
    } else if (c[u] == c[v]) {
      exist = false;
    }
  }
}

void solve() {
  vector<pair<int, int>> cc_size;
  memset(c, -1, sizeof(c));

  path[0].clear();
  path[1].clear();
  for (int i = 0; i < n; i++) {
    if (c[i] == -1) {
      memset(total, 0, sizeof(total));
      c[i] = 0;
      exist = true;
      path[0].push_back(vector<int>());
      path[1].push_back(vector<int>());
      dfs(i);

      if (!exist) {
        cout << "NO" << endl;
        return;
      }
      cc_size.push_back(make_pair(total[0], total[1]));
    }
  }

  memset(dp, -1, sizeof(dp));
  dp[0][0] = 0;
  int cc = cc_size.size();
  for (int i = 0; i < cc; i++) {
    for (int j = 0; j < N; j++) {
      if (dp[i][j] != -1) {
        dp[i + 1][j + cc_size[i].first] = 0;
        dp[i + 1][j + cc_size[i].second] = 1;
      }
    }
  }

  if (dp[cc][a[1]] == -1) {
    cout << "NO" << endl;
    return;
  }

  cout << "YES" << endl;

  memset(res, -1, sizeof(res));
  for (int i = cc; i > 0; i--) {
    for (auto it : path[dp[i][a[1]]][i - 1]) {
      res[it] = 2;
    }
    a[1] -= path[dp[i][a[1]]][i - 1].size();
  }
  for (int i = 0; i < n; i++) {
    if (res[i] == -1) {
      if (a[0] > 0) {
        res[i] = 1;
        --a[0];
      } else {
        res[i] = 3;
        --a[2];
      }
    }
  }

  for (int i = 0; i < n; i++) {
    cout << res[i];
  }
  cout << endl;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  while (read()) {
    solve();
  }
  return 0;
}
