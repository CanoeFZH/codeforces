N = int(input())
M = 998244353

ans = []
for i in range(1, N):
    a = 0
    if N - i >= 2:
        a += (N - i - 1) * 81 * pow(10, N - i - 1, M)
    if N - i >= 1:
        a += 2 * 9 * pow(10, N - i, M)
    ans.append(a % M)
ans.append(10)

print(*ans)
