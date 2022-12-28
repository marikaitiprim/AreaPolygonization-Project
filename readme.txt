Optimization algorithms in polygonization using CGAL library.

ΚΑΜΑΡΗΣ ΑΓΓΕΛΟΣ sdi1900070  (KAMARIS ANGELOS)
ΠΡΙΜΕΝΤΑ ΑΙΚΑΤΕΡΙΝΗ-ΜΑΡΙΑ sdi1900160 (PRIMENTA AIKATERINI-MARIA)

compilation: <path to cgal library>/CGAL-5.5.1/scripts/cgal_create_CMakeLists -s   optimal_polygon 
        	(optimal_polygon is the name of the executive program)
        	cmake -DCGAL_DIR=<path to cgal library>/CGAL-5.5.1 . -DCMAKE_BUILD_TYPE=Release
        	make

run:    	for local search algorithm:
        	./optimal_polygon -i <input file> -o <output file> -greedyalgorithm <incremental or convex_hull> -algorithm local_search -L -max -threshold <int>
            Choose an integer between 1 and 10 for L and a small integer for threshold. You can either run with -max for maximization or -min for minimization

        	for simulated annealing algorithm:

	        local step:
	        ./optimal_polygon -i <input file> -o <output file> -greedyalgorithm <incremental or convex_hull> -algorithm simulated_annealing -L -max -annealing local
            Choose a big value for L, for example -5000, again -max or -min for maximization or minimization 
        	
	        global step:
	        ./optimal_polygon -i <input file> -o <output file> -greedyalgorithm <incremental or convex_hull> -algorithm simulated_annealing -L -max -annealing global
            Choose a big value for L, for example -5000, again -max or -min for maximization or minimization 

	        subdivision:
            ./optimal_polygon -i <input file> -o <output file> -greedyalgorithm <incremental or convex_hull> -algorithm simulated_annealing -L -max -annealing subdivision
            Choose a big value for L, for example -5000, again -max or -min for maximization or minimization 


Recommendation: create an output file text in order to store the data of the program.

ALGORITHMS:

Local search:
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



Simulated annealing: 
There are 3 options in this algorithm. Simulated annealing with local step, with global step and with subdivision, which is a way to combine local and global steps.
For local and global step, there is a common function in the file localglobalstep.cpp, where depending on the value “an” given in main, it performs local or global steps. 
If an==1, local step, if an==2, global step. localglobalstep function performs the pseudocode given in the lesson, with some differences, 
such as we apply the transitions in the polygon only with metropolis criterion (not the difference in energy being negative) 
and then we decrease the temperature T, and we have set an upper bound of maximum iterations to be performed, in order to break the loop.

Local step: See localtranstep.cpp/localtranstep.h. These are the files for local step. We perform exactly the instructions in the lesson. While using the kd-tree, 
we create a fuzzy box (cgal) using 2 points with the minimum and maximum x and y of the 4 points we have (pqrs).

Global step: See globaltranstep.cpp/globaltranstep.h. These are the files for global step. We perform exactly the instructions in the lesson. 
Some parts of the globaltransitionstep function are used only in subdivision (boolean value).

Subdivision: See subdivision.cpp/subdivision.h. The function subdivision performs the algorithm being described in the lesson. 
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



As for the inputs.cpp file, where the main function is, in the initialization functions, we have chosen to pass the best parameters. 
For example, the parameter edge selection is the max and min whether we want maximum or minimum optimization.
For incremental, we chose sorting by x, from larger to smaller. The construction time is computed by the initialization of the polygon (incremental or convex_hull) until the end of the program. 
In case we want to compute the construction time of the optimization algorithms only, we can move clock() into the corresponding if-else part of the main function.  

There are some functions in localchange.cpp file that are not used in the program. We tried to implement a method to compute the area of a polygon recursively, 
using its convex hull and split it into triangles, by using area() function only for triangles but it turned out to take a lot of time, 
instead we used the area() function to compute the whole area of the polygon. 
We decided to keep them just because we thought it was a good algorithm for computing areas by ourselves. 