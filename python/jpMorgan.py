input_s = input()

ans =''
a =0
words = input_s.split()
for i in words:
	l = len(i)
	if (l%2==0 and a<l):
		a =l
		ans =i

print(ans)

