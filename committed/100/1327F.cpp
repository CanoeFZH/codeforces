#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <numeric>

using namespace std;

const int N = 500005;
const int MOD = 998244353;

int n, k, m, l[N], r[N], x[N];
int one[N], last[N], dp[N], sum[N];

int solve(int b) {
  fill_n(one, n + 2, 0);
  fill_n(last, n + 1, 0);

  for (int i = 1; i <= m; i++) {
    if ((x[i] >> b) & 1) {
      one[l[i]]++;
      one[r[i] + 1]--;
    } else {
      last[r[i]] = max(last[r[i]], l[i]);
    }
  }

  partial_sum(one, one + n + 2, one);
  partial_sum(last, last + n + 1, last, [](int a, int b) { return max(a, b); });

  dp[0] = sum[0] = 1;

  for (int i = 1; i <= n + 1; i++) {
    if (!one[i]) {
      dp[i] =
          (sum[i - 1] - (last[i - 1] == 0 ? 0 : sum[last[i - 1] - 1]) + MOD) %
          MOD;
    } else {
      dp[i] = 0;
    }
    sum[i] = (sum[i - 1] + dp[i]) % MOD;
  }
  return dp[n + 1];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  scanf("%d %d %d", &n, &k, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d %d %d", &l[i], &r[i], &x[i]);
  }

  int ans = 1;
  for (int i = 0; i < k; i++) {
    ans = ans * 1LL * solve(i) % MOD;
  }
  printf("%d\n", ans);
  return 0;
}