def compute_gcd(x, y):
   while(y):
       x, y = y, x % y
   return x

def compute_lcm(x, y):
   lcm = (x*y)//compute_gcd(x,y)
   return lcm

t = 1
r = compute_lcm(t, t + 1)

for i in range(3, 21):
    r = compute_lcm(r, i)

print (r)
