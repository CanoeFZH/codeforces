#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

using lint = long long;

const lint INF = (lint)2e18 + 77;
const int N = 100100;

int n;
lint h[N], sum[N], A, R, M;

lint solve(lint x) {
  int pos = lower_bound(h, h + n, x) - h;
  lint res = 0;
  lint P = x * pos - sum[pos];
  lint Q = sum[n] - sum[pos] - x * (n - pos);
  res = min(P, Q);
  P -= res;
  Q -= res;
  res *= M;
  res += P * A;
  res += Q * R;
  return res;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> A >> R >> M;
  M = min(M, A + R);
  for (int i = 0; i < n; i++) {
    cin >> h[i];
  }

  sort(h, h + n);

  for (int i = 0; i < n; i++) {
    sum[i + 1] = sum[i] + h[i];
  }
  lint ans = INF;
  ans = min(ans, solve(sum[n] / n));
  ans = min(ans, solve(sum[n] / n + 1));
  for (int i = 0; i < n; i++) {
    ans = min(ans, solve(h[i]));
  }
  cout << ans << endl;
  return 0;
}
