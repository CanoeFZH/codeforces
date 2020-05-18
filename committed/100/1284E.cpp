#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 2520;
using pi = pair<int, int>;

int n;
pi a[N];

long long bino(int x, int y) {
	long long acc = 1;
	for (int i = 0; i < y; i++) {
		acc *= x - i;
		acc /= i + 1;
	}

	return acc;
}

long long ccw(pi a, pi b) {
	return 1LL * a.first * b.second - 1LL * b.first * a.second;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i].first >> a[i].second;
	}

	long long total = 0;

	for (int i = 0; i < n; i++) {
		vector <pi> v;
		for (int j = 0; j < n; j++) {
			if (i != j) {
				v.emplace_back(a[j].first - a[i].first, a[j].second - a[i].second);
			}
		}

		sort(v.begin(),
			v.end(),	
			[&](const pi &a, const pi &b) {
			bool cmpA = a < pi(0, 0);
			bool cmpB = b < pi(0, 0);
			if (cmpA != cmpB) {
			return cmpA < cmpB;
			}
			return ccw(a, b) > 0;
		});

		int k = 0;
		int v_size = v.size();
		for (int j = 0; j < v_size; j++) {
			while(k < j + v_size && ccw(v[j], v[k % v_size]) >= 0) {
				k++;
			}
			total += bino(k - j - 1, 3);
		}
	}

	cout << bino(n, 5) * 5 - total << endl;
	return 0;
}
