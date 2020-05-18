#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 200 + 7;

int n, k, A[N];
vector<int> G[N];
int dp[N][N], answer;

void dfs(int u, int fa) {
	dp[u][0] = A[u];
	for (auto v: G[u]) {
		if (v == fa) {
			continue;
		}

		dfs(v, u);
		for (int i = 0; i <= n; i++) {
			int tmp = dp[u][i];
			for (int j = max(0, k - i); j <= n; j++) {
				int depth = min(j + 1, i);
				dp[u][depth] = max(dp[u][depth], dp[v][j] + tmp);
			}
		}
	}
}

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> A[i];
	}

	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	dfs(1, 0);

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			answer = max(answer, dp[i][j]);
		}
	}

	cout << answer << endl;
	return 0;
}
