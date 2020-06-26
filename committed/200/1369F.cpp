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
using pii = pair<int, int>;
using lint = long long;

const int N = 1e5 + 7;

pii c[N];

int win(lint s, lint e) {
  if (e == s) {
    return 0;
  }
  if (e == s + 1) {
    return 1;
  }

  if (e & 1) {
    return 1 - (s & 1);
  }

  if (s <= e / 4) {
    return win(s, e / 4);
  }

  if (s > (e / 4) * 2) {
    return ((e - s) & 1);
  }

  return 1;
}

int lose(lint s, lint e) {
  if (s * 2 > e) {
    return 1;
  }

  lint w = e / 2 + 3;
  while (w * 2 > e) {
    w--;
  }

  return win(s, w);
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
  for (int i = 0; i < n; i++) {
    lint s, e;
    cin >> s >> e;
    c[i] = {win(s, e), lose(s, e)};
  }

  int w = 0, l = 1;
  for (int i = 0; i < n; i++) {
    if (w == l) {
      break;
    }
    if (w == 1) {
      c[i].first ^= 1;
      c[i].second ^= 1;
    }

    w = c[i].first;
    l = c[i].second;
  }

  cout << w << " " << l << endl;
  return 0;
}
