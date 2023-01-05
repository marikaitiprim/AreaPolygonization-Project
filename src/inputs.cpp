/*/home/marikaiti/CGAL-5.5.1/scripts/cgal_create_CMakeLists -s optimal_polygon
cmake -DCGAL_DIR=/home/marikaiti/CGAL-5.5.1 . -DCMAKE_BUILD_TYPE=Release
make
./optimal_polygon -i ../instances/data/uniform/uniform-0000200-1.instance -o output.txt -greedyalgorithm incremental -algorithm local_search -L -max -threshold 1

./optimal_polygon -i ../instances/data/uniform/uniform-0000400-1.instance -o output.txt -greedyalgorithm convex_hull -algorithm simulated_annealing -1 -min -annealing global
*/

#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <ctime>
#include "algorithms.h"
#include "loops.h"
#include "localglobalstep.h"
#include "subdivision.h"

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef vector<Point> Vector;

int main(int argc, char *argv[]){
    srand(time(0));
    clock_t t;

    //errors in arguments
    if(argc != 13){               //less args
        cout << "Please give the right the arguments" << endl;
        exit(1);
    }

    //store args in values
    const char* inputfile = argv[2];
    const char* outputfile = argv[4];
    const char* gralgorithm = argv[6];
    const char* optalgorithm = argv[8];
    char* Lamda = argv[9];
    const char* maxmin = argv[10]; 
    int algo, optalgo;
    char* initialization;

    if(!strcmp(gralgorithm,"incremental")){
        algo = 1;
    }
    else if(!strcmp(gralgorithm,"convex_hull")){
        algo = 2;
    }

    if(!strcmp(optalgorithm,"local_search")){
        optalgo = 1;
    }
    else if(!strcmp(optalgorithm,"simulated_annealing")){
        optalgo = 2;
    }

    bool max;
    int edgeselect;

    if(!strcmp(maxmin,"-max")){
        max = 1;                    //maximization
        edgeselect = 3;
    }
    else if(!strcmp(maxmin,"-min")){
        max = 0;                    //minimization
        edgeselect = 2;
    }

    int L = atoi(&Lamda[1]);

    //read file from input
    FILE* fp = fopen(inputfile, "r");       //open file
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char* line = NULL;
    size_t len = 0;
    int counter = 0;
    while ((getline(&line, &len, fp)) != -1) {  //read file line by line
        counter++;                              //count the lines
    }
    fclose(fp);                         //close file
    free(line);

    fp = fopen(inputfile, "r");       //reopen file
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int numofpoints = counter - 2;      //number of points in the file
    
    Vector points;        //initialize array of points

    len = 0;
    line = NULL;
    counter = 0;
    while ((getline(&line, &len, fp)) != -1) {  //read file line by line
        counter++;
        if(counter>2){  //reading 3rd line 

            char delimit[] = " \t";         //check for spaces and tabs

            line = strtok(line,"\n");       //remove \n character
            vector <char*> tokens;          //vector to store the tokens
            char *token = strtok(line,delimit); //split line by tab or by space

            while (token)  {
                tokens.push_back(token);
                token = strtok(NULL,delimit);   
            }

            points.push_back(Point(atoi(tokens[1]),atoi(tokens[2])));   //store the point into the vector of points
        }
    }
    free(line);
    fclose(fp);                         //close file

    //begin clock to see how much time it takes for the algorithm to run
    t = clock();
    Polygon pol;

    Polygon newpol;

    if(optalgo==1){
        //localsearch
        //check which algorithm has been chosen 
        if(algo==1){        //incremental
            pol = incremental(&points,edgeselect,1,0);

        }else if(algo==2){  ///convex hull
            pol = convex_hull(&points,edgeselect);
        }
        double threshold = atof(argv[12]);
        newpol = loops(pol,threshold,L,max);
    }else if(optalgo==2){
        //annealing
        char* annealing = argv[12];
        if(!strcmp(annealing,"local")){
            //check which algorithm has been chosen 
            if(algo==1){        //incremental
                pol = incremental(&points,edgeselect,1,0);

            }else if(algo==2){  ///convex hull
                pol = convex_hull(&points,edgeselect);
            }
            newpol = localglobalstep(pol,1,L,max,0,Point(-1,-1),Point(-1,-1));
        }
        else if(!strcmp(annealing,"global")){
            //check which algorithm has been chosen 
            if(algo==1){        //incremental
                pol = incremental(&points,edgeselect,1,0);

            }else if(algo==2){  ///convex hull
                pol = convex_hull(&points,edgeselect);
            }
            newpol = localglobalstep(pol,2,L,max,0,Point(-1,-1),Point(-1,-1));
        }
        else if(!strcmp(annealing,"subdivision")){
            if(algo==1){        //incremental
                pol = incremental(&points,edgeselect,1,0);          //initialization
                newpol = subdivision(points,100,1,edgeselect,L,max);

            }else if(algo==2){  ///convex hull
                pol = convex_hull(&points,edgeselect);                  //initialization
                newpol = subdivision(points,100,0,edgeselect,L,max);
            }
            if(newpol.is_empty()){
                return 1;
            }
        }

    }
    t = clock() - t;    //stop the clock

    ofstream outfile;
    outfile.open(outputfile);

    //prints to stdout & write to outputfile
    cout << "Optimal Area Polygonization" << endl;
    outfile << "Optimal Area Polygonization" << endl;
    for(int i=0; i<numofpoints; i++){   //print vector of points
        cout << points[i] << endl;
        outfile << points[i] << endl;   //write data to outputfile
    }

    Segment seg;
    for(int i=0; i<newpol.size(); i++){    //print edges
        if(i==newpol.size()-1){
            seg = Segment(newpol[i],newpol[0]);
        }
        else{
            seg = Segment(newpol[i],newpol[i+1]);
        }
        cout << seg << endl;
        outfile << seg << endl; //write data to outputfile
    }

    cout << "Algorithm: " << optalgorithm << maxmin << endl;
    outfile << "Algorithm: " << optalgorithm << maxmin << endl;

    cout << "area_initial " << abs(pol.area()) << endl;
    outfile << "area_initial: " << abs(pol.area()) << endl;  //write data to outputfile

    cout << "area: " << abs(newpol.area()) << endl;
    outfile << "area: " << abs(newpol.area()) << endl;  //write data to outputfile

    Polygon conh1,conh2;
    CGAL::convex_hull_2(pol.begin(),pol.end(),std::back_inserter(conh1));
    cout << "ratio_initial: " << pol.area()/conh1.area() << endl;
    outfile << "ratio_initial: " << pol.area()/conh1.area() << endl; //write data to outputfile

    CGAL::convex_hull_2(newpol.begin(),newpol.end(),std::back_inserter(conh2));
    cout << "ratio: " << newpol.area()/conh2.area() << endl;
    outfile << "ratio: " << newpol.area()/conh2.area() << endl; //write data to outputfile

    cout << "construction time: " << (int)((float)t*1000/CLOCKS_PER_SEC) << " milliseconds" << endl;
    outfile << "construction time: " << (int)((float)t*1000/CLOCKS_PER_SEC) << " milliseconds" << endl;   //write data to outputfile

    outfile.close();
}