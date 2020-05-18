#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//https://codeforces.com/blog/entry/69901
int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto &x: a) {
        cin >> x;
    }

    const int N = 67;
    // because 2 is a primitive root modulo 67. As a consequence, all powers of two less than 10^18 give distinct remainders modulo 67, so there are no collisions.
    int cnt[N] {};
    
    for (auto x: a) {
        ++cnt[(x & -x) % N];
    }

    int p = max_element(cnt, cnt + N) - cnt;

    cout << n - cnt[p] << endl;

    for (auto x: a) {
        if ((x & -x) % N != p) {
            cout << x << " ";
        }
    }
    cout << endl;

    return 0;
}
