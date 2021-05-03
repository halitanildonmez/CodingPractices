res = 0
for i in range(2, 1000):
    if i % 3 == 0 or i % 5 == 0:
        res = res + i
print (res)
