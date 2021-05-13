import sys

primes = []

def SieveOfEratosthenes():
    n = 1000005
    prime = [True for i in range(n + 1)]
     
    p = 2
    while (p * p <= n):
        if (prime[p] == True):
            for i in range(p * p, n + 1, p):
                prime[i] = False
                 
        p += 1
       
    for p in range(2, n + 1):
        if prime[p]:
            primes.append(p)


SieveOfEratosthenes()
print(primes[10000])
