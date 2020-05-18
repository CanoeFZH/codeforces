#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int S = 1 << 14;
const int N = 14;

typedef long long ll;

vector<ll> f[S][N];
string a[N];
ll ans[S];

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for (int i = 0; i < 1 << n; i++) {
    for (int j = 0; j < n; j++) {
      if (i >> j & 1) {
        f[i][j].resize(1 << (__builtin_popcount(i) - 1));
      }
    }
  }
  for (int i = 0; i < n; i++) {
    f[1 << i][i][0] = 1;
  }

  for (int i = 0; i < 1 << n; i++) {
    int s = __builtin_popcount(i) - 1;
    for (int j = 0; j < n; j++) {
      if (i >> j & 1) {
        for (int k = 0; k < f[i][j].size(); k++) {
          for (int x = 0; x < n; x++) {
            if (!(i >> x & 1)) {
              f[i | 1 << x][x][k | (a[j][x] == '1') << s] += f[i][j][k];
            }
          }
          if (i == (1 << n) - 1) {
            ans[k] += f[i][j][k];
          }
        }
      }
    }
  }

  for (int i = 0; i < 1 << (n - 1); i++) {
    cout << ans[i] << " ";
  }
  cout << "\n";
  return 0;
}