#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const int N = 1005;

int a[N][N], f[N][N];
bool vis[N][N];
int n, m, T;

int dn[] = {-1, 0, 1, 0};
int dm[] = {0, -1, 0, 1};

bool check(int i, int j) {
  for (int t = 0; t < 4; t++) {
    if (a[i + dn[t]][j + dm[t]] == a[i][j]) {
      return true;
    }
  }
  return false;
}

void bfs() {
  queue<pair<int, int> > q;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (check(i, j)) {
        f[i][j] = 0;
        vis[i][j] = true;
        q.push(make_pair(i, j));
      }
    }
  }

  while (!q.empty()) {
    pair<int, int> u = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      int vn = u.first + dn[i];
      int vm = u.second + dm[i];
      if (vn < 1 || vn > n || vm < 1 || vm > m || vis[vn][vm]) {
        continue;
      }

      f[vn][vm] = f[u.first][u.second] + 1;
      vis[vn][vm] = true;
      q.push(make_pair(vn, vm));
    }
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> n >> m >> T;
  string s;
  memset(a, -1, sizeof(a));
  for (int i = 1; i <= n; i++) {
    cin >> s;
    for (int j = 1; j <= m; j++) {
      a[i][j] = s[j - 1] - '0';
    }
  }
  bfs();
  int x, y;
  long long t;
  while (T--) {
    cin >> x >> y >> t;
    if (vis[x][y]) {
      printf("%d\n", a[x][y] ^ (int)(max(0LL, t - f[x][y]) & 1));
    } else {
      printf("%d\n", a[x][y]);
    }
  }
  return 0;
}
