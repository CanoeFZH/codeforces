import collections

MOD = 1000000007
n, k = map(int, input().split())

g = [[] for _ in range(n)]
for _ in range(n - 1):
    u, v, x = map(int, input().split())
    u -= 1
    v -= 1
    if x == 0:
        g[u].append(v)
        g[v].append(u)

res = 0
visit = [False] * n

all = pow(n, k, MOD)
bad = 0
for i in range(n):
    if visit[i]:
        continue
    d = collections.deque()
    d.append(i)
    visit[i] = True
    c = 1
    while d:
        u = d.pop()
        for v in g[u]:
            if visit[v]:
                continue
            visit[v] = True
            d.append(v)
            c += 1
    bad += pow(c, k, MOD)

print ((all - bad + MOD) % MOD)