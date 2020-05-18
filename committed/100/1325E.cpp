#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int INF = 1e9;
const int N = 1e6 + 10;

vector<int> E[N];

vector<int> get_primes(int x) {
  vector<int> primes;
  for (int i = 2; i * i <= x; i++) {
    int cnt = 0;
    while (x % i == 0) {
      x /= i;
      cnt++;
    }

    if (cnt & 1) {
      primes.push_back(i);
    }
  }

  if (x > 1) {
    primes.push_back(x);
  }
  return primes;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  int n, a, ans = INF;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a);
    auto primes = get_primes(a);

    if (primes.size() == 0) {
      ans = 1;
    } else {
      if (primes.size() == 1) {
        primes.push_back(1);
      }
      int u = primes[0], v = primes[1];
      E[u].push_back(v);
      E[v].push_back(u);
    }
  }

  vector<int> d(N, INF);

  for (int s = 0; s * s <= N; s++) {
    if (!E[s].size()) {
      continue;
    }

    fill(d.begin(), d.end(), INF);
    d[s] = 0;
    queue<pair<int, int>> q;
    q.emplace(s, -1);

    while (!q.empty()) {
      int u = q.front().first, p = q.front().second;
      q.pop();
      for (auto v : E[u]) {
        if (v == p) {
          continue;
        }
        if (d[v] == INF) {
          d[v] = d[u] + 1;
          q.emplace(v, u);
        } else {
          ans = min(d[v] + d[u] + 1, ans);
        }
      }
    }
  }

  printf("%d\n", ans == INF ? -1 : ans);
  return 0;
}