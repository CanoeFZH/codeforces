'''
https://codeforces.com/contest/1139/problem/D
https://codeforces.com/blog/entry/66101?#comment-500999
https://brilliant.org/wiki/linearity-of-expectation/
https://en.wikipedia.org/wiki/Negative_binomial_distribution
Suppose there is a sequence of independent Bernoulli trials. Thus, each trial has two potential outcomes called "success" and "failure". In each trial the probability of success is p and of failure is (1 − p). We are observing this sequence until a predefined number r of failures has occurred. Then the random number of successes we have seen, X, will have the negative binomial (or Pascal) distribution:

{\displaystyle X\sim \operatorname {NB} (r,p)} {\displaystyle X\sim \operatorname {NB} (r,p)}
1. mobius function: 
2. Negative binomial distribution
'''

N = 100010

def gen_mobius_function():
    mu = [1] * N
    mu[0] = 0
    P = [True] * N
    P[0] = P[1] = False
    for i in range(2, N):
        if P[i]:
            j = i
            while j < N:
                P[j] = False
                mu[j] *= -1
                j += i
            j = i * i
            while j < N:
                mu[j] = 0
                j += i * i
    return mu

m = int(input())
mu = gen_mobius_function()

MOD = 10**9 + 7

def mod_inv(x):
    return pow(x, MOD - 2, MOD)

E = 1
for i in range(2, N):
    p = m // i * mod_inv(m)
    E += -mu[i] * p * mod_inv(1 - p) #mobius, Negative binomial function
print(E % MOD)
