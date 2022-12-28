#include "triangle.h"

/*
This function takes in a Vector of points, creates a triangle out of it,
, removes the first three points from the vector, and returns the trianlge
in the form of a polygon.
*/
Polygon triangle(Vector *p){
    Vector temp=*p;

    Polygon pol;
    for(int i=0;i<3;i++){
        pol.push_back(temp[0]);
        temp.erase(temp.begin());
    }
    
    *p=temp;
    return pol;
}

/*This function takes in a vector of points and the protected segments.
*depending on the subset we are (first\last or in between) we create a
*triangle of the protected points and the first point of the vector, else
*we create a rectangle of the 4 protected points.
*/
Polygon rectangle(Vector *p, SegmentVector protect){
    Vector temp=*p;

    Polygon pol;
    if(protect.size()>1){
        pol.push_back(protect[0][0]);
        pol.push_back(protect[0][1]);
        pol.push_back(protect[1][0]);
        pol.push_back(protect[1][1]);
        temp.erase(std::find(temp.begin(),temp.end(),protect[1][1]));
        temp.erase(std::find(temp.begin(),temp.end(),protect[1][0]));
        temp.erase(std::find(temp.begin(),temp.end(),protect[0][1]));
        temp.erase(std::find(temp.begin(),temp.end(),protect[0][0]));
    }
    else{
        pol.push_back(protect[0][0]);
        pol.push_back(protect[0][1]);
        temp.erase(std::find(temp.begin(),temp.end(),protect[0][1]));
        temp.erase(std::find(temp.begin(),temp.end(),protect[0][0]));
        pol.push_back(temp[0]);
        temp.erase(temp.begin());
    }
    
    
    *p=temp;
    return pol;
}

