#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int S = 26;
const int N = 2005;
const int INF = 2e9;

int n, suffix[2][S][N], dp[N][N];
string s, t;

int f(int i, int j) {
  if (j == 0) {
    return 0;
  }

  int &ans = dp[i][j];
  if (ans != -1) {
    return ans;
  }

  ans = INF;
  if (i > 0) {
    ans = 1 + f(i - 1, j);
    if (s[i - 1] == t[j - 1]) {
      ans = min(ans, f(i - 1, j - 1));
    }
  }

  int c = t[j - 1] - 'a';
  if (suffix[0][c][i + 1] > suffix[1][c][j + 1]) {
    ans = min(ans, f(i, j - 1));
  }
  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int tc;
  cin >> tc;
  while (tc--) {
    memset(dp, -1, sizeof(dp));
    memset(suffix, 0, sizeof(suffix));

    cin >> n >> s >> t;
    for (int i = n; i >= 1; i--) {
      for (int j = 0; j < S; j++) {
        suffix[0][j][i] = suffix[0][j][i + 1];
        suffix[1][j][i] = suffix[1][j][i + 1];
      }
      suffix[0][s[i - 1] - 'a'][i]++;
      suffix[1][t[i - 1] - 'a'][i]++;
    }

    int ans = f(n, n);
    if (ans >= INF) {
      ans = -1;
    }
    cout << ans << endl;
  }
  return 0;
}
