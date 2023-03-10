#include "localtranstep.h"

/*return 1 if the 2 segments have a common point, else 0*/
bool commonpoint_check(Segment a, Segment b){
    if(a.vertex(0)==b.vertex(0) || a.vertex(0)==b.vertex(1) || a.vertex(1)==b.vertex(0) || a.vertex(1)==b.vertex(1)){
        return 1;
    }
    return 0;
}

/*check if new polygon is valid*/
int checkValidity(Polygon pol,Segment pr, Segment qs, kTree* kdtree,int tim){
    int cutoff = 500*pol.size();
    int tms = (int)((float)clock()*1000/CLOCKS_PER_SEC) + tim;        //starting  milliseconds
    int tml;

    tml = (int)((float)clock()*1000/CLOCKS_PER_SEC) - tms;      //milliseconds until now
    if(tml>= cutoff){       //check cutoff
        return -1;
    }

    //a) new edges do not intersect each other
    if(intersect_check(pr,qs)){
        return 0;
    }
    //b) new edges do not intersect another edge in the polygon

    Xy X,Y;
    Vector pqrs;                            //store p,q,r,s into a vector
    pqrs.push_back(pr.vertex(0));
    pqrs.push_back(pr.vertex(1));
    pqrs.push_back(qs.vertex(0));
    pqrs.push_back(qs.vertex(1));

    for(int i=0; i<pqrs.size(); i++){       
        X.push_back(pqrs[i].x());
        Y.push_back(pqrs[i].y());
    }

    int xmin = *std::min_element(X.begin(),X.end());        //find min x value from p,q,r,s
    int ymin = *std::min_element(Y.begin(),Y.end());        //find min y value from p,q,r,s

    Point min = Point(xmin,ymin);                           //create new point with min x and y

    int xmax = *std::max_element(X.begin(),X.end());        //find max x value from p,q,r,s
    int ymax = *std::max_element(Y.begin(),Y.end());        //find max y value from p,q,r,s

    Point max = Point(xmax,ymax);                           //create new point with max x and y
    
    Fuzzybox fb(min,max);	                                //fuzzy box
    Vector innerpoints;

    kdtree->search(std::back_inserter(innerpoints), fb);     //range-search query

    tml = (int)((float)clock()*1000/CLOCKS_PER_SEC) - tms;      //milliseconds until now
    if(tml>= cutoff){       //check cutoff
        return -1;
    }

    Vector inpoint, inneigh;
    for(int i=0; i<innerpoints.size(); i++){                //for every inner point
        bool flag = 0;
        Point temp = innerpoints[i];
        for(int j=0; j<pqrs.size(); j++){
            if(temp == pqrs[j]){                            //inner point is not p,q,r or s
                flag = 1;
                break;
            }
        }
        if(flag){
            continue;
        }

        tml = (int)((float)clock()*1000/CLOCKS_PER_SEC) - tms;      //milliseconds until now
        if(tml>= cutoff){       //check cutoff
            return -1;
        }

        inpoint.push_back(temp);
        inneigh = neighbours(inpoint,pol);                  //find neighbours of inner point
        Point before = inneigh[0];                          //predecessor
        Point after = inneigh[1];                           //successor
        Segment a = Segment(before,temp);
        Segment b = Segment(temp,after);

        if(intersect_check(a,pr)){              //if a and pr intersects
            if(!commonpoint_check(a,pr)){       //if a and pr do not have a common point
                return 0;
            }
        }
        if(intersect_check(b,pr)){
            if(!commonpoint_check(b,pr)){       
                return 0;
            }
        } 
        if(intersect_check(a,qs)){
            if(!commonpoint_check(a,qs)){       
                return 0;
            }
        } 
        if(intersect_check(b,qs)){
            if(!commonpoint_check(b,qs)){       
                return 0;
            }
        }

        inpoint.clear();
        inneigh.clear();

        tml = (int)((float)clock()*1000/CLOCKS_PER_SEC) - tms;      //milliseconds until now
        if(tml>= cutoff){       //check cutoff
            return -1;
        }
    }
    return 1;
}

/*local step in simulated annealing*/
Polygon localtransitionstep(Polygon pol,kTree* kdtree,int tim){
    int tms = (int)((float)clock()*1000/CLOCKS_PER_SEC) + tim;        //starting  milliseconds
    int tml;

    Polygon newpol;
    int qi = rand() % pol.size();       //select random point q in the polygon
    Point q = pol[qi];
    Vector qv;
    qv.push_back(q);                    //put q into a vector qv

    Vector qneigh = neighbours(qv,pol); //find neighbours of q
    Point p = qneigh[0];                //p is predecessor of q
    Point r = qneigh[1];                //r is successor of q
    Vector qr;
    qr.push_back(r);                    //put r into a vector qr

    Vector rneigh = neighbours(qr,pol); //find neighbours of r
    Point s = rneigh[1];                //s is successor of r

    Segment pr = Segment(p,r);          //new segments
    Segment qs = Segment(q,s);
    Segment rs = Segment(r,s);

    tml = (int)((float)clock()*1000/CLOCKS_PER_SEC) - tms;      //milliseconds until now
    int valuecheck = checkValidity(pol,pr,qs,kdtree,tml);

    if(valuecheck==1){          //success in checking
        newpol = changePolygon(pol,qv,rs); 
    }
    else if(valuecheck==0){     //fail in checking
        newpol = pol;
    }
    else if(valuecheck==-1){    //out of time
        Polygon fail;
        return fail;
    }

    return newpol;

}