n = int(input())
l = list(map(int, input().split()))

ans = 0

for i in range(n):
    for j in range(i, n):
        for k in range(j, n):
            ans = max(ans, l[i] | l[j] | l[k])
print(ans)
