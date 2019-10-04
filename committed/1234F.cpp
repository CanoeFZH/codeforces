#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int N = 20;
const int MASK = 1 << 20;

int main() {
    string s;
    cin >> s;

    vector <int> dp(MASK);
    for(int i = 0; i < int(s.size()); i++) {
        vector <bool> used(N);
        int mask = 0;
        for (int j = 0; i + j < int(s.size()); j++) {
            int index = s[i + j] - 'a';
            if (used[index]) {
                break;
            } 

            used[index] = true;
            mask |= 1 << index;
            dp[mask] = __builtin_popcount(mask);
        }
    }

    for (int mask = 0; mask < MASK; mask++) {
        for (int j = 0; j < N; j++) {
            if ((mask >> j) & 1) {
                dp[mask] = max(dp[mask], dp[mask ^ (1 << j)]);
            }
        }
    }
    
    int answer = 0;
    for (int mask = 0; mask < MASK; mask++) {
        if (dp[mask] == __builtin_popcount(mask)) {
            int reverse = ~mask & (MASK - 1);
            answer = max(answer, dp[mask] + dp[reverse]);
        }
    }

    cout << answer << endl;
    return 0;
}
