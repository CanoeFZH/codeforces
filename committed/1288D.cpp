#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

vector <vector<int>> A;
int n, m, a1, a2;

bool check(int x) {
	vector <int> mask(1 << m, -1);

	for (int i = 0; i < n; i++) {
		int mask_acc = 0;
		for (int j = 0; j < m; j++) {
			if (A[i][j] >= x) {
				mask_acc ^= (1 << j);
			}
		}
		mask[mask_acc] = i;
	}

	if (mask[(1 << m) - 1] != -1) {
		a1 = a2 = mask[(1 << m) - 1];
		return true;
	}

	for (int i = 0; i < (1 << m); i++) {
		for (int j = 0; j < (1 << m); j++) {
			if (mask[i] != -1 && mask[j] != -1 && (i | j) == (1 << m) - 1) {
				a1 = mask[i];
				a2 = mask[j];
				return true;
			}
		}
	}

	return false;
}

int main() {
	cin >> n >> m;
	A.resize(n, vector<int> (m));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> A[i][j];
		}
	}

	int left = 0, right = int(1e9) + 43;
	
	while(left <= right) {
		int middle = (left + right) / 2;
		if (check(middle)) {
			left = middle + 1;
		} else {
			right = middle - 1;
		}
	}

	cout << a1 + 1 << " " << a2 + 1 << endl;
	return 0;
}
