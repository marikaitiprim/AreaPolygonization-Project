#include "localtranstep.h"

//from instersect.cpp
bool intersect_check(Segment a, Segment b){
    return CGAL::do_intersect(a,b);
}

/*return 1 if the 2 segments have a common point, else 0*/
bool commonpoint_check(Segment a, Segment b){
    if(a.vertex(0)==b.vertex(0) || a.vertex(0)==b.vertex(1) || a.vertex(1)==b.vertex(0) || a.vertex(1)==b.vertex(1)){
        return 1;
    }
    return 0;
}

//from loops.cpp
/*function to find neighbours of the path*/
Vector neighbours(Vector V, Polygon pol){
    //std::cout<<" IN NEIGHBOURS"<<std::endl;
    Vector neigh;

    Point a;
    if(pol[0]==V[0]){           //1st point of polgon is also 1st point of the path
        neigh.push_back(pol[pol.size()-1]);
    }

    a = pol[0];
    for(int i=1; i<pol.size(); i++){        //for each vertex in the polygon
        if(pol[i]==V[0]){                       //if the point of the vertex is equal to the first point of the path
            neigh.push_back(a);         //first neighbour
        }
        a = pol[i];
    }

    bool flag = 0;
    for(int i=0; i<pol.size(); i++){        //for each vertex in the polygon
        if(flag){
            neigh.push_back(pol[i]);        //second neighbour
            break;
        }
        if(pol[i]==V[V.size()-1]){                       //if the point of the vertex is equal to the last point of the path
            flag = 1;
        }
    }
    if(pol[pol.size()-1]==V[V.size()-1]){   //last point in the polygon is also the last in the path
        neigh.push_back(pol[0]);
    }
    //std::cout<<" OUT NEIGHBOURS"<<std::endl;
    return neigh;

}

/*check if new polygon is valid*/
bool checkValidity(Polygon pol,Segment pr, Segment qs){
    //a) new edges do not intersect each other
    if(intersect_check(pr,qs)){
        std::cout << "metaji tous " <<pr << "   " << qs << std::endl;
        return 0;
    }
    //b) new edges do not intersect another edge in the polygon
    Tree kdtree;
    for(int i=0; i<pol.size(); i++){            //initialize kdtree + insert all points of the polygon
        kdtree.insert(pol[i]);
    }

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

    kdtree.search(std::back_inserter(innerpoints), fb);     //range-search query

    Vector inpoint, inneigh;
    for(int i=0; i<innerpoints.size(); i++){                //for every inner point
        bool flag = 0;
        Point temp = innerpoints[i];
        std::cout << "inner point is " << temp << std::endl;
        for(int j=0; j<pqrs.size(); j++){
            if(temp == pqrs[j]){                            //inner point is not p,q,r or s
                std::cout << "okk" << std::endl;
                flag = 1;
                break;
            }
        }
        if(flag){
            continue;
        }
        inpoint.push_back(temp);
        inneigh = neighbours(inpoint,pol);                  //find neighbours of inner point
        Point before = inneigh[0];                          //predecessor
        Point after = inneigh[1];                           //successor
        Segment a = Segment(before,temp);
        Segment b = Segment(temp,after);

        std::cout << "Segment a " << a << std::endl;
        std::cout << "Segment b " << b << std::endl;

        bool yo = intersect_check(a,pr);
        bool lo = intersect_check(b,pr) ;
        bool po = intersect_check(a,qs) ; 
        bool we = intersect_check(b,qs);
        std::cout << yo << lo << po << we<< std::endl;
        std::cout << "Segment pr " << pr << std::endl;
        std::cout << "Segment qs " << qs << std::endl;

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
    }
    return 1;
}

Polygon localtransitionstep(Polygon pol){
    Polygon newpol;
    int qi = rand() % pol.size();       //select random point q in the polygon
    std::cout << qi << std::endl;
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

    std::cout << "Segment pr " << pr << std::endl;
    std::cout << "Segment rs " << rs << std::endl;
    std::cout << "Segment qs " << qs << std::endl;

    if(checkValidity(pol,pr,qs)){
        std::cout << "ok" << std::endl;
        newpol = changePolygon(pol,qv,rs); 
    }
    return newpol;

}