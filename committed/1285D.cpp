#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector <int> a;

int solve(vector <int> & full_set, int bit) {
	if (a.size() == 0 || bit < 0 ) {
		return 0;
	}

	vector <int> on, off;
	for (auto &e: full_set) {
		if (((e >> bit) & 1) == 0) {
			off.push_back(e);
		} else {
			on.push_back(e);
		}
	}

	if (on.size() == 0) {
		return solve(off, bit - 1);
	}

	if (off.size() == 0) {
		return solve(on, bit - 1);
	}

	return min(solve(off, bit - 1), solve(on, bit - 1)) + (1 << bit);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	a.resize(n);
	
	for (auto &e: a) {
		cin >> e;
	}

	cout << solve(a, 30) << endl;
}


