#include "evalalgorithms.h"

using namespace std;

//incremental + local search
double algorithm1(Vector points, bool max){
    std::cout << "starting algorithm1 for max:"<<max << std::endl;
    clock_t t,t1,t2;
    Polygon pol,newpol;
    int tml,edgeselect=2;
    double ret=1.0;      //minimization failed
    if(max){
        ret=0.0;        //maximization failed
        edgeselect = 3; //for incremental
    }

    t = clock();        //start clock for the whole algorithm      
    pol = incremental(&points, edgeselect, 1, 1);
    t1 = clock() - t;                             //stop clock for incremental
    tml = (int)((float)t1*1000/CLOCKS_PER_SEC);      
    std::cout << "Incremental time: " << tml << std::endl;

    if(pol.area()==0){
        //failed
        cout << "failed" << endl;
        return ret;
    }
    cout << "area incremental " << pol.area() << endl;
    newpol = loops(pol, 1.5, 10, max, tml);
    t2 = clock() - t;                               //stop clock for local search
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      
    std::cout << "Local search time: " << (int)((float)(t2-t1)*1000/CLOCKS_PER_SEC) << std::endl;
    std::cout << "Total: " << tml << std::endl;

    if(newpol.area()==0){
        //failed
        cout << "failed" << endl;
        return ret;
    }else{
        cout << "area local search " << newpol.area() << endl;
    }

    t = clock() - t;    //stop the clock of the whole algorithm
    cout << "construction time: " << (int)((float)t*1000/CLOCKS_PER_SEC) << " milliseconds" << endl;
    return newpol.area();

}

//incremental + global step
double algorithm2(Vector points, bool max){
    std::cout << "starting algorithm2 for max:"<<max << std::endl;
    clock_t t,t1,t2;
    Polygon pol,newpol;
    int tml,edgeselect=2;
    double ret=1.0;      //minimization failed
    if(max){
        ret=0.0;        //maximization failed
        edgeselect = 3;
    }

    t = clock();        //start clock for the whole algorithm      
    pol = incremental(&points, edgeselect, 1, 1);
    t1 = clock() - t;                             //stop clock for incremental
    tml = (int)((float)t1*1000/CLOCKS_PER_SEC);      
    std::cout << "Incremental time: " << tml << std::endl;

    if(pol.area()==0){
        //failed
        cout << "failed" << endl;
        return ret;
    }
    cout << "area incremental " << pol.area() << endl;
    newpol = localglobalstep(pol,2,6000,max,0,Point(-1,-1),Point(-1,-1),tml);
    t2 = clock() - t;                               //stop clock for local step
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      
    std::cout << "global step time: " << (int)((float)(t2-t1)*1000/CLOCKS_PER_SEC) << std::endl;
    std::cout << "Total: " << tml << std::endl;

    if(newpol.area()==0){
        //failed
        cout << "failed" << endl;
        return ret;
    }else{
        cout << "area global step " << newpol.area() << endl;
    }

    t = clock() - t;    //stop the clock of the whole algorithm
    cout << "construction time: " << (int)((float)t*1000/CLOCKS_PER_SEC) << " milliseconds" << endl;
    return newpol.area();

}

//incremental + global step + local step
double algorithm3(Vector points, bool max){
    std::cout << "starting algorithm3 for max:"<<max << std::endl;
    clock_t t,t1,t2;
    Polygon pol,newpol;
    int tml,edgeselect=2;
    double ret=1.0;      //minimization failed
    if(max){
        ret=0.0;        //maximization failed
        edgeselect = 3;
    }

    t = clock();        //start clock for the whole algorithm      
    pol = incremental(&points, edgeselect, 1, 1);
    t1 = clock() - t;                             //stop clock for incremental
    tml = (int)((float)t1*1000/CLOCKS_PER_SEC);      
    std::cout << "Incremental time: " << tml << std::endl;

    if(pol.area()==0){
        //failed
        cout << "failed" << endl;
        return ret;
    }
    cout << "area incremental " << pol.area() << endl;
    newpol = localglobalstep(pol,2,6000,max,0,Point(-1,-1),Point(-1,-1),tml);
    t2 = clock() - t;                               //stop clock for global step
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      
    std::cout << "global step time: " << (int)((float)(t2-t1)*1000/CLOCKS_PER_SEC) << std::endl;

    if(newpol.area()==0){
        //failed
        cout << "failed" << endl;
        return ret;
    }
        
    cout << "area global step " << newpol.area() << endl;
    newpol = localglobalstep(pol,1,6000,max,0,Point(-1,-1),Point(-1,-1),tml);
    t2 = clock() - t;                               //stop clock for local step
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      
    std::cout << "local step time: " << (int)((float)(t2-t1)*1000/CLOCKS_PER_SEC) << std::endl;
    std::cout << "Total: " << tml << std::endl;

    if(newpol.area()==0){
        //failed
        cout << "failed" << endl;
        return ret;
    }
    cout << "area local step " << newpol.area() << endl;

    t = clock() - t;    //stop the clock of the whole algorithm
    cout << "construction time: " << (int)((float)t*1000/CLOCKS_PER_SEC) << " milliseconds" << endl;
    return newpol.area();

}

//incremental + subdivision + local step
double algorithm4(Vector points, bool max){
    std::cout << "starting algorithm4 for max:"<<max << std::endl;
    clock_t t,t1,t2;
    Polygon pol,newpol;
    int tml,edgeselect=2;
    double ret=1.0;      //minimization failed
    if(max){
        ret=0.0;        //maximization failed
        edgeselect = 3;
    }

    t = clock();        //start clock for the whole algorithm      
    pol = incremental(&points, edgeselect, 1, 1);
    t1 = clock() - t;                             //stop clock for incremental
    tml = (int)((float)t1*1000/CLOCKS_PER_SEC);      
    std::cout << "Incremental time: " << tml << std::endl;

    if(pol.area()==0){
        //failed
        cout << "failed" << endl;
        return ret;
    }
    cout << "area incremental " << pol.area() << endl;
    //------------------------------------
    int sub;
    if(pol.size() < 1000){      ///just for now - check it please
        sub = pol.size()/2;     //preprocessing
    }else{
        sub = 100;
    }
    //----------------------------
    newpol = subdivisionPol(pol,sub,0,edgeselect,6000,max,tml);     ///with convex_hull
    t2 = clock() - t;                               //stop clock for subdivision
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      
    std::cout << "subdivision time: " << (int)((float)(t2-t1)*1000/CLOCKS_PER_SEC) << std::endl;

    if(newpol.area()==0){
        //failed
        cout << "failed" << endl;
        return ret;
    }
        
    cout << "area subdivision " << newpol.area() << endl;
    newpol = localglobalstep(pol,1,6000,max,0,Point(-1,-1),Point(-1,-1),tml);
    t2 = clock() - t;                               //stop clock for local step
    tml = (int)((float)t2*1000/CLOCKS_PER_SEC);      
    std::cout << "local step time: " << (int)((float)(t2-t1)*1000/CLOCKS_PER_SEC) << std::endl;
    std::cout << "Total: " << tml << std::endl;

    if(newpol.area()==0){
        //failed
        cout << "failed" << endl;
        return ret;
    }
    cout << "area local step " << newpol.area() << endl;

    t = clock() - t;    //stop the clock of the whole algorithm
    cout << "construction time: " << (int)((float)t*1000/CLOCKS_PER_SEC) << " milliseconds" << endl;
    return newpol.area();

}