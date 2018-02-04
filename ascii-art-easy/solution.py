import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.
l = int(input())
h = int(input())
t = input()
# all the letters so we can get the index of the given letter
letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ?"
# the line for the art
line=""
for i in range(h):
    row = input()
    for c in t:
        foundIndex = int(letters.find (c.upper()))
        if foundIndex != -1:
            # zero based index
            foundIndex+=1
            line+=row[foundIndex*l - l:foundIndex*l]
        else:
            foundIndex = 27
            line+=row[foundIndex*l - l:foundIndex*l]
    print (line)
    # clear the line
    line=""
