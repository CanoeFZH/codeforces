#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int N = 2e5 + 5;
const int INF = 2e9;

using pii = pair<int, int>;

int a[N], b[N], c[N];
long long cost = 0;
vector<int> E[N];

pii dfs(int u, int p, int p_min) {
  pii digit_count = {0, 0};
  if (b[u] != c[u]) {
    digit_count.first += b[u];
    digit_count.second += c[u];
  }

  for (auto v : E[u]) {
    if (v == p) {
      continue;
    }

    pii son_digit_count = dfs(v, u, min(p_min, a[u]));
    digit_count.first += son_digit_count.first;
    digit_count.second += son_digit_count.second;
  }

  if (a[u] < p_min) {
    int change = min(digit_count.first, digit_count.second);
    cost += 2LL * change * a[u];
    digit_count.first -= change;
    digit_count.second -= change;
  }

  return digit_count;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i] >> c[i];
  }

  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    E[u].push_back(v);
    E[v].push_back(u);
  }

  pii answer = dfs(1, 0, INF);
  if (answer.first || answer.second) {
    cout << -1 << endl;
  } else {
    cout << cost << endl;
  }
  return 0;
}
