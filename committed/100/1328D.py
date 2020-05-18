t = int(input())

for _ in range(t):
    N = int(input())
    A = [int(a) for a in input().split()]

    if max(A) == min(A):
        print(1)
        print(*([1] * N))
    elif N % 2 == 0:
        print(2)
        print(*([1, 2] * (N // 2)))
    else:
        for i in range(N):
            if A[i - 1] == A[i]:
                print(2)
                print(*(([1, 2] * N)[:i][::-1] + ([1, 2] * N)[:N - i]))
                break
        else:
            print(3)
            print(*([3] + [1, 2] * (N // 2)))
