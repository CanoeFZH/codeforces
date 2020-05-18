#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <iostream>
#include <cstdlib>

using namespace std;

const int N = 100000;

int u[N + 1], cnt[N + 1];

vector<int> d[N + 1];
bool b[N + 1];

void update(int x, int value) {
    for(int e: d[x]) {
        cnt[e] += value;
    }
}

bool coprime(int x) {
    int ret = 0;
    for (int e: d[x]) {
        ret += u[e] * cnt[e];
    }
    return ret;
}

int main() {
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            d[j].push_back(i);
        }
        if (i == 1) {
            u[i] = 1;
        } else if ((i / d[i][1]) % d[i][1] == 0) {
            u[i] = 0;
        } else {
            u[i] = -u[i / d[i][1]];
        }
    }

    int n;
    cin >> n;
    long long ans = 0;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        ans = max(ans, (long long) a);
        b[a] = true;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 2; i * j <= N; j++) {
            b[i] |= b[i * j];
        }
    }

    stack<int> s;
    for (int i = N; i > 0; --i) {
        if (!b[i]) {
            continue;
        }

        while(coprime(i)) {
            ans = max(ans, (long long) i * s.top());
            update(s.top(), -1);
            s.pop();
        }

        update(i, 1);
        s.push(i);
    }

    cout << ans << endl;
    return 0;
}