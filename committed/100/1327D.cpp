#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 2e5 + 5;

int p[N], c[N], a[N];
bool vis[N];

bool check(int n, int m) {
  for (int i = 1; i <= m; i++) {
    bool flag = false;
    for (int j = i; j <= n; j += m) {
      if (c[a[j]] != c[a[i]]) {
        flag = true;
        break;
      }
    }
    if (!flag) {
      return true;
    }
  }

  return false;
}

int solve(int n) {
  int ans = n;
  for (int i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      if (check(n, i)) {
        ans = min(ans, i);
      }

      if (check(n, n / i)) {
        ans = min(ans, n / i);
      }
    }
  }
  return ans;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif

  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &p[i]);
      vis[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
      scanf("%d", &c[i]);
    }

    int ans = n;
    for (int i = 1; i <= n; i++) {
      if (!vis[i]) {
        int tot = 0, x = i;
        while (!vis[x]) {
          a[++tot] = x;
          vis[x] = 1;
          x = p[x];
        }

        ans = min(ans, solve(tot));
      }
    }

    printf("%d\n", ans);
  }
}