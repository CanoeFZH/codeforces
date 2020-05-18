#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int N = 1e5 + 5;

vector<int> E[N];

int leaf_count[2], leaf[N], ans[2];

void dfs(int u, int f, int d) {
  if (E[u].size() == 1) {
    leaf_count[d] = 1;
  }
  int u_leaf_count = 0;
  for (auto v : E[u]) {
    if (v != f) {
      dfs(v, u, d ^ 1);
      u_leaf_count += E[v].size() == 1;
    }
  }
  ans[1] -= max(0, u_leaf_count - 1);
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, u, v;
  cin >> n;

  for (int i = 1; i < n; i++) {
    cin >> u >> v;
    E[u].push_back(v);
    E[v].push_back(u);
  }

  ans[1] = n - 1;
  for (int i = 1; i <= n; i++) {
    if (E[i].size() > 1) {
      dfs(i, 0, 0);
      break;
    }
  }

  ans[0] = leaf_count[0] && leaf_count[1] ? 3 : 1;

  printf("%d %d\n", ans[0], ans[1]);
  return 0;
}