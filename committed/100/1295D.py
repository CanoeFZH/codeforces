from math import gcd

def phi(n):
    m = n
    factors = set()
    q = 2

    while n > 1 and q * q <= n:
        if n % q == 0:
            factors.add(q)
            n //= q
        else:
            q += 1
    if n > 1:
        factors.add(n)

    for p in factors:
        m *= p - 1
        m //= p
    return m

for _ in range(int(input())):
    a, m = map(int, input().split())
    m //= gcd(a, m)
    print(phi(m))
