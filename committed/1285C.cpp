#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

ll x;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> x;
	vector<ll> f;

	for (ll i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			ll cur = 1;
			while (x % i == 0) {
				x /= i;
				cur *= i;
			}
			f.push_back(cur);
		}
	}

	if (x > 1) {
		f.push_back(x);
	}

	/*for (int i = 0; i < f.size(); i++) {
		cout << f[i] << " ";
	}
	cout << endl;
	*/

	int n = f.size();
	ll ans_a = 1e18, ans_b = 1e18;

	for (int i = 0; i < (1 << n); i++) {
		ll a = 1, b = 1;
		for (int j = 0; j < n; j++) {
			if ((i >> j) & 1) {
				a *= f[j];
			} else {
				b *= f[j];
			}
		}

		if (max(a, b) < max(ans_a, ans_b)) {
			ans_a = a;
			ans_b = b;
		}
	}

	cout << ans_a << " " << ans_b << endl;
	return 0;
}
