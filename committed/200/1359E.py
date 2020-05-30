MOD = 998244353
N = 10 ** 6 + 10

fac = [1] * N
for i in range(1, N):
    fac[i] = fac[i - 1] * i % MOD


def nCr(n, r):
    if n < 0 or r < 0 or n < r:
        return 0
    return fac[n] * pow(fac[n - r], MOD - 2, MOD) * pow(fac[r], MOD - 2, MOD) % MOD


n, k = map(int, input().split())

ans = 0
for i in range(1, n + 1):
    ans += nCr(n // i - 1, k - 1)
print(ans % MOD)
