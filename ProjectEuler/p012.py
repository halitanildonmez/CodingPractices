import math

def find_factors(n):
    s = math.sqrt(n)
    factors = 0
    for f in range(1, int(s)+1):
        if n % f == 0:
            factors = factors + 2

    if s * s == n:
        factors = factors - 1
        
    return factors


start_num = 0
i = 1

while find_factors(start_num) < 500:
    start_num = start_num + i
    i = i + 1

print (start_num, i)
