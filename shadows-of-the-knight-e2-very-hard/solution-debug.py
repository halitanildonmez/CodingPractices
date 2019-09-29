import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

def calculate_mid(a, b):
    return int((a+b)/2)

# w: width of the building.
# h: height of the building.
w, h = [int(i) for i in input().split()]
n = int(input())  # maximum number of turns before game over.
x0, y0 = [int(i) for i in input().split()]

print ("W: {0} H: {1}".format(w, h), file=sys.stderr)

sx = True
sy = False

w_l = 0
w_h = w - 1 
c_l = w_l
c_h = w_h

cur_l = 0
cur_h = w - 1 
pos = x0

limit = w - 1
give = 0
outside = False

first = True
override_y = -1

#https://stackoverflow.com/questions/25558951/hot-and-cold-binary-search-game
#https://gist.github.com/MSK61/1997c31e01fafbaff01f

# game loop
while True:
    bomb_dir = input()  # Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN
   
    print ("w_l: {0} w_h: {1} start: {2}".format(w_l, w_h, y0), file=sys.stderr)
    print ("c_l: {0} c_h: {1} pos: {2}".format(c_l, c_h, pos), file=sys.stderr)
    print ("cur_l: {0} cur_h: {1} test mid: {2}".format(cur_l, cur_h, calculate_mid(cur_l, cur_h)), file=sys.stderr)
    
    if bomb_dir == "WARMER":
        print(bomb_dir, file=sys.stderr)
        cur_l = w_l
        cur_h = w_h
    elif bomb_dir == "COLDER":
        print(bomb_dir, file=sys.stderr)
        cur_l = c_l
        cur_h = c_h        
    elif bomb_dir == "SAME":
        print(bomb_dir, file=sys.stderr)
        tx = calculate_mid(cur_l, cur_h)
        # HANDLE THIS!
        if sx == True:
            sx = False
            x0 = tx
            w_l = 0
            w_h = h - 1
            c_l = w_l
            c_h = w_h
            cur_l = 0
            cur_h = h - 1 
            pos = y0
            limit = h - 1
        else:
            #handle this too ?
            print("THIS ONE ??", file=sys.stderr)
            y0 = tx
            sy = True
            
    elif bomb_dir == "UNKNOWN":
        print(bomb_dir, file=sys.stderr)
    
    if cur_l >= cur_h:
        tx = calculate_mid(cur_l, cur_h)
        if sx == False:
            print("Already found the sx ? {0}".format(tx), file=sys.stderr)
            override_y = tx
            sy = False
        else:
            sx = False
            x0 = tx
        print("Found a SAME ? {0} {1} {2}".format(tx, first, sx), file=sys.stderr)
        w_l = 0
        w_h = h - 1
        c_l = w_l
        c_h = w_h
        cur_l = 0
        cur_h = h - 1 
        pos = y0
        limit = h - 1
    
    low = cur_l
    high = cur_h
    give = low + high - pos
    
    if outside:
        if pos == 0:
            give = calculate_mid(give,0)
        elif pos == limit:
            give = calculate_mid(limit,give)
    outside = False
    if give > limit:
        give = limit
        outside = True
    elif give == pos:
        give = pos + 1
    elif give < 0:
        give = 0
        outside = True
        
    mid = calculate_mid(give, pos)
    lower = calculate_mid(give, pos - 1)
    higher = calculate_mid(give, pos + 1)
    
    print ("mid: {0} lower: {1} higher: {2}".format(mid, lower, higher), file=sys.stderr)
    print ("Cur_l: {0} Cur_h: {1}".format(cur_l, cur_h), file=sys.stderr)
    
    if give > pos:
        w_l = higher
        w_h = high
        c_l = low
        c_h = lower
    elif give < pos:
        w_l = low
        w_h = lower
        c_l = higher
        c_h = high

    if sx == False and sy == True:
        print("Found bof ?", file=sys.stderr)
        

    if sx == True:
        print("{0} {1}".format(give, y0))
    else:
        if override_y != -1:
            print("{0} {1}".format(x0, override_y))
        elif sy == True:
            print("{0} {1}".format(x0, y0))
        else:
            print("{0} {1}".format(x0, give))
    pos = give
    first = False