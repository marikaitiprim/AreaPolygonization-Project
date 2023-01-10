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

Combinations:
