# Area Polygonization, optimization and evaluation

compilation: (path to cgal library)/CGAL-5.5.1/scripts/cgal_create_CMakeLists -s evaluate \
        	(evaluate is the name of the executive program)\
        	cmake -DCGAL_DIR=(path to cgal library)/CGAL-5.5.1 . -DCMAKE_BUILD_TYPE=Release \
        	make

run:    	./evaluate -i (path to catalogue) -o output.txt \
			(path to catalogue): written as ../(foldername)/ \
			SOS: the last slash of the path is obligatory.

**1st Step: Polygonization:**

Polygonization of point set using CGAL library. 2 algorithms implemented:

***a) Incremental algorithm:*** \
Step 1: Sort the points using function sortv from sort.cpp file. \
Step 2: Choose starting triangle using function triangle from triangle.cpp file\
Step 3: For each point into the vector with the sorted points (loop)
        check its visile edges from the convex hull, function intersect from intersect.cpp file.
        Method used here is checking the ends and the middle of the edge. \
Step 4: From these visible edges, check if there are edges of the polygon (behind the convex hull). Function alledges from line.cpp file.\
Step 5: Select edge depending on the choice of the user. edgeselection function from edgeselection.cpp file, which seperates 
the options (1,2 or 3 criterion) and calls the appropriate functions from above.\
Step 6: Insert point in the appropriate place of the polygon in order to "break" the edge selected. insertpoint function from insertpoint.cpp file.

***b) Convex hull algorithm:***\
Step 1: Create convex hull (using convex_hull_2 function of cgal)\
Step 2: For every edge of the polygon find the closest visible point and store in a vector, using function closest from the close.cpp file.\
Step 3: Select edge using again edgeselection function, but for arguments we have pairvector (not segmentvector).\
Step 4: Insert point in the appropriate place of the polygon in order to "break" the edge selected using again insertpoint function.

Further explanation of the functions you can have from the comments in each function.

! In the second algorithm, there are cases where points have no more visible edges.
In that case the algorithm will display a message that says how many points remain
and give the polygon that was created up to that point. !


**2nd Step: Optimization:**

Optimization algorithms using CGAL library. 2 main algorithms implemented:

***a) Local search:***
See: loops.cpp/loops.h, pathlist.cpp/pathlist.h, changepol.cpp/changepol.h, localchange.cpp/localchange.h, globalchange.cpp/globalchange.h.
This algorithm is implemented as the given pseudocode in the lesson, that means it starts by creating the polygon using the greedy algorithm it was given and given a threshold, 
the maximum amount of points in a path (L) and whether we are looking for maximum or minimum, it will create a vector of segments that holds all the edges of our current polygon 
and a vector of paths which are vectors of points. As the algorithm progresses the polygon will change, thus they are calculated repeatedly, everytime the polygon is changed. 
For every edge, we check for every path if  the edge belongs to the path and in that case we skip to the next path, then we create a new polygon  using changePolygon, that puts the path, 
inside of the edge and links the points before and after it. If the polygon created is simple, we check if the difference between the areas of the old and the new polygons is smaller or 
bigger and depending on the result, we compare the area of the new polygon, to the area of the best polygon we have had until now and if it is we store the new polygons area as the best area and 
we add the path and the edge to the vector that will be used to change our polygon. We have added a counter that will stop the algorithm in case there are no better polygons 
found after multiple repeats. After all paths have been crossed with all the edges, we apply the changes and find the difference of areas between the new and the old polygon. 
If we surpass the threshold we repeat the previous steps for the new polygon, else we return the new polygon.



***b) Simulated annealing***: 
There are 3 options in this algorithm. Simulated annealing with local step, with global step and with subdivision, which is a way to combine local and global steps.
For local and global step, there is a common function in the file localglobalstep.cpp, where depending on the value “an” given, it performs local or global steps. 
If an==1, local step, if an==2, global step. localglobalstep function performs the pseudocode given in the lesson, with some differences, 
such as we apply the transitions in the polygon only with metropolis criterion (not the difference in energy being negative) 
and then we decrease the temperature T, and we have set an upper bound of maximum iterations to be performed, in order to break the loop.

*_Local step_*: See localtranstep.cpp/localtranstep.h. These are the files for local step. We perform exactly the instructions in the lesson. While using the kd-tree, 
we create a fuzzy box (cgal) using 2 points with the minimum and maximum x and y of the 4 points we have (pqrs).

*_Global step_*: See globaltranstep.cpp/globaltranstep.h. These are the files for global step. We perform exactly the instructions in the lesson. 
Some parts of the globaltransitionstep function are used only in subdivision (boolean value).

*_Subdivision_*: See subdivision.cpp/subdivision.h. The function subdivision performs the algorithm being described in the lesson. 
Firstly, we split the set of points into subsets (splitsubsets function), given a certain number of points in every subset (parameter m). 
We have chosen by default to set m = 100 in the main function (inputs.cpp file), in order to create less subsets with more points in each. 
However, each subset may end with more or less points than m due to the limit subdivision has about the common point. 
Specifically, the common point between two polygons must have a lower edge in both of them.
We achieve that by checking whether the final point in our subset has the previous and the next point lower in the y axis than it, 
and if not go to the previous point if that is above the common or go to the next for the same reason and use it as the common point between the polygons. 
The edges created by those points will be referred to as protected from now on.
Then, for every subset, depending on the boolean value “inc”,we perform the incremental or convex-hull algorithm. 
We have made some changes in these 2 algorithms in order to make sure that the protected edges will never change. 
We also chose to perform the convex_hull algorithm while incremental has been selected because sometimes incremental algorithm fails.
In case convex_hull fails in min or max, we call it again using rand. If the algorithm fails, the program returns an empty polygon and terminates in the main function. 
In addition, we have separated this implementation in 3 parts, because we want to discriminate the first subset with the last and all the in between. 
The reason is that there are different edges that must be retained in each of these 3 cases. 
The parameters in the incremental and convex hull algorithm have been set by default.
When applying global steps in each polygon, we set constraints for the points to be chosen, in order not to break the edges needed. 
That results sometimes in a non-terminating loop when searching for a random point to apply the change. 
So, we have also set an upper bound for max iterations while searching for points to apply transitions. 
The next step is to merge the polygons into one so we use the function mergePolygon in the merge.cpp/merge.h file. 
Finally, we perform some local steps, exactly as described before.


**3rd Step: Evaluation:**

Evaluation of combinations of algorithms using CGAL library. 

The main program is evaluation.cpp file, where the given directory and its files are being processed.
The program runs 7 times, each for one of the algorithms (combinations) that we have made in evalalgorithms.cpp/evalalgorithms.h
All files into the directory are being processed one by one, as in the previous 2 projects, but additionally, we have a vector to 
store all the different point sizes. We have also a different vector to store other vectors for holding min/max scores and bounds.
Before calling the algorithm, we go through a preproccess, in order to extract the most appropriate values (L,threshold,number
of points in each subset, sorting by x or y, ect.). We have chosen the following 7 combinations-algorithms for our program:

1) incremental + local search
2) incremental + local search + global step
3) incremental + global step + local step
4) subdivision(with convex hull) + local step
5) subdivision(with convex hull) + global step
6) subdivision(with convex hull) + global step + local step
7) subdivision(with convex hull) + local step + global step

We thought that these are the best combinations, as incremental takes way less time than convex hull,especially for big sizes,
local search gives (almost) always good results but it is slower than simulated annealing, and subdivision with convex hull is better
than subdivision with incremental, as incremental sometimes fails. We also wanted to show the results after combining the 2 steps (local and
global), and the optimizations (or not) after subdivision. Some others combinations where also tested, but because of really bad results,
we decided to omit and not include into the program.
Finally, we both print and write in a file a table with the scores and bounds of each algorithm that are used mainly to compare in the report.txt. For printing,
we use the vectors we discussed previously, by finding the index of the smaller size each time, printing its data and then remove both 
data and size from the vectors.
We checked the code from the previous two projects and made them as fast as we could. We achieved that by not checking if the middle of an edge intersects
with a point (since we check the two points of the edge, this was redundant), instead of checking for every edge and every point, after some 800 points, we only
check random points and edges in local search. We also fixed the local step to initialize only one time the kd tree and added some breaks in loops for simmulated 
annealing generally.
While working on preprocessing we tried to make the algorithms run without failing due to being cut off by time. Thus preprocessing values were set having in
mind that this programm might run for many points.
