import sys
import math
surface_n = int(input())
for i in range(surface_n):
    land_x, land_y = [int(j) for j in input().split()]
while True:
    x, y, h_speed, v_speed, fuel, rotate, power = [int(i) for i in input().split()]
    print ("0 1") if v_speed <= 0 and v_speed > -40 else print ("0 4")