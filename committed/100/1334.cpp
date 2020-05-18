#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int N = 1000;
const long long MOD = 998244353;

vector<long long> primes;
long long f[N], inv[N];

long long gcd(long long a, long long b) { return a == 0 ? b : gcd(b % a, a); }

long long quick_power(long long a, long long x, long long mod = MOD) {
  long long acc = 1;
  while (x) {
    if (x & 1) {
      acc = acc * a % mod;
    }
    a = a * a % mod;
    x >>= 1;
  }
  return acc;
}

long long solve(long long n) {
  long long acc = 1;
  int s = 0;
  for (auto p : primes) {
    int count = 0;
    while (n % p == 0) {
      count++;
      n /= p;
    }
    s += count;
    acc = acc * inv[count] % MOD;
  }

  acc = acc * f[s] % MOD;
  return acc;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  f[0] = inv[0] = 1;
  for (int i = 1; i < N; i++) {
    f[i] = f[i - 1] * i % MOD;
    inv[i] = inv[i - 1] * quick_power(i, MOD - 2) % MOD;
  }

  long long d;
  cin >> d;
  for (long long i = 2; i * i <= d; i++) {
    if (d % i == 0) {
      primes.push_back(i);
      while (d % i == 0) {
        d /= i;
      }
    }
  }

  if (d != 1) {
    primes.push_back(d);
  }

  int t;
  cin >> t;
  while (t--) {
    long long u, v;
    cin >> u >> v;
    long long g = gcd(u, v);
    u /= g, v /= g;
    cout << solve(u) * solve(v) % MOD << "\n";
  }
}
