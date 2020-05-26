#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

#define x first
#define y second
#define forn(i, n) for (int i = 0; i < int(n); i++)
#define fore(i, l, r) for (int i = int(l); i < int(r); i++)

const int N = 100;
const int INF = 1e9;

using piii = pair<pair<int, int>, int>;

piii a[N];

int n, k;

bool read() {
  if (scanf("%d%d", &n, &k) != 2) {
    return false;
  }
  forn(i, n) {
    scanf("%d%d", &a[i].x.x, &a[i].x.y);
    a[i].y = i;
  }
  return true;
}

int dp[N][N], p[N][N];

void solve() {
  sort(a, a + n, [](const piii &a, const piii &b) {
    if (a.x.y != b.x.y) {
      return a.x.y < b.x.y;
    }
    return a.x.x < b.x.x;
  });
  forn(i, n) { printf("%d %d %d\n", a[i].x.x, a[i].x.y, a[i].y); }
  forn(i, N) forn(j, N) dp[i][j] = -INF;
  dp[0][0] = 0;
  forn(i, n) forn(j, N) if (dp[i][j] >= 0) {
    if (dp[i + 1][j] < dp[i][j] + a[i].x.y * (k - 1)) {
      dp[i + 1][j] = dp[i][j] + a[i].x.y * (k - 1);
      p[i + 1][j] = j;
    }
    if (dp[i + 1][j + 1] < dp[i][j] + a[i].x.y * j + a[i].x.x) {
      dp[i + 1][j + 1] = dp[i][j] + a[i].x.y * j + a[i].x.x;
      p[i + 1][j + 1] = j;
    }
  }

  vector<int> ans[2];
  printf("n,k,dp[n][k]:%d,%d,%d\n", n, k, dp[n][k]);
  int current = k;
  for (int i = n; i > 0; i--) {
    if (p[i][current] == current) {
      ans[1].push_back(a[i - 1].second + 1);
    } else {
      ans[0].push_back(a[i - 1].second + 1);
    }
    current = p[i][current];
  }

  printf("%d\n", (int)ans[0].size() + (int)ans[1].size() * 2);
  for (int i = ans[0].size() - 1; i >= 0; i--) {
    printf("%d ", ans[0][i]);
  }
  for (auto x : ans[1]) {
    printf("%d %d ", x, -x);
  }
  printf("%d\n", ans[0].back());
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int tc;
  scanf("%d", &tc);
  while (tc--) {
    read();
    solve();
  }
  return 0;
}
