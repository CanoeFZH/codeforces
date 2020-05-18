#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

const int N = 101;

int a[N];
int dp[N][N][2];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0][0] = dp[0][0][1] = 0;
	for (int i = 1; i <= n; i++) {
		for (int c0 = 0; c0 <= i; c0++) {
			if (a[i] % 2 || a[i] == 0) {
				dp[i][c0][1] = min(dp[i - 1][c0][0] + 1, dp[i - 1][c0][1]);
			}

			if (a[i] % 2 == 0 && c0 >= 1) {
				dp[i][c0][0] = min(dp[i - 1][c0 - 1][0], dp[i - 1][c0 - 1][1] + 1);
			}
		}
	}
	cout << min(dp[n][n/2][0], dp[n][n/2][1]) << endl;
	
	return 0;
}
