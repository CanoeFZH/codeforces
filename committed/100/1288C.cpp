#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;
const int M = 11;
const int N = 1010;

ll dp[M][N];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	dp[0][0] = 1;
	for (int p = 0; p < 10; p++) {
		for (int i = 0; i < N; i++) {
			for (int j = max(i, 1); j < N; j++) {
				dp[p + 1][j] = (dp[p + 1][j] + dp[p][i]) % MOD;
			}
		}
	}

	int n, m;
	cin >> n >> m;
	ll answer = 0;

	for (int x = 1; x <= n; x++) {
		for (int y = 1; y <= n + 1 - x; y++) {
			answer += dp[m][x] * dp[m][y];
			answer %= MOD;
		}
	}
	cout << answer << endl;
	return 0;
}
