#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 500005;

int a[N];

bool solve() {
  int n, k;
  cin >> n >> k;
  bool flag = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] < k) {
      a[i] = 0;
    } else if (a[i] > k) {
      a[i] = 2;
    } else {
      a[i] = 1;
      flag = 1;
    }
  }

  if (!flag) {
    return false;
  }
  if (n == 1) {
    return true;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n && j - i <= 2; j++) {
      if (a[i] && a[j]) {
        return true;
      }
    }
  }
  return false;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    printf("%s\n", solve() ? "YES" : "NO");
  }
  return 0;
}