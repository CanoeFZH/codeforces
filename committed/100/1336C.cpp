#include <cstdio>
#include <cstring>

using namespace std;

const int MOD = 998244353;
const int N = 3025;

char s[N], t[N];

int dp[N][N], n, m;

bool equal(int i, int j) { return j > m || s[i] == t[j]; }

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif

  scanf("%s %s", s + 1, t + 1);
  n = strlen(s + 1);
  m = strlen(t + 1);

  for (int i = 0; i <= n; i++) {
    dp[i + 1][i] = 1;
  }

  for (int len = 1; len <= n; len++) {
    for (int l = 1; l + len - 1 <= n; l++) {
      int r = l + len - 1;
      if (equal(len, l)) {
        dp[l][r] = (dp[l][r] + dp[l + 1][r]) % MOD;
      }

      if (equal(len, r)) {
        dp[l][r] = (dp[l][r] + dp[l][r - 1]) % MOD;
      }
    }
  }

  int ans = 0;
  for (int i = m; i <= n; i++) {
    ans = (ans + dp[1][i]) % MOD;
  }
  printf("%d\n", ans);
  return 0;
}
