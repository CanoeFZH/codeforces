n, m = (int(i) for i in input().split())
a = [[int(i) for i in input().split()] for _ in range(n)]

res = 0
for j in range(m):
	b = [0] * n
	for i in range(n):
		if a[i][j] <= n * m and (a[i][j] - j - 1) % m == 0:
			pos = (a[i][j] - j - 1) // m
			shift = (i - pos + n) % n
			b[shift] += 1
    
	res += min(i + n - b[i] for i in range(n))
print(res)
