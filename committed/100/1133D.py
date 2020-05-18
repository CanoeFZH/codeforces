from decimal import *

n = int(input())
a = list(map(Decimal, input().split()))
b = list(map(Decimal, input().split()))

d = {}
extra = 0

for i in range(n):
    if a[i] == 0 and b[i] == 0:
        extra += 1
        continue
    elif a[i] == 0:
        continue
    p = b[i] / a[i]
    d[p] = d.get(p, 0) + 1

print(max(list(d.values()) + [0]) + extra)