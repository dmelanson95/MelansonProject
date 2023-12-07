import re, sys

fileName = sys.argv[1]

vals = [float(i.split(',')[1]) for i in open(fileName, 'r').readlines() if i.split(',')[1] != 'value']

min, max, avg, count = 1000, -100, 0, 0
for i in vals:
    if i < min:
        min = i
    if i > max:
        max = i
    avg += i
    count +=1
avg = avg/count

print(f"min = {min}\nmax = {max}\navg = {avg}\ntotal entries = {count}\n")
