#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

const int N = 2e6 + 10;

int lps[N];

int KMP(const string& s) {
  int i = 0, j = -1, l = s.size();
  lps[0] = -1;

  while (i < l) {
    if (j == -1 || s[i] == s[j]) {
      i++, j++;
      lps[i] = j;
    } else {
      j = lps[j];
    }
  }

  return lps[l];
}

void solve() {
  string s;
  cin >> s;
  int l = 0, r = s.size() - 1;
  while (l < r && s[l] == s[r]) {
    l++, r--;
  }

  string header = s.substr(0, l);
  string tail = s.substr(r + 1);

  string middle = s.substr(l, r - l + 1);
  string middle_reverse = middle;
  reverse(middle_reverse.begin(), middle_reverse.end());

  string p = middle + "#" + middle_reverse;
  string q = middle_reverse + "#" + middle;

  p = p.substr(0, KMP(p));
  q = q.substr(0, KMP(q));

  if (p.size() < q.size()) {
    swap(p, q);
  }

  cout << header << p << tail << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
