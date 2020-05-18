m, n = map(int, input().split())

s = [0] * m

for w in range(m):
    for i in list(map(int, input().split()))[1:]:
        s[w] |= 1 << i

for i in s:
    for j in s:
        if not (i & j):
            print('impossible')
            exit(0)

print('possible')