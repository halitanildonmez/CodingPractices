r = 1000

for m in range(2, 110):
    for n in range(1, 100):
        a = (m * m) - (n * n)
        b = 2 * m * n
        c = (m * m) + (n * n)
        if (a*a) + (b*b) == (c*c):
            if a + b + c == r:
                p = a*b*c
                print(a, b, c, p)

