#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// shuffle(d.begin(), d.end(), rng);
// int i = uniform_int_distribution<int>(1, n)(rng);
//

const int N = 200020;

int cnt[2];

vector<int> E[N];

void dfs(int u, int p, int c) {
  cnt[c]++;
  for (int v : E[u]) {
    if (v != p) {
      dfs(v, u, c ^ 1);
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

  int n;

  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    E[u].push_back(v);
    E[v].push_back(u);
  }

  dfs(1, 1, 0);
  cout << min(cnt[0], cnt[1]) - 1 << endl;

  return 0;
}
