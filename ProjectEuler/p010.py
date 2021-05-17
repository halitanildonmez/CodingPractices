import math

n = 2000000
A = [True for i in range(n)]

sq_n = math.sqrt(n)

for i in range(2, int(sq_n) + 1):
    if A[i] == True:
        for j in range(n):
            index = i*i + j*i
            if index < n:
                A[index] = False
            else:
                break

res = 0
for i in range(2, len(A)):
    if A[i] == True:
        res = res + i

print (res)
