N = 600851475143
p = 2
while N >= p * p:
    if N % p == 0:
        N = N / p
    else:
        p = p + 1
print (N)
