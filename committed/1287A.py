for _ in range(int(input())):
	input()
	s = input().lstrip('P')
	print(max(map(len, s.split('A'))))
