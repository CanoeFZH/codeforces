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

const int N = (1 << 11) + 5;

int p[N];

int query(int i, int j) {
	printf("? %d %d\n", i, j);
	fflush(stdout);
	int ans;
	scanf("%d", &ans);
	return ans;
}


int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  int n;
  scanf("%d", &n);
  vector<int> d;

  for(int i = 1; i <= n; i++) {
	  d.push_back(i);
  }

  shuffle(d.begin(), d.end(), rng);

  int a = d[0], b = d[1];
  int previous = query(a, b);

  for (int i = 2; i < n; i++) {
	  int current = query(b, d[i]);
	  if (current < previous) {
		  a = d[i];
		  previous = current;
	  } else if (current == previous) {
		  b = d[i];
		  previous = query(a, b);
	  }
  }

  int zero_index;
  while(1) {
	  int i = uniform_int_distribution<int>(1, n)(rng);
	  if (i == a || i == b) {
		  continue;
	  }

	  int v1 = query(i, a);
	  int v2 = query(i, b);
	  if (v1 != v2) {
		  zero_index = v1 < v2 ? a : b;
		  break;
	  } 
  }

  for (int i = 1; i <= n; i++) {
	  if (i != zero_index) {
		  p[i] = query(i, zero_index);
	  }
  }

  printf("!");
  for (int i = 1; i <= n; i++) {
	  printf(" %d", p[i]);
  }
  printf("\n");
  fflush(stdout);
  return 0;
}
