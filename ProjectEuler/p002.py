f = [0, 1]
n = 33

even_sum = 0

for i in range(2, n+1):
    f_n = f[i-1] + f[i-2]
    if f_n % 2 == 0:
        even_sum = even_sum + f_n
    f.append(f_n)

print(even_sum)


     

