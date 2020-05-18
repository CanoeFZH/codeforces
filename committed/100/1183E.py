N, K = map(int, input().split())
pre = [input()]
ans = 0
k = 1
f = 0
while True:
    if k >= K:
        print(ans)
        break
    if len(pre) == 0:
        print(-1)
        break

    post = []
    for s in pre:
        for i in range(len(s)):
            t = s[:i] + s[i+1:]
            if t not in post:
                k += 1
                post.append(t)
                ans += N - len(t)

                if k >= K:
                    print(ans)
                    f = 1
                    break
        if f:
            break
    if f:
        break
    pre = post

