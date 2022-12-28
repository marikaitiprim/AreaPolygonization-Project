#include "subdivision.h"
#include "sort.h"

Subsets splitsubsets(Vector points, int m){
    int n=points.size();
    Vector sortpoints = sortv(&points,1,1);              //sort points by increasing x
    for(int i=0; i<sortpoints.size(); i++){
        std::cout << sortpoints[i] << std::endl;
    }

    int start=0,end=m, k = (int)(n/m);
    if(n%m>0){
        k++;
    }
    std::cout << k << std::endl;
    Subsets subsets;                    //vector to store all the subsets
    for(int i=0; i<k; i++){             //for every subset
        Vector sub;
        for(int j=start; j<end; j++){   //push m-1 points in the subset
            sub.push_back(sortpoints[j]);
        }
        if(i<k-1){                      //not in the last subset
            while(sub.size()>0){
                if(sub[sub.size()-1][1]>sub[sub.size()-2][1]&&sub[sub.size()-1][1]>sortpoints[start+sub.size()][1]){
                    subsets.push_back(sub);         //push subset in vector with subsets
                    start=start+sub.size()-1;
                    end=end+sub.size()-1;        //we want to have the last point of this sub at the first position of the next sub
                    break;
                }
                else{
                    sub.pop_back();
                }
            }
        }
        subsets.push_back(sub);         //push subset in vector with subsets
        start = start+m;
        end = end+m;
        if(end>n){
            end=n;
        }
    }

    for(int i=0; i<subsets.size(); i++){
        std::cout << "------------subset " << i <<":---------------" << std::endl;
        for(int j=0; j<subsets[i].size(); j++){
            std::cout << subsets[i][j] << std::endl;
        }
    }
    return subsets;

}


void subdivision(Vector points,int m, bool incremental){
    Subsets subs = splitsubsets(points,m);
}