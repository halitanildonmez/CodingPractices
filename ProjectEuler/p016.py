import math

m = 2
n = 1000

digits = str(int(math.pow(m, n)))

sum_digits = 0
for s in digits:
    sum_digits = sum_digits + int(s)

print(sum_digits)
