#include "edgeselection.h"

//for incremental

/*function for the 1st edge selection criterion,
which takes a segment vector with a point and its visible edges and 
returns a random edge*/
Segment edgerand(SegmentVector* sv, Point* p){
    SegmentVector segv = *sv;
    int j = rand() % segv.size();
    return segv[j];
}

/*function for the 2nd and 3rd edge selection criterion, 
which takes a segment vector with the visible edges of a point,
the point and a boolean value: max=1 --> adding max area, max=0 --> adding min area. 
Returns the best visible edge*/
Segment edgeminmax(SegmentVector* sv, Point* p,bool max){
    SegmentVector segv = *sv;
    std::vector<double> areas;
    double e;
    for(int i=0; i<segv.size();i++){                  //for each visible segment
        Polygon polyg;
        polyg.push_back(*p);                        //create a triangle(polygon) with the given point and the points of the segment
        polyg.push_back(segv[i].vertex(0));
        polyg.push_back(segv[i].vertex(1));
        if(!polyg.is_counterclockwise_oriented()){
            polyg.reverse_orientation();             //make sure polygon orientation is counterclockwise
        }
        e = abs(polyg.area());                           //store the area of the triangle...
        areas.push_back(e);                            // ...into a vector    
    }
    if(max){                                        //edgeselection = 3, we want to add the max area
        int j=0;
        double maxi = areas[j]; 
        if(areas.size()>1){                             //more than one visible edge
            for(int i=1; i<areas.size(); i++){
                if(maxi<areas[i]){                      //find the maximum area
                    maxi = areas[i];
                    j = i;                              //store the position into the vector
                }
            }
        }
        else{
            j = 0;
        }
        return segv[j];                                   //return the segment been selected
    }
    else{                                           //find the minimum area
        int j=0;
        double mini = areas[j]; 
        if(areas.size()>1){                         //more than one visible edge
            for(int i=1; i<areas.size(); i++){
                if(mini>areas[i]){
                    mini = areas[i];
                    j = i;
                }
            }
        }
        else{
            j = 0;
        }
        return segv[j];                                   //return the segment been selected
    }
}

/*function that combines all 3 criteria for edge selection.
if edgeselect==1: random edge selection, edgeselect==2: adding min area,
edgeselect==3: adding max area*/
Segment edgeselection(SegmentVector* sv, Point* p, int edgeselect){
    Segment seg;
    srand(time(NULL));
    if(edgeselect==1){
        /*random choice for visible edge*/
        seg = edgerand(sv,p);
    }else if(edgeselect==2){
        /*min area*/
        seg = edgeminmax(sv,p,0);
    }
    else if(edgeselect==3){
        /*max area*/
        seg = edgeminmax(sv,p,1);
    }
    else{
        std::cout<< "Wrong number for edge selection" << std::endl;
        exit(1);
    }
    return seg;
}


//for convex hull

/*function for the 1st edge selection criterion,
which takes a vector of pairs and chooses a random
cell from there*/
PSpair edgerand2(PairVector* pv){
    PairVector paiv = *pv;
    int j = rand() % paiv.size();
    return paiv[j];
}

/*function for the 2nd and 3rd edge selection criterion, 
which takes a vector of pairs and chooses depending on
whether we want th maximum or minimum area, the appropriate
pair*/
PSpair edgeminmax2(PairVector* pv,bool max){
    PairVector paiv = *pv;
    std::vector<double> areas;
    double e;
    for(int i=0; i<paiv.size();i++){                  //for each visible segment
        Polygon polyg;
        polyg.push_back(paiv[i].first);                        //create a triangle(polygon) with the given point and the points of the segment
        polyg.push_back(paiv[i].second[0]);
        polyg.push_back(paiv[i].second[1]);
        if(!polyg.is_counterclockwise_oriented()){
            polyg.reverse_orientation();             //make sure polygon orientation is counterclockwise
        }
        e = abs(polyg.area());                           //store the area of the triangle...
        areas.push_back(e);                            // ...into a vector    
    }
    if(max){                                        //edgeselection = 3, we want to add the max area
        int j=0;
        double maxi = areas[j]; 
        if(areas.size()>1){                             //more than one visible edge
            for(int i=1; i<areas.size(); i++){
                if(maxi<areas[i]){                      //find the maximum area
                    maxi = areas[i];
                    j = i;                              //store the position into the vector
                }
            }
        }
        else{
            j = 0;
        }
        return paiv[j];                                   //return the segment been selected
    }
    else{                                           //find the minimum area
        int j=0;
        double mini = areas[j]; 
        if(areas.size()>1){                         //more than one visible edge
            for(int i=1; i<areas.size(); i++){
                if(mini>areas[i]){
                    mini = areas[i];
                    j = i;
                }
            }
        }
        else{
            j = 0;
        }
        return paiv[j];                                   //return the segment been selected
    }
}

/*function that combines all 3 criteria for edge selection.
if edgeselect==1: random edge selection, edgeselect==2: adding max area,
edgeselect==3: adding min area*/
PSpair edgeselection2(PairVector* tv, int edgeselect){
    PSpair temp;
    srand(time(NULL));
    if(edgeselect==1){
        /*random choice for visible edge*/
        temp = edgerand2(tv);
    }else if(edgeselect==2){
        /*max area of triangle => min area of polygon*/
        temp = edgeminmax2(tv,1);
    }
    else if(edgeselect==3){
        /*min area of triangle => max area of polygon*/
        temp = edgeminmax2(tv,0);
    }
    else{
        std::cout<< "Wrong number for edge selection" << std::endl;
        exit(1);
    }
    return temp;
}