#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int N = 3e3;

vector<vector<int> > v;

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, k;
  string s;
  cin >> n >> k >> s;
  int sum = 0;
  while (1) {
    v.push_back({});
    for (int i = 0; i + 1 < n; i++) {
      if (s[i] == 'R' && s[i + 1] == 'L') {
        v.back().push_back(i);
        sum++;
      }
    }
    for (int i : v.back()) {
      swap(s[i], s[i + 1]);
    }

    if (v.back().empty()) {
      v.pop_back();
      break;
    }
  }

  if (k < v.size() || k > sum) {
    cout << -1 << "\n";
    return 0;
  }

  for (int i = 0; i < v.size(); i++) {
    while (v[i].size() > 1 && k > v.size()) {
      --k;
      cout << "1 " << v[i].back() + 1 << "\n";
      v[i].pop_back();
    }
    cout << v[i].size();
    for (int j : v[i]) {
      cout << " " << j + 1;
    }
    cout << "\n";
  }
  return 0;
}
