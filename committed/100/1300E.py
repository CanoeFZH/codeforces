n = int(input())
A = list(map(int, input().split()))

ans = []

for i, a in enumerate(A):
    sum_a = a
    count_a = 1
    for s, c in reversed(ans):
        if (sum_a + s) * c > s * (count_a + c):
            break
        count_a += c
        sum_a += s
        ans.pop()
    ans.append((sum_a, count_a))

for s, c in ans:
    mean = str(s / c)
    print('\n'.join(mean for _ in range(c)))