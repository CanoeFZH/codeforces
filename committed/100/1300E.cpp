#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

const int N = 1000007;

long long acc[N], cnt[N];

int main() {
    int n, top = 0;
    long long a;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &a);
        acc[++top] = a;
        cnt[top] = 1;
        while(acc[top - 1] * cnt[top] >= acc[top] * cnt[top - 1] && top - 1 > 0) {
            acc[top - 1] += acc[top];
            cnt[top - 1] += cnt[top];
            acc[top] = cnt[top] = 0;
            top--;
        }

    }

    for(int i = 1; i <= top; i++) {
        for(int j = 1; j <= cnt[i]; j++) {
            printf("%.9lf\n", ((double) acc[i]) / cnt[i]);
        }
    }

    return 0;
}