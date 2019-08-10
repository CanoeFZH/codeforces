#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 55;

int f[N][N][N][N];
char s[N][N];

int solve(int x, int y, int z, int w) {
    if (f[x][y][z][w] != -1) {
        return f[x][y][z][w];
    }
    if (x == z && y == w) {
        return s[x][y] == '#';
    }
    
    int & ret = f[x][y][z][w];
    ret = max(z - x + 1, w - y + 1);
    for (int i = x; i < z; i++) {
        ret = min(ret, solve(x, y, i, w) + solve(i + 1, y, z, w));
    }

    for (int i = y; i < w; i++) {
        ret = min(ret, solve(x, y, z, i) + solve(x, i + 1, z, w));
    }
    return ret;
}

int main() {
    int n;
    scanf("%d", &n);
    memset(f, -1, sizeof(f));
    for (int i = 1; i <= n; i++) {
        scanf("%s", s[i] + 1);
    }
    
    printf("%d\n", solve(1, 1, n, n));
    return 0;
}
