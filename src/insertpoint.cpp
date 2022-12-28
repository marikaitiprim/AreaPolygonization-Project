#include "insertpoint.h"

/*function that inserts a point to a polygon, in the place of the
given edge*/
Polygon insertpoint(Polygon* polyg, Point* p, Segment* e){
    Polygon temp=*polyg;
    int counter = 1;
    for(const Point& pv : temp.vertices() ){        //for each vertex in the polygon
        if(pv==e->vertex(0)){                       //if the point of the vertex is equal to the first point of our segment
            temp.insert(temp.vertices_begin()+counter,*p);    //insert the point in this place
            break;
        }
        counter++;
    }
    *polyg=temp;
    return *polyg;
}