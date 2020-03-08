#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int N = 5e5 + 10;

long long V[N];

int main() {

#ifndef ONLINE_JUDGE
    freopen("input", "r", stdin);
#endif

    int test_case;
    scanf("%d", &test_case);
    while(test_case--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%lld", &V[i]);
        }

        vector<vector<int> > E(n);
        int u, v;
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            u--, v--;
            E[v].push_back(u);
        }

        map<vector<int>, long long> S;
        for(int v = 0; v < n; v++) {
            if (E[v].empty()) {
                continue;
            }
            sort(E[v].begin(), E[v].end());

            S[E[v]] += V[v];
        }

        long long gcd = 0;
        for(auto e: S) {
            //gcd = __algo_gcd(gcd, e.second);
            gcd = __gcd(gcd, e.second);
        }
        printf("%lld\n", gcd);
    }
    return 0;
}