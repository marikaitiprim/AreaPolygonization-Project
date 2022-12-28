#include "localglobalstep.h"

/*compute energy of a polygon. If maxmin = 1 -> maximization, if maxmin=0 -> minimization*/
double energy(Polygon pol, bool maxmin){
    int n = pol.size();
    Polygon cv;
    CGAL::convex_hull_2(pol.begin(),pol.end(),std::back_inserter(cv)); 
    if(maxmin){
        return (n*(1-(abs(pol.area())/abs(cv.area()))));
    }
    else{
        return (n*(abs(pol.area())/abs(cv.area())));
    }
}

/*metropolis criterion*/
bool metropolis(double T, double DE){
    double R = (double) rand()/RAND_MAX;       //find R
    double e = exp(-(DE/T));
    if(e>=R){
        return 1;
    }
    else{
        return 0;
    }
}

Polygon localglobalstep(Polygon pol,int an,int L,bool maxmin,bool subdivision,Point qlast, Point qfirst){
    double polenergy = energy(pol,maxmin);
    double T = 1.0;
    srand(time(NULL));
    int counter=0;        //count iterations
    while(T>=0){
        counter++;
        Polygon newpol;
        if(an==1){                                              //perform transition step
            //local step
            newpol = localtransitionstep(pol);
        }
        else if(an==2){ //global step
            newpol = globaltransitionstep(pol,subdivision,qlast,qfirst);
        }
        
        double newpolenergy = energy(newpol,maxmin);
        double DE = newpolenergy-polenergy;
        if(metropolis(T,DE)){             //metropolis
            pol = newpol;                           //apply transition
            T = T - (1/L);
        }

        if(counter>2*L){                //upper bound to break iterations
            break;
        }

    }
    return pol;
}