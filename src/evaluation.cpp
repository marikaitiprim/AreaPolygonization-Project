//./evaluate -i ../instances/data/uniform/ -o output.txt
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
#include <dirent.h>
#include <thread>
#include <future>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef vector<Point> Vector;
typedef vector<int> Size;
typedef vector<double> Score;
typedef vector<Score> Storescore;

static int timeout = 0;
static void alarm_handler(int sig){
    //kill thread
    timeout = 1;
    cout << "bye" << endl;
    exit(-1);
}

Polygon algorithm1(Vector points){
    struct sigaction sact;
    sigemptyset( &sact.sa_mask );
    sact.sa_flags = 0;
    sact.sa_handler = alarm_handler;
    sigaction( SIGALRM, &sact, NULL );

    int cutoff = points.size();
    alarm(cutoff);
    Polygon pol = incremental(&points,3,1,1);
    cout << "area before " << pol.area() << endl;
    Polygon newpol = loops(pol,1.5,10,1);
    return newpol;
}

int main(int argc, char *argv[]){

    clock_t t;

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
    int cutoff;
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
            }


            //algorithm1
            t = clock();
            auto future = async(algorithm1,points);
            future.wait();
            t = clock() - t;    //stop the clock

            if(timeout){           //run out of time
                cout << "out of time!" << endl;
            }
            else{               //receive data
                Polygon pol = future.get();
                cout << "area " << pol.area() << endl; 
                cout << "construction time: " << (int)((float)t*1000/CLOCKS_PER_SEC) << " milliseconds" << endl;
            }

        }   

        ofstream outfile;
        outfile.open(outputfile);

        //prints to stdout & write to outputfile
        cout << "//algorithms" << endl;
        outfile << "//algorithms" << endl;

        cout << "Size   || minscore | max score | min bound | max bound ||" << endl;
        outfile << "Size   || minscore | max score | min bound | max bound ||" << endl;

        for(int k=0; k<pointsize.size(); k++){      //for every point size
            cout << pointsize[k] << "   || ";
            outfile << pointsize[k] << "   || ";

            /*for(int j=0; j<stscores[k].size(); j+=4){    
                cout << stscores[k][j] << " | " << stscores[k][j+1] << " | " << stscores[k][j+2] << " | " << stscores[k][j+3] << " || ";
                outfile << stscores[k][j] << " | " << stscores[k][j+1] << " | " << stscores[k][j+2] << " | " << stscores[k][j+3] << " || ";
            }*/

            cout << endl;
            outfile << endl;
        }

        
        outfile.close();
        closedir (dir);
    } 
    else {
        perror ("cannot open the directory");
        return EXIT_FAILURE;
    }
    
}