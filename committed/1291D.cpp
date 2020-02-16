#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 200010;

char s[N];
int sum[N][26];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> (s + 1);

    int n = strlen(s + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 26; j++) {
            sum[i][j] = sum[i - 1][j];
        }
        sum[i][s[i] - 'a'] += 1;
    }

    int l, r, q;
    cin >> q;
    while(q--) {
        cin >> l >> r;
        int count = 0;
        for(int i = 0; i < 26; i++) {
            count += (sum[r][i] - sum[l - 1][i]) > 0;
        }

        if (l == r || count >= 3 || s[l] != s[r]) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}