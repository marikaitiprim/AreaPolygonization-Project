#include "close.h"

/*
*This function accepts a vector of points, a line and the polygon
*and finds the closest visible point from that vector to the line
*and returns it.
*/
Point closest(Vector vec, Segment seg, Polygon pol){
    Point cl;
    bool empty=true;
    for(int i=0;i<vec.size();i++){
        Point current=vec[i];      
            if(empty){
                if(!lineintersect(vec[i],seg,pol)){             //check if the point is visible
                    cl=vec[i];
                    empty=false;
                }
            }
            else{
                if(CGAL::squared_distance(vec[i],seg)<CGAL::squared_distance(cl,seg)){      //calculate distance from the previous smallest point, using squared distance.
                    if(!lineintersect(vec[i],seg,pol)){         //check if the point is visible
                        cl=vec[i];
                    }
                }
        }
    }
    if(empty){
        return Point(-1,-1);            //if no point is visible, return a negative Point, since all our points are positive.
    }
    return cl;              //return closest point

};