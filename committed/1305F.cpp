#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <set>
#include <ctime>
#include <random>
#include <iterator>
#include <chrono>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 2e5 + 10;

int n;
long long a[N], ans;

void calc(long long x) {
    long long acc = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < x) {
            acc += x - a[i];
        } else {
            acc += min(x - a[i] % x, a[i] % x);
        }
    }
    ans = min(ans, acc);
}

void test(long long x) {
    if(!x) {
        return;
    }
    for (long long i = 2; i * i <= x; i++) {
        if(x % i == 0) {
            calc(i);
        }
        while(x % i == 0) {
            x /= i;
        }
    }

    if (x != 1) {
        calc(x);
    }
}

int main() {
    scanf("%d", &n);
    ans = n;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    for (int t = 0; t < 30; t++) {
        int index = rng() % n;
        test(a[index] - 1);
        test(a[index]);
        test(a[index] + 1);
    }

    printf("%lld\n", ans);
    return 0;
}