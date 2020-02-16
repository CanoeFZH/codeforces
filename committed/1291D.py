s = input()

count = [[0] * 26] * (len(s) + 1)
for index, e in enumerate(s):
    char_index = ord(e) - ord('a')
    count[index + 1][char_index] = count[index][char_index] + 1 

n = int(input())

for _ in range(n):
    l, r = map(int, input().split())
    element_size = 0
    for i in range(26):
        if count[r][i] - count[l - 1][i] > 0:
            element_size += 1
    if l == r or element_size >= 3 or s[l - 1] != s[r - 1]:
        print("Yes")
    else:
        print("No")
