#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//shuffle(d.begin(), d.end(), rng);
//int i = uniform_int_distribution<int>(1, n)(rng);
//
int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  return 0;
}
