#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

const int N = 300010, L = 20;

int n, q, a[N], last[N], reach[N][L];

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < L; j++) {
            if (a[i] >> j & 1) {
                reach[i][j] = i;
                //Bit j is reachable from a[i], so all bits in last[j] are all reachable from a[i]. 
                for (int k = 0; k < L; k++) {
                    reach[i][k] = max(reach[i][k], reach[last[j]][k]);
                }
                last[j] = i;
            }
        }
    }

    while(q--) {
        bool flag = false;
        int x, y;
        cin >> x >> y;
        for (int i = 0; i < L; i++) {
            if (a[x] >> i & 1) {
                flag |= reach[y][i] >= x;
            }
        }
        string answer = flag ? "Shi" : "Fou";
        cout << answer << endl;
    }    
    return 0;
}