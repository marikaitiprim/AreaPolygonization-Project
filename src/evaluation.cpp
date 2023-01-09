//./evaluate -i ../instances/data/uniform/ -o output.txt
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <dirent.h>
#include "evalalgorithms.h"
#define AL 4

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef vector<Point> Vector;
typedef vector<int> Size;
typedef vector<double> Score;
typedef vector<Score> Storescore;

int main(int argc, char *argv[]){

    clock_t t,t1,t2;
    Polygon pol,newpol;
    int tml;

    //errors in arguments
    if(argc != 5 && argc != 7){               //less args
        cout << "Please give the right the arguments" << endl;
        exit(1);
    }

    //store args in values
    const char* inputfolder = argv[2];
    const char* outputfile = argv[4];
    char* inputfile;
    if(argc==7){        //preprocess argument
        //preprocessing
    }

    DIR *dir;
    struct dirent *folder;
    Size pointsize;                                     //vector to store the point size of each file
    Storescore stscores;                                //vector to store the vectors with the scores for each size
    int num_of_algorithms = 0;
    double score_max, score_min, bound_max, bound_min;

    ofstream outfile;
    outfile.open(outputfile);

    while(num_of_algorithms< AL){                       //count the algorithms
        num_of_algorithms++;
        if(!stscores.empty()){
            stscores.clear();
        }
        if(!pointsize.empty()){
            pointsize.clear();
        }
        if ((dir = opendir (inputfolder)) != nullptr) {
            while ((folder = readdir (dir)) != nullptr) {
                inputfile = folder->d_name;
                if(!strcmp(inputfile,".") || !strcmp(inputfile,"..")){
                    continue;
                }
                printf ("%s\n", inputfile);

                char path[100];
                stpcpy(path,inputfolder);
                strcat(path,inputfile);             //make whole path of the file

                FILE* fp = fopen(path, "r");       //open file
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

                fp = fopen(path, "r");       //reopen file
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

                int position = -1;
                for(int i=0; i<pointsize.size(); i++){
                    if(pointsize[i]==points.size()){            //check if we have already evaluate a file with the same point size
                        position = i;                           //save the position in the vector
                        break;
                    }
                }

                if(position == -1){    //first time evaluating this size of points
                    pointsize.push_back(points.size());
                    position = pointsize.size()-1;
                    //set scores to 0 and set bounds
                    Score tempsc;
                    tempsc.push_back(0.0);
                    tempsc.push_back(0.0);
                    tempsc.push_back(0.0);
                    tempsc.push_back(1.0);
                    stscores.push_back(tempsc);
                    
                }

                Polygon cpol;
                CGAL::convex_hull_2(points.begin(),points.end(),std::back_inserter(cpol));

                //algorithm1
                if(num_of_algorithms==1){
                    double res1=algorithm1(points,1);        //max
                    if((res1!=1.0)&&(res1!=0.0)){       
                        score_max = abs(res1)/abs(cpol.area());
                        std::cout << "\tResult of algorithm1 max is: " << score_max << std::endl;
                    }else{
                        score_max = res1;
                    }

                    res1=algorithm1(points,0);        //min
                    if((res1!=1.0)&&(res1!=0.0)){ 
                        score_min = abs(res1)/abs(cpol.area());      
                        std::cout << "\tResult of algorithm1 min is: " << score_min << std::endl;
                    }else{
                        score_min = res1;
                    }
                }
                else if(num_of_algorithms==2){
                    //algorithm 2
                    double res2=algorithm2(points,1);       //max
                    if((res2!=1.0)&&(res2!=0.0)){
                        score_max = abs(res2)/abs(cpol.area());
                        std::cout << "\tResult of algorithm2 max is: " << score_max << std::endl;
                    }
                    else{
                        score_max = res2;
                    }

                    res2=algorithm2(points,0);       //min
                    if((res2!=1.0)&&(res2!=0.0)){
                        score_min = abs(res2)/abs(cpol.area());
                        std::cout << "\tResult of algorithm2 min is: " << score_min << std::endl;
                    }
                    else{
                        score_min = res2;
                    }
                }
                else if(num_of_algorithms==3){
                    //algorithm 3
                    double res3=algorithm3(points,1);       //max
                    if((res3!=1.0)&&(res3!=0.0)){
                        score_max = abs(res3)/abs(cpol.area());
                        std::cout << "\tResult of algorithm3 max is: " << score_max << std::endl;
                    }
                    else{
                        score_max = res3;
                    }

                    res3=algorithm3(points,0);       //min
                    if((res3!=1.0)&&(res3!=0.0)){
                        score_min = abs(res3)/abs(cpol.area());
                        std::cout << "\tResult of algorithm3 min is: " << score_min << std::endl;
                    }
                    else{
                        score_min = res3;
                    }
                }
                else if(num_of_algorithms==4){
                    //algorithm 4
                    double res4=algorithm4(points,1);       //max
                    if((res4!=1.0)&&(res4!=0.0)){
                        score_max = abs(res4)/abs(cpol.area());
                        std::cout << "\tResult of algorithm4 max is: " << score_max << std::endl;
                    }
                    else{
                        score_max = res4;
                    }

                    res4=algorithm4(points,0);       //min
                    if((res4!=1.0)&&(res4!=0.0)){
                        score_min = abs(res4)/abs(cpol.area());
                        std::cout << "\tResult of algorithm4 min is: " << score_min << std::endl;
                    }
                    else{
                        score_min = res4;
                    }
                }

                //save scores to the appropriate position
                Score tempscore = stscores[position];
                tempscore[0] += score_min;
                bound_min = tempscore[2];
                if(score_min>bound_min){        //bound for min
                    tempscore[2] = score_min;
                }
                tempscore[1] += score_max;
                bound_max = tempscore[3];
                if(score_max<bound_max){        //bound for max
                    tempscore[3] = score_max;
                }
                stscores.erase(stscores.begin()+position);
                stscores.insert(stscores.begin()+position, tempscore);

            } 
            closedir(dir);  

            //prints to stdout & write to outputfile
            cout << "Algorithm " << num_of_algorithms << endl;
            outfile << "Algorithm " << num_of_algorithms << endl;

            cout << "Size   || minscore | max score | min bound | max bound ||" << endl;
            outfile << "Size   || minscore | max score | min bound | max bound ||" << endl;

            while(!pointsize.empty()){     
                int minelement = distance(begin(pointsize), min_element(begin(pointsize), end(pointsize)));

                cout << pointsize[minelement] << "   || ";
                outfile << pointsize[minelement] << "   || ";

                Score tsc = stscores[minelement];
                  
                cout << tsc[0] << " | " << tsc[1] << " | " << tsc[2] << " | " << tsc[3] << " || "; 
                outfile << tsc[0] << " | " << tsc[1] << " | " << tsc[2] << " | " << tsc[3] << " || "; 

                cout << endl;
                outfile << endl;

                pointsize.erase(pointsize.begin()+minelement);
                stscores.erase(stscores.begin()+minelement);
            }
        } 
        else {
            perror ("cannot open the directory");
            return EXIT_FAILURE;
        }
    }
    outfile.close();
    
}