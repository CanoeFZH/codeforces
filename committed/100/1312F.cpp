#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

const int N = 300043;
const int K = 5;

int x, y, z, n, cnt, peroid;
long long a[N];

typedef vector<vector<int>> state;

state state_log;
map<state, int> d;

int mex(const vector<int> &a) {
  for (int i = 0; i < a.size(); i++) {
    bool f = false;
    for (auto x : a) {
      if (x == i) {
        f = true;
        break;
      }
    }

    if (!f) {
      return i;
    }
  }

  return a.size();
}

state go(const state &s) {
  int f1 = mex({s[0][K - x], s[1][K - y], s[2][K - z]});
  int f2 = mex({s[0][K - x], s[2][K - z]});
  int f3 = mex({s[0][K - x], s[1][K - y]});

  state ns = s;
  ns[0].push_back(f1);
  ns[1].push_back(f2);
  ns[2].push_back(f3);

  for (int i = 0; i < 3; i++) {
    ns[i].erase(ns[i].begin());
  }

  return ns;
}

void init() {
  d.clear();
  state current(3, vector<int>(K, 0));
  cnt = 0;
  state_log.clear();

  while (!d.count(current)) {
    d[current] = cnt;
    state_log.push_back(
        {current[0].back(), current[1].back(), current[2].back()});

    current = go(current);
    cnt++;
  }

  peroid = cnt - d[current];
}

int get_sg(long long x, int t) {
  if (x < cnt) {
    return state_log[x][t];
  }

  int head = cnt - peroid;
  return state_log[head + (x - head) % peroid][t];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  int t;
  for (scanf("%d", &t); t; t--) {
    scanf("%d%d%d%d", &n, &x, &y, &z);
    for (int i = 0; i < n; i++) {
      scanf("%lld", &a[i]);
    }

    init();

    int ans = 0;
    for (int i = 0; i < n; i++) {
      ans ^= get_sg(a[i], 0);
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
      ans ^= get_sg(a[i], 0);
      res += get_sg(max(a[i] - x, 0LL), 0) == ans;
      res += get_sg(max(a[i] - y, 0LL), 1) == ans;
      res += get_sg(max(a[i] - z, 0LL), 2) == ans;
      ans ^= get_sg(a[i], 0);
    }
    printf("%d\n", res);
  }
  return 0;
}