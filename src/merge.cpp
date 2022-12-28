// /home/angelos/CGAL-5.5.1/scripts//cgal_create_CMakeLists -s ex
// cmake -DCGAL_DIR=/home/angelos/CGAL-5.5.1 . -DCMAKE_BUILD_TYPE=Release
// make

#include "merge.h"


/*This function takes in two polygons, finds where the first polygon has a common point with the first point of the second
*and inserts before that point all the points of the second polygon
*/
Polygon mergePolygon(Polygon first,Polygon second){
    int inpoint;
    for(int i=0;i<first.size();i++){
        if(first[i]==second[0]){
            inpoint=i;
            break;
        }
    }
    for(int i=1;i<second.size();i++){
     first.insert(first.vertices_begin()+inpoint+i-1,second[i]);   
    }
    return first;
    
}