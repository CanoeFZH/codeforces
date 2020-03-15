u, v = map(int, input().split())

if u > v or u % 2 != v % 2:
    print("-1")
elif u == v:
    if u == 0:
        print(0)
    else:
        print(1)
        print(u)
else:
    x = (v - u) // 2
    if u & x:
        print(3)
        print(u, x, x)
    else:
        print(2)
        print(u ^ x, x)
