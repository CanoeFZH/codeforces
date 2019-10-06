def prime_factorization(x):
    primes = []
    i = 2
    while i * i <= x:
        if x % i == 0:
            primes.append(i)
            while x % i == 0:
                x //= i
        i += 1

    if x > 1:
        primes.append(x)

    return primes

def solve(x, n):
    mod = 10 ** 9 + 7
    answer = 1
    primes = prime_factorization(x)

    for prime in primes:
        power = 0
        factor = prime
        while factor <= n:
            power += n // factor
            factor *= prime

        answer *= pow(prime, power, mod)
        answer %= mod

    return answer

x, n = [int(e) for e in input().split()]
print(solve(x, n))
