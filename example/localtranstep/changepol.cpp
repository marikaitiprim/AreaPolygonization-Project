// /home/angelos/CGAL-5.5.1/scripts//cgal_create_CMakeLists -s sort
// cmake -DCGAL_DIR=/home/angelos/CGAL-5.5.1 .
// make

#include "changepol.h"

/*This function takes a polygon, a vector and a segment.
*the vector holds the points inside the path, while the segment represents our edge.
*We first locate the first point of our polygon where we remove the polygon and the
*first point of the edge, after which we insert the path, and erase and insert them
*accordingly.
*/
Polygon changePolygon(Polygon pol, Vector Path, Segment edge){
    Polygon newpol=pol;
    int counter= 1;
    int inpoint=0;
    int erpoint=0;
    bool er=0;
    bool in=0;
    for(const Point& pv : newpol.vertices() ){
        if(pv==Path[0]){
            erpoint=counter;
            er=1;
        }
        else if(pv==edge[0]){
            inpoint=counter;
            in=1;
        }
        else if(in==1&&er==1){
            break;
        }
        counter++;
    }
    if(inpoint>erpoint){
        inpoint-=Path.size();

    }
    for(int i=0;i<Path.size();i++){
        if(erpoint>=newpol.size()){
            inpoint-=Path.size()-i;
            erpoint=1;
        }
        newpol.erase(newpol.vertices_begin()+erpoint-1);
    }

    for(int i=Path.size()-1;i>=0;i--){
        newpol.insert(newpol.vertices_begin()+inpoint,Path[i]);
    }
    return newpol;
}