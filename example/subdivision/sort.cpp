#include "sort.h"

bool smx(Point a, Point b){        //smaller to larger x comperator
    return (a[0]<b[0]);
}

bool smy(Point a, Point b){        //smaller to larger y comperator
    return (a[1]<b[1]);
}

bool lrx(Point a, Point b){        //larger to smaller x comperator
    return (a[0]>b[0]);
}

bool lry(Point a, Point b){        //larger to smaller y comperator
    return (a[1]>b[1]);
}

/*
this function, takes in the vector of boints, a bool whether it wants x or y
and a bool whether it wants to go from smallest to largest or from largest to smallest
(Vector *p: the vector given eg &example, bool x=1 if true 0 if false, bool sm=1 if true 0 if false)
*/
Vector sortv(Vector *p, bool x, bool sm){
    Vector temp=*p;
    if(x){
        if(sm){
            std::sort(temp.begin(), temp.end(),smx);
        }
        else{
            std::sort(temp.begin(), temp.end(),lrx);
        }
    }
    else{
        if(sm){
            std::sort(temp.begin(), temp.end(),smy);
        }
        else{
            std::sort(temp.begin(), temp.end(),lry);
        }
    }
    return temp;
}

