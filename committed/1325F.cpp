#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

const int N = 1e5 + 5;

vector<int> E[N], s;
int k, c[N], d[N];

void dfs(int u) {
  s.push_back(u);
  d[u] = s.size();
  for (auto v : E[u]) {
    if (!d[v]) {
      dfs(v);
    } else if (d[u] - d[v] + 1 >= k) {
      printf("2\n%d\n", d[u] - d[v] + 1);
      for (int x = d[v] - 1; x < d[u]; x++) {
        printf("%d ", s[x]);
      }
      exit(0);
    }
  }
  if (!c[u]) {
    for (auto v : E[u]) {
      c[v] = 1;
    }
  }
  s.pop_back();
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  int n, m;
  scanf("%d%d", &n, &m);

  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    E[u].push_back(v);
    E[v].push_back(u);
  }

  k = 0;
  while (k * k < n) {
    k++;
  }

  dfs(1);

  puts("1");
  for (int i = 1; k; i++) {
    if (!c[i]) {
      printf("%d ", i);
      k--;
    }
  }
  return 0;
}