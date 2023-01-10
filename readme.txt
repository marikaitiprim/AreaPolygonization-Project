Evaluation of combinations of algorithms in polygonization using CGAL library.

ΚΑΜΑΡΗΣ ΑΓΓΕΛΟΣ sdi1900070  (KAMARIS ANGELOS)
ΠΡΙΜΕΝΤΑ ΑΙΚΑΤΕΡΙΝΗ-ΜΑΡΙΑ sdi1900160 (PRIMENTA AIKATERINI-MARIA)

compilation: <path to cgal library>/CGAL-5.5.1/scripts/cgal_create_CMakeLists -s evaluate 
        	(evaluate is the name of the executive program)
        	cmake -DCGAL_DIR=<path to cgal library>/CGAL-5.5.1 . -DCMAKE_BUILD_TYPE=Release
        	make

run:    	./evaluate -i <path to catalogue> -o output.txt
			<path to catalogue>: written as ../<foldername>/
			SOS: the last slash of the path is obligatory.

Recommendation: create an output file text in order to store the data of the program.

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
with a point (since we check the two points of the edge, this was reduntand), instead of checking for every edge and every point, after some 800 points, we only
check random points and edges in local search
