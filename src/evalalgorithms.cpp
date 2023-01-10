#include "evalalgorithms.h"

using namespace std;

//incremental + local search
double algorithm1(Vector points, bool max, bool sm, bool x, double th, int L){
    clock_t t,t1,t2;
    Polygon pol,newpol;
    int tml,edgeselect=2;
    double ret=1.0;      //minimization failed
    if(max){
        ret=0.0;        //maximization failed
        edgeselect = 3; //for incremental
    }

    t = clock();        //start clock for the whole algorithm      
    pol = incremental(&points, edgeselect, x, sm);
    t1 = clock() - t;                             //stop clock for incremental
    tml = (int)((float)t1*1000/CLOCKS_PER_SEC);      

    if(pol.area()==0){
        //failed
        return ret;
    }
    newpol = loops(pol, th, L, max, tml);
    t2 = clock() - t;                               //stop clock for local search
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      

    if(newpol.area()==0){
        //failed
        return ret;
    }

    t = clock() - t;    //stop the clock of the whole algorithm
    return newpol.area();

}

//incremental + local search + global step
double algorithm2(Vector points, bool max, bool sm, bool x, double th, int L){
    clock_t t,t1,t2;
    Polygon pol,newpol;
    int tml,edgeselect=2;
    double ret=1.0;      //minimization failed
    if(max){
        ret=0.0;        //maximization failed
        edgeselect = 3;
    }

    t = clock();        //start clock for the whole algorithm      
    pol = incremental(&points, edgeselect, x, sm);
    t1 = clock() - t;                             //stop clock for incremental
    tml = (int)((float)t1*1000/CLOCKS_PER_SEC);      

    if(pol.area()==0){
        //failed
        return ret;
    }
    newpol = loops(pol, th, L, max, tml);
    t2 = clock() - t;                               //stop clock for local search
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      


    if(newpol.area()==0){
        //failed
        return ret;
    }
    
    newpol = localglobalstep(newpol,2,6000,max,0,Point(-1,-1),Point(-1,-1),tml);
    t2 = clock() - t;                               //stop clock for local step
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      

    if(newpol.area()==0){
        //failed
        return ret;
    }

    t = clock() - t;    //stop the clock of the whole algorithm
    return newpol.area();

}

//incremental + global step + local step
double algorithm3(Vector points, bool max, bool sm, bool x){
    clock_t t,t1,t2;
    Polygon pol,newpol;
    int tml,edgeselect=2;
    double ret=1.0;      //minimization failed
    if(max){
        ret=0.0;        //maximization failed
        edgeselect = 3;
    }

    t = clock();        //start clock for the whole algorithm      
    pol = incremental(&points, edgeselect, x, sm);
    t1 = clock() - t;                             //stop clock for incremental
    tml = (int)((float)t1*1000/CLOCKS_PER_SEC);      

    if(pol.area()==0){
        //failed
        return ret;
    }
    newpol = localglobalstep(pol,2,6000,max,0,Point(-1,-1),Point(-1,-1),tml);
    t2 = clock() - t;                               //stop clock for global step
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      

    if(newpol.area()==0){
        //failed
        return ret;
    }
        
    newpol = localglobalstep(pol,1,6000,max,0,Point(-1,-1),Point(-1,-1),tml);
    t2 = clock() - t;                               //stop clock for local step
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      

    if(newpol.area()==0){
        //failed
        return ret;
    }

    t = clock() - t;    //stop the clock of the whole algorithm
    return newpol.area();

}

//subdivision(with convex hull) + local step
double algorithm4(Vector points, bool max, int sub){
    clock_t t,t1,t2;
    Polygon pol,newpol;
    int tml,edgeselect=2;
    double ret=1.0;      //minimization failed
    if(max){
        ret=0.0;        //maximization failed
        edgeselect = 3;
    }

    t = clock();        //start clock for the whole algorithm      
    tml = (int)((float)t*1000/CLOCKS_PER_SEC); 
    pol = subdivision(points,sub,0,edgeselect,6000,max,tml);     ///with convex_hull
    t1 = clock() - t;                               //stop clock for subdivision
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      

    if(pol.area()==0){
        //failed
        return ret;
    }
        
    newpol = localglobalstep(pol,1,6000,max,0,Point(-1,-1),Point(-1,-1),tml);
    t2 = clock() - t;                               //stop clock for local step
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      

    if(newpol.area()==0){
        //failed
        return ret;
    }

    t = clock() - t;    //stop the clock of the whole algorithm
    return newpol.area();

}

//subdivision(with convex hull) + global step
double algorithm5(Vector points, bool max, int sub){
    clock_t t,t1,t2;
    Polygon pol,newpol;
    int tml,edgeselect=2;
    double ret=1.0;      //minimization failed
    if(max){
        ret=0.0;        //maximization failed
        edgeselect = 3;
    }

    t = clock();        //start clock for the whole algorithm      
    tml = (int)((float)t*1000/CLOCKS_PER_SEC); 
    pol = subdivision(points,sub,0,edgeselect,6000,max,tml);     ///with convex_hull
    t1 = clock() - t;                               //stop clock for subdivision
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      

    if(pol.area()==0){
        //failed
        return ret;
    }
        
    newpol = localglobalstep(pol,2,6000,max,0,Point(-1,-1),Point(-1,-1),tml);
    t2 = clock() - t;                               //stop clock for global step
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      

    if(newpol.area()==0){
        //failed
        return ret;
    }

    t = clock() - t;    //stop the clock of the whole algorithm
    return newpol.area();

}

//subdivision(with convex hull) + global step + local step
double algorithm6(Vector points, bool max, int sub){
    clock_t t,t1,t2;
    Polygon pol,newpol;
    int tml,edgeselect=2;
    double ret=1.0;      //minimization failed
    if(max){
        ret=0.0;        //maximization failed
        edgeselect = 3;
    }

    t = clock();        //start clock for the whole algorithm      
    tml = (int)((float)t*1000/CLOCKS_PER_SEC); 
    pol = subdivision(points,sub,0,edgeselect,6000,max,tml);     ///with convex_hull
    t1 = clock() - t;                               //stop clock for subdivision
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      

    if(pol.area()==0){
        //failed
        return ret;
    }
        
    newpol = localglobalstep(pol,2,6000,max,0,Point(-1,-1),Point(-1,-1),tml);
    t2 = clock() - t;                               //stop clock for global step
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      

    if(newpol.area()==0){
        //failed
        return ret;
    }

    newpol = localglobalstep(newpol,1,6000,max,0,Point(-1,-1),Point(-1,-1),tml);
    t2 = clock() - t;                               //stop clock for local step
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      

    if(newpol.area()==0){
        //failed
        return ret;
    }

    t = clock() - t;    //stop the clock of the whole algorithm
    return newpol.area();

}

//subdivision(with convex hull) + local step + global step
double algorithm7(Vector points, bool max, int sub){
    clock_t t,t1,t2;
    Polygon pol,newpol;
    int tml,edgeselect=2;
    double ret=1.0;      //minimization failed
    if(max){
        ret=0.0;        //maximization failed
        edgeselect = 3;
    }

    t = clock();        //start clock for the whole algorithm      
    tml = (int)((float)t*1000/CLOCKS_PER_SEC); 
    pol = subdivision(points,sub,0,edgeselect,6000,max,tml);     ///with convex_hull
    t1 = clock() - t;                               //stop clock for subdivision
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      

    if(pol.area()==0){
        //failed
        return ret;
    }
        
    newpol = localglobalstep(pol,1,6000,max,0,Point(-1,-1),Point(-1,-1),tml);
    t2 = clock() - t;                               //stop clock for local step
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      

    if(newpol.area()==0){
        //failed
        return ret;
    }

    newpol = localglobalstep(newpol,2,6000,max,0,Point(-1,-1),Point(-1,-1),tml);
    t2 = clock() - t;                               //stop clock for global step
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      

    if(newpol.area()==0){
        //failed
        return ret;
    }

    t = clock() - t;    //stop the clock of the whole algorithm
    return newpol.area();

}