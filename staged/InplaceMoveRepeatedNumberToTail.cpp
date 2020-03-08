#include <cstdio>
#include <vector>

using namespace std;

void print(vector<int> & a) {
    for (auto e : a) {
        printf("%d ", e);
    }
    puts("");
}

void solve(vector <int> &a) {
    if (a.size() <= 2) {
        return;
    }
    int n = a.size();
    int i = 1, j = 1;
    int previous = a[0];
    while(j < n) {
        if (a[j] != previous) {
            previous = a[j];
            swap(a[i++], a[j]);
        }
        ++j;
    }

}

int main() {
#define _DEBUG
#ifdef _DEBUG
    freopen("input", "r", stdin);
#endif

    int test_case = 0;
    scanf("%d", &test_case);
    while(test_case--) {
        int n;
        scanf("%d", &n);
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        solve(a);
        print(a);
    }
    return 0;
}