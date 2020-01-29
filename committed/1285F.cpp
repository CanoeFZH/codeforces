#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int N = 105000;
const int MAXA = 100000;

int n, a[N], cnt[N];
bool has[N];
vector<int> p[N], divs[N], v;

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

void update_counts(int x, int val) {
    for(int div: divs[x]) {
       // cout << div << " ??" << endl;
        cnt[div] += val;
    }
}

int get_bit(long long x, int pos) {
    return (x & (1LL << pos)) > 0 ? 1 : 0;
}

long long get_coprime(int x) {
    int p_number = p[x].size();
    long long result = 0;
    for (int mask = 1; mask < (1 << p_number); mask++) {
        int acc = 1;
        for (int i = 0; i < p_number; i++) {
            if (get_bit(mask, i) == 1) {
                acc *= p[x][i];
            }
        }
        if (__builtin_popcount(mask) & 1) {
            result += cnt[acc];
        } else {
            result -= cnt[acc];
        }
    }
    return result;
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        has[a[i]] = true;
    }

    long long ans = lcm(a[0], a[1]);
    for (int i = 1; i <= MAXA; i++) {
        int current = i;
        for (int j = 2; j * j <= current; j++) {
            if (current % j == 0) {
                p[i].push_back(j);
            }
            while (current % j == 0) {
                    current /= j;
            }
        }
        if (current != 1) {
            p[i].push_back(current);
        }

        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                divs[i].push_back(j);
                if (i / j != j) {
                    divs[i].push_back(i / j);
                }
            }
        }
    }

    for (int g = 1; g <= MAXA; g++) {
        v.clear();
        for (int i = g; i <= MAXA; i += g) {
            if (has[i]) {
                v.push_back(i / g);
            }
        }
        reverse(v.begin(), v.end());

        stack<int> s;
        for (int x: v) {
            int coprime = s.size() - get_coprime(x);
            while(coprime) {
                int y = s.top();
                if (gcd(x, y) == 1) {
                    ans = max(ans, 1LL * g * x * y);
                    coprime--;
                }
                s.pop();
                update_counts(y, -1);
            }
            s.push(x);
            update_counts(x, 1);
        }

        while(!s.empty()) {
            update_counts(s.top(), -1);
            s.pop();
        }
    }

    cout << ans << endl;
    return 0;
}