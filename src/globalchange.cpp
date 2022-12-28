#include "globalchange.h"

/*returns new polygon after applying changes */
Polygon applyChanges(EdgePath t, Polygon S){
    Polygon Snew = S;
    if(t.empty()){
        return S;
    }  
    Polygon temp = changePolygon(Snew, t[0].v,t[0].e);  //apply to current polygon 
    Snew = temp;
    return Snew;
}


/*returns DA - if DA>0 we continue the loops, else there is no better solution*/
double difference(Polygon S, Polygon Snew){
    return abs(abs(Snew.area())-abs(S.area()));
}