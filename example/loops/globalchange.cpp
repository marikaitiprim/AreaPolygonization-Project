#include "globalchange.h"

/*returns new polygon after applying changes */
Polygon applyChanges(EdgePath t, Polygon S){
    Polygon Snew = S;
    if(t.empty()){
        return S;
    }
    for(int i=0; i<t.size(); i++){          //for every pair [e,V] 
        Snew = changePolygon(Snew, t[i].v,t[i].e);  //apply to current polygon 
    }
    return Snew;
}


/*returns DA - if DA>0 we continue the loops, else there is no better solution*/
double difference(Polygon S, Polygon Snew){
    return abs(abs(Snew.area())-abs(S.area()));
}