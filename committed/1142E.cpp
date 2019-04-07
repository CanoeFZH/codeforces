/*
 * binary lifting
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200010;
const int B = 20;

int n, m, Q, x, y, p[N], h[N], last[N], g[N], f[N][B + 2];

int go(int x, int y) {
    for (int i = B; ~i; i--) {
        if(y & (1 << i)) {
            x = f[x][i];
        }
    }
    return x;
}

int main() {
    cin >> n >> m >> Q;
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    last[p[1]] = p[n];
    for(int i = 2; i <= n; i++) {
        last[p[i]] = p[i - 1];
    }
    
    for (int i = 1; i <= m; i++) {
        cin >> x;
        h[x] = i;
        f[i][0] = h[last[x]];
        for(int j = 1; j <= B; j++) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }
        g[i] = max(g[i - 1], go(i, n - 1));
    }
    for (int i = 1; i <= Q; i++) {
        cin >> x >> y;
        cout << (char)('0' + (x <= g[y]));
    }
    cout << endl;

    return 0;
}
