#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 200001;
int a[N], n;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = abs(a[i]);
    }

    sort(a + 1, a + n + 1);
    long long answer = 0;
    for(int i = 1; i < n; i++) {
        answer += upper_bound(a + i + 1, a + n + 1, 2 * a[i]) - a - 1 - i;
    }

    cout << answer << endl;
    return 0;
}