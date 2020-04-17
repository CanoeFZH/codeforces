#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

long long ans;

long long f(int x) { return 1LL * x * x; }

void solve(const vector<int> &a, const vector<int> &b, const vector<int> &c) {
  for (auto x : a) {
    auto y = lower_bound(b.begin(), b.end(), x);
    auto z = upper_bound(c.begin(), c.end(), x);
    if (y == b.end() || z == c.begin()) {
      continue;
    }

    z--;
    ans = min(ans, f(x - *y) + f(x - *z) + f(*y - *z));
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t, nr, ng, nb;
  for (cin >> t; t; t--) {
    cin >> nr >> ng >> nb;
    vector<int> r(nr), g(ng), b(nb);
    for (int i = 0; i < nr; i++) {
      cin >> r[i];
    }

    for (int i = 0; i < ng; i++) {
      cin >> g[i];
    }

    for (int i = 0; i < nb; i++) {
      cin >> b[i];
    }

    sort(r.begin(), r.end());
    sort(g.begin(), g.end());
    sort(b.begin(), b.end());

    ans = 9e18;
    solve(r, g, b);
    solve(r, b, g);
    solve(g, r, b);
    solve(g, b, r);
    solve(b, r, g);
    solve(b, g, r);
    cout << ans << endl;
  }
  return 0;
}
