p1 = 999
res = 0
while p1 > 99:  
    for i in range(p1, 99, -1):
        candidate = p1 * i
        candidate_str = str(candidate)
        if candidate_str == candidate_str[::-1]:
            if res < candidate:
                res = candidate
            break
    p1 = p1 - 1

print (res)
