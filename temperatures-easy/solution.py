import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.
vals = [];
n = int(input())  # the number of temperatures to analyse

for i in input().split():
    vals.append (int(i))
    
try:
    largerThanZero = min (list ( filter (lambda x : x >= 0, vals) ) )
except (ValueError, TypeError):
    largerThanZero = 100000

try:
    smallerThanZero = max (list ( filter (lambda x : x < 0, vals) ) )
except (ValueError, TypeError):
    smallerThanZero = -100000

result = 0 if smallerThanZero == -100000 and largerThanZero == 100000 else largerThanZero if largerThanZero < smallerThanZero*-1 else largerThanZero if largerThanZero == smallerThanZero*-1 else smallerThanZero

print(result)