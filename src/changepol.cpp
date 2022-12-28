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
    int inpoint=0;      //where in oyr polygon the path enters
    int erpoint=0;      //from where in our polygon we must erase the path
    bool er=0;
    bool in=0;
    for(const Point& pv : newpol.vertices() ){
        if(pv==Path[0]){
            erpoint=counter;        //if we find the first point of the path, we know from where we should start erasing
            er=1;
        }
        else if(pv==edge[0]){
            inpoint=counter;        //if we find the first point of the edge, we know after which point to put in the path
            in=1;
        }
        else if(in==1&&er==1){
            break;                  //once we find both, we can stop looking
        }
        counter++;
    }
    if(inpoint>erpoint){
        inpoint-=Path.size();       //if the entrance point is after the erase point, we should go back as many points as the path is

    }
    for(int i=0;i<Path.size();i++){ //erase path
        if(erpoint>=newpol.size()){
            inpoint-=Path.size()-i; //if path goes from the last to the first point, we need to adjust them
            erpoint=1;
        }
        newpol.erase(newpol.vertices_begin()+erpoint-1);
    }

    for(int i=Path.size()-1;i>=0;i--){                          //insert path
        newpol.insert(newpol.vertices_begin()+inpoint,Path[i]);
    }
    return newpol;
}