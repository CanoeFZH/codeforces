n = int(input())
a = list(map(int, input().split())) + [0]

answer = [0] * n
current_increase_max = -1
current_decrease_min = 1e6

for i in range(n):
    if current_increase_max < a[i] and a[i] < current_decrease_min:
        if a[i] < a[i + 1]:
            current_increase_max = a[i]
            answer[i] = 0
        else:
            current_decrease_min = a[i]
            answer[i] = 1
    elif current_increase_max < a[i]:
        current_increase_max = a[i]
        answer[i] = 0
    elif current_decrease_min > a[i]:
        current_decrease_min = a[i]
        answer[i] = 1
    else:
        print("NO")
        exit(0)

print("YES")
print(*answer)


