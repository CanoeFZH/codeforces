#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int N = 2020;

int p[N], c[N], a[N];

vector<int> e[N];

vector <int> dfs(int u) {
	vector <int> u_sons;
	for (auto v: e[u]) {
		vector<int> v_sons = dfs(v);
		u_sons.insert(u_sons.end(), v_sons.begin(), v_sons.end());
	}

	if (c[u] > u_sons.size()) {
		cout << "NO" << endl;
		exit(0);
	}

	u_sons.insert(u_sons.begin() + c[u], u);
	return u_sons;
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> p[i] >> c[i];
		e[p[i]].push_back(i);
	}

	vector<int> v = dfs(0);

	for (int i = 1; i <= n; i++) {
		a[v[i]] = i;
	}
	cout << "YES" << endl;
	for (int i = 1; i <= n; i++) {
		cout << a[i] << (i == n ? '\n' : ' ') << endl;
	}
	return 0;
}
