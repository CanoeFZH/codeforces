_, m = list(map(int, input().split()))
q = list(map(int, input().split()))

aggrement = set()

for i in range(m):
    u, v = list(map(int, input().split()))
    aggrement.add((u, v))

pendings = [q.pop()]
count = 0
while q != []:
    u = q.pop()
    works = True
    for pending in pendings:
        if not (u, pending) in aggrement:
            works = False
            break
    if works:
        count += 1
    else:
        pendings.append(u)

print(count)