#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int INF = 1e9;
const int N = 10010;

int dp[N][N], nxt[N];
string s, t;

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> s >> t;
  int n = s.size();
  int m = t.size();

  for (int i = 0; i < n; i++) {
    if (s[i] != '.') {
      int brackets = 0;
      nxt[i] = -1;
      for (int j = i; j < n; j++) {
        if (s[j] == '.') {
          brackets--;
        } else {
          brackets++;
        }
        if (brackets == 0) {
          nxt[i] = j;
          break;
        }
      }
    }
  }

  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      dp[i][j] = INF;
    }
  }

  dp[0][0] = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= m; j++) {
      dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
      if (j < m && s[i] == t[j]) {
        dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j]);
      }
      if (s[i] != '.' && nxt[i] != -1) {
        dp[nxt[i] + 1][j] = min(dp[nxt[i] + 1][j], dp[i][j]);
      }
    }
  }

  cout << dp[n][m] << endl;
  return 0;
}
