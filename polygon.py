import fileinput
##########
#this is for wsl
import matplotlib
matplotlib.use('Agg') # no UI backend
import os
##########
import matplotlib.pyplot as plt
from shapely.geometry import Polygon

def plotPolygon(polygon):
    x,y = polygon.exterior.xy
    plt.plot(x,y,c="red")
    plt.show()
##########################################
#this is for wsl also
    if os.path.isfile("matplotlib.png") :
        os.remove("matplotlib.png")

    plt.savefig("matplotlib.png")
######################################


counter = 0
poly = []
for line in fileinput.input():          #read line by line
    counter += 1
    if counter>=3:                      #begin from 3rd row
        line = line.strip()             #remove '\n' 
        mylist = line.split('   ')      #split by tabs

        mylist[0] = int(mylist[0])      #convert to integers
        mylist[1] = int(mylist[1])
        mylist[2] = int(mylist[2])

        mylist.pop(0)                   #remove index
        mylist = tuple(mylist)          
        poly.append(mylist)

polygon1 = Polygon(poly)                #create polygon

plotPolygon(polygon1)