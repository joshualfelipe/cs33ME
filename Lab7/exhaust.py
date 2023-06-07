from itertools import permutations
import math

length = int(input())
activity = {}

for i in range(length):
    val = input().split(" ")
    activity[val[0]] = [val[2], val[3]]

places = list(activity.keys())

m = list(permutations(places))
l = []
for i in m:
    if i[0] == "Rest":
        l.append(i)

final = {}
counter = 0
for i in range(len(l)):
    lst = []
    for j in range(length):
        d1x = float(activity[l[i][j]][0])
        d1y = float(activity[l[i][j]][1])
        x = j + 1
        if j == length - 1:
            x = 0
        d2x = float(activity[l[i][x]][0])
        d2y= float(activity[l[i][x]][1])
        dist = math.sqrt(((d1x-d2x)**2)+((d1y-d2y)**2))*1000
        lst.append(dist)
    counter+=1
    final[str(i)] = sum(lst)

minimum = min(final, key=final.get)
print(round(final[minimum],3))
for i in l[int(minimum)]:
    print(i)
print(l[int(minimum)][0])
