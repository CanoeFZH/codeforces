MOD = 998244353

n, m, l, r = map(int, input().split())

if n * m % 2 == 1:
    print(pow(r - l + 1, n * m, MOD))
else:
    e = r // 2 - (l - 1) // 2
    o = (r - l + 1) - e
    print((pow(e + o, n * m, MOD) + pow(e - o, n * m, MOD)) * (MOD + 1) // 2 % MOD)
