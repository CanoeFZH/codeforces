//#define _DEBUG
#ifdef _DEBUG
freopen("input", "r", stdin);
#endif
mt19937 rng(chrono::system_clock().now().time_since_epoch().count());
cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);

#include <bits/stdc++.h>

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iterator>
#include <random>
#include <set>

using namespace std;

// z[i] = len of lcp of s, s[i..]; lcp(longest common prefix)
vector<int> z_fn(const string& s) {
  int n = s.size();
  vector<int> z(n, 0);
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}
template <typename T = int>
struct Fenwick {
  int n;
  vector<T> v;

  Fenwick(int size = 100005) : n(size), v(n + 1, 0) {}
  inline void add(int p, T val) {
    for (; p <= n; p += (p & -p)) {
      v[p] += val;
    }
  }
  inline T query(int p) {
    T tmp = 0;
    for (; p > 0; p -= (p & -p)) {
      tmp += v[p];
    }
    return tmp;
  }
  inline T query(int l, int r) { return query(r) - query(l - 1); }
};
using ll = long long;
void solve() {
  int n, m;
  cin >> n >> m;
  string a, b, s;
  cin >> a >> b >> s;
  auto za = z_fn(s.substr(0, m - 1) + "#" + a);
  za = vector<int>(za.begin() + m, za.end());

  reverse(s.begin(), s.end());
  reverse(b.begin(), b.end());
  auto zb = z_fn(s.substr(0, m - 1) + "#" + b);
  zb = vector<int>(zb.begin() + m, zb.end());
  reverse(zb.begin(), zb.end());

  Fenwick<int> occur(m);
  Fenwick<ll> sum(m);
  ll res = 0;
  for (int i = 0, j = 0; i < n; i++) {
    while (j < n && j < i + m - 1) {
      int p = m - zb[j];
      occur.add(p, 1);
      sum.add(p, p);
      j++;
    }
    int p = za[i] + 1;
    res += p * 1ll * occur.query(p) - sum.query(p);

    p = m - zb[i];
    occur.add(p, -1);
    sum.add(p, -p);
  }
  cout << res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  solve();
  return 0;
}
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
pair<int, int> a[200020];
pair<int, int> b[200020];
pair<pair<int, int>, int> c[200020];
int n, m, p, ans = -2000000000;
int mx[800080], ad[800080];
void build(int k, int l, int r) {
  if (l == r) return mx[k] = -b[l].second, void();
  build(k << 1, l, l + r >> 1);
  build(k << 1 | 1, (l + r >> 1) + 1, r);
  mx[k] = max(mx[k << 1], mx[k << 1 | 1]);
}
inline void pushdown(int k) {
  ad[k << 1] += ad[k];
  ad[k << 1 | 1] += ad[k];
  mx[k << 1] += ad[k];
  mx[k << 1 | 1] += ad[k];
  ad[k] = 0;
}
void add(int k, int l, int r, int ll, int rr, int w) {
  if (l > rr || r < ll) return;
  if (l >= ll && r <= rr) {
    mx[k] += w;
    ad[k] += w;
    return;
  }
  if (ad[k]) pushdown(k);
  add(k << 1, l, l + r >> 1, ll, rr, w);
  add(k << 1 | 1, (l + r >> 1) + 1, r, ll, rr, w);
  mx[k] = max(mx[k << 1], mx[k << 1 | 1]);
}
int main() {
  scanf("%d %d %d", &n, &m, &p);
  for (int i = 1; i <= n; ++i) scanf("%d %d", &a[i].first, &a[i].second);
  for (int i = 1; i <= m; ++i) scanf("%d %d", &b[i].first, &b[i].second);
  for (int i = 1; i <= p; ++i)
    scanf("%d %d %d", &c[i].first.first, &c[i].first.second, &c[i].second);
  sort(a + 1, a + 1 + n);
  sort(b + 1, b + 1 + m);
  sort(c + 1, c + 1 + p);
  build(1, 1, m);
  //	printf("!!!");
  for (int i = 1, last = 1; i <= n; ++i) {
    while (last <= p && c[last].first.first < a[i].first) {
      int x = lower_bound(b + 1, b + 1 + m,
                          make_pair(c[last].first.second + 1, 0)) -
              b;
      if (x <= m) add(1, 1, m, x, m, c[last].second);
      ++last;
    }
    ans = max(ans, -a[i].second + mx[1]);
  }
  printf("%d", ans);
  return 0;
}
/*I highly dissuade hashing (multi)sets modulo a prime. Instead: assign random
64bit integer for each element, and use xor/sum of all elements as hash of the
whole set (xor if we are guaranteed there are no repetitions, or we do want
repetitions to cancel out, sum if we're hashing a multiset). To get those values
of each element I use following function: ull mix(ull o){ o+=0x9e3779b97f4a7c15;
    o=(o^(o>>30))*0xbf58476d1ce4e5b9;
    o=(o^(o>>27))*0x94d049bb133111eb;
    return o^(o>>31);
    //Those constants supposedly are chosen to give this function better
pseudo-random properties, but on any on-site contest, when one can't have team
reference document/doesn't want to waste time searching it for implementation
typing arbitrary large odd numbers by hand should be good enough
}
And value used for x is mix(x), or in case of rounds with hacking mix(x ^ salt),
where salt is value returned by
chrono::steady_clock::now().time_since_epoch().count() at the beginning of
runtime. This is way faster than anything using modulo, uses all 2^64 possible
hash values, so avoids any birthday paradox issues, also avoids any
overflows/issues with and requires way less code than using more than one
modulo. Moreover this technique can be used for hashing other objects than sets,
e.g. sequences, which can be represented as set of pairs (𝑖,𝑎𝑖)
(
i
,
a
i
)
, the only difference is that now we need random value for each pair, but this
can be easily done e.g. by ull hash(pii a) {return mix(a.first ^
mix(a.second));} And finally: using well-known modulos is not an issue, as long
as you use random number as base (guaranteed by Schwartz–Zippel lemma).
*/

while (clock() - st <= CLOCKS_PER_SEC * 4.5) {
  random_shuffle(u, u + X);
  int mx = 0;
  for (i = 0; i < X; i++) col[i] = 0;
  for (i = 0; i < X; i++) {
    int t = u[i];
    for (j = 1; j <= X; j++) tchk[j] = false;
    for (j = 0; j < X; j++)
      if (conn2[t][j]) tchk[col[j]] = true;
    for (j = 1;; j++)
      if (!tchk[j]) break;
    col[t] = j;
    mx = max(mx, j);
  }
  mn = min(mn, mx);
}

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#define pb push_back
using namespace std;
const int maxn = 510;
int n, a[maxn], cnt, dp[maxn], sta[maxn], top;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for (int i = 0; i <= n; i++) dp[i] = 1e9;
  dp[0] = 0;
  for (int i = 0; i < n; i++) {
    top = 0;
    for (int j = i + 1; j <= n; j++) {
      int v = a[j];
      while (top && sta[top] == v) {
        top--;
        v++;
      }
      sta[++top] = v;
      if (top == 1) dp[j] = min(dp[j], dp[i] + 1);
    }
  }
  printf("%d\n", dp[n]);
  return 0;
}

#include <bits/stdc++.h>
using namespace std;
const int N = 510;
int n, a[N], dp[N], x;
stack<int> s;
int main() {
  cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
  cin >> n;
  memset(dp, 0x3f, sizeof dp);
  dp[0] = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    while (!s.empty()) s.pop();
    for (int j = i; j; j--) {
      x = a[j];
      while (!s.empty() && x == s.top()) {
        s.pop();
        x++;
      }
      s.push(x);
      dp[i] = min(dp[i], dp[j - 1] + (int)s.size());
    }
  }
  cout << dp[n];
}

#include <stdio.h>
int f[100002][3], n, t, x, y, z;
inline int Max(int p, int q) { return p > q ? p : q; }
inline int Mex(int p, int q) { return p && q ? 0 : (p != 1 && q != 1 ? 1 : 2); }
inline int Mex(int p, int q, int r) {
  int mk[4] = {0, 0, 0, 0};
  mk[p] = mk[q] = mk[r] = 1;
  for (int i = 0; i < 4; i++)
    if (!mk[i]) return i;
}
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d%d", &n, &x, &y, &z);
    f[0][0] = f[0][1] = f[0][2] = 0;
    int d = (x + y) * (y + z) * (z + x);
    for (int i = 1; i <= d + d + d; i++) {
      int p = f[Max(i - x, 0)][0], q = f[Max(i - y, 0)][1],
          r = f[Max(i - z, 0)][2];
      f[i][0] = Mex(p, q, r);
      f[i][1] = Mex(p, r);
      f[i][2] = Mex(p, q);
    }
    int v = 0, s[4] = {0, 0, 0, 0};
    for (int i = 1; i <= n; i++) {
      long long p;
      scanf("%lld", &p);
      p = p > d + d ? p % d + d + d : p;
      int val = f[p][0], v0 = f[Max(p - x, 0)][0], v1 = f[Max(p - y, 0)][1],
          v2 = f[Max(p - z, 0)][2];
      v ^= val;
      s[val ^ v0]++;
      s[val ^ v1]++;
      s[val ^ v2]++;
    }
    printf("%d\n", s[v]);
  }
}

#include <bits/stdc++.h>

using namespace std;

#ifdef NeverBeRed
#include "debug.h"
#else
#define debug(...) 15
#endif
typedef long long ll;
typedef long double ld;
typedef complex<ll> point;
#define F first
#define S second

struct aho_corasick {
  static const int alpha = 14;

  vector<array<int, alpha>> go;
  vector<int> fail;
  vector<ll> endpos;

  aho_corasick() { add_node(); }

  int add_string(const string& str, int cost) {
    int e = 0;
    for (char c : str) {
      if (!go[e][c - 'a']) {
        int nn = add_node();
        go[e][c - 'a'] = nn;
      }
      e = go[e][c - 'a'];
    }
    endpos[e] += cost;
    return e;
  }

  void build() {
    queue<int> que;
    for (int c = 0; c < alpha; ++c)
      if (go[0][c]) que.push(go[0][c]);
    for (; !que.empty(); que.pop()) {
      int e = que.front();
      int f = fail[e];
      for (int c = 0; c < alpha; ++c)
        if (!go[e][c])
          go[e][c] = go[f][c];
        else {
          fail[go[e][c]] = go[f][c];
          endpos[go[e][c]] += endpos[go[f][c]];
          que.push(go[e][c]);
        }
    }
  }

 private:
  int add_node() {
    int pos = go.size();
    go.emplace_back(array<int, alpha>());
    fail.emplace_back(0);
    endpos.emplace_back(0);
    return pos;
  }
};

int main() {
#ifdef NeverBeRed
  // freopen("a.in", "r", stdin);
  // freopen("a.out", "w", stdout);
#endif

  ios_base::sync_with_stdio(0), cin.tie(0);

  int k;
  cin >> k;
  string s;
  aho_corasick ac;
  for (int i = 0, c; i < k; ++i) {
    cin >> s >> c;
    ac.add_string(s, c);
  }
  cin >> s;
  ac.build();

  vector<int> pos;
  for (auto& i : s)
    if (i == '?') pos.push_back(&i - &s[0]);

  int n = s.length();
  pos.push_back(n);
  vector<vector<pair<int, ll>>> cost(pos.size(),
                                     vector<pair<int, ll>>(ac.go.size()));
  int last = 0;
  for (size_t i = 0; i < pos.size(); ++i) {
    for (size_t j = 0; j < ac.go.size(); ++j) {
      int nod = j, u = last;
      ll v = 0;
      while (u < pos[i]) {
        nod = ac.go[nod][s[u] - 'a'];
        v += ac.endpos[nod];
        ++u;
      }
      cost[i][j] = {nod, v};
    }
    last = pos[i] + 1;
  }

  int sz = 14;
  ll ans = numeric_limits<ll>::min() / 2;
  vector<vector<ll>> dp(1 << sz, vector<ll>(ac.go.size(), ans));
  dp[0][cost[0][0].F] = cost[0][0].S;
  for (int j = 0; j < 1 << sz; ++j) {
    int bp = __builtin_popcount(j) + 1;
    if (bp >= pos.size()) {
      ans = max(ans, *max_element(dp[j].begin(), dp[j].end()));
      continue;
    }
    for (int k = 0; k < sz; ++k)
      if (~j >> k & 1)
        for (size_t i = 0; i < ac.go.size(); ++i) {
          int u = i;
          ll v = dp[j][i];
          u = ac.go[u][k];
          v += ac.endpos[u];
          if (pos[bp] > 0 && s[pos[bp] - 1] != '?')
            v += cost[bp][u].S, u = cost[bp][u].F;
          dp[j | 1 << k][u] = max(dp[j | 1 << k][u], v);
        }
  }
  cout << ans << "\n";

  return 0;
}

#include <bits/stdc++.h>
#define rep(i, x, y) for (auto i = (x); i <= (y); ++i)
#define dep(i, x, y) for (auto i = (x); i >= (y); --i)
#define fr first
#define sc second
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
const int M = 1010;
const ll inf = 1e18;
const int mo = 998244353;
char s[N];
int p[14][M], f[M], t[M];
ll dp[M][1 << 14], w[M], a[M];
int main() {
  int n, m, tot = 0;
  scanf("%d", &n);
  rep(i, 1, n) {
    int W;
    scanf("%s%d", s + 1, &W);
    m = strlen(s + 1);
    int x = 0;
    rep(j, 1, m) {
      int c = s[j] - 'a';
      if (!p[c][x]) p[c][x] = ++tot;
      x = p[c][x];
    }
    w[x] += W;
  }
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    rep(i, 0, 13) if (p[i][x]) {
      f[p[i][x]] = x ? p[i][f[x]] : 0;
      w[p[i][x]] += w[f[p[i][x]]];
      q.push(p[i][x]);
    }
    else p[i][x] = p[i][f[x]];
  }
  scanf("%s", s + 1);
  m = strlen(s + 1);
  rep(j, 0, tot) rep(k, 0, (1 << 14) - 1) dp[j][k] = -inf;
  dp[0][0] = 0;
  rep(j, 0, tot) t[j] = j;
  rep(i, 1, m) if (s[i] == '?') {
    dep(k, (1 << 14) - 1, 0) rep(j, 0, tot) if (dp[j][k] != -inf) {
      rep(l, 0, 13) if (!((1 << l) & k)) {
        int jj = p[l][t[j]], kk = k ^ (1 << l);
        dp[jj][kk] = max(dp[jj][kk], dp[j][k] + a[j] + w[jj]);
      }
      dp[j][k] = -inf;
    }
    rep(j, 0, tot) t[j] = j, a[j] = 0;
  }
  else rep(j, 0, tot) {
    t[j] = p[s[i] - 'a'][t[j]];
    a[j] += w[t[j]];
  }
  ll ans = -inf;
  rep(j, 0, tot) rep(k, 0, (1 << 14) - 1) ans = max(ans, dp[j][k] + a[j]);
  printf("%lld\n", ans);
}