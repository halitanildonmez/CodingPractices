max_count = 0
res = 0
for i in range(1000000, 1, -1):
    count = 0
    num = i
    while num != 1:
        if num % 2 == 0:
            num = num / 2
        else:
            num = (num * 3) + 1
        count = count + 1
    if count > max_count:
        max_count = count
        res = i
    
print(max_count, res)
