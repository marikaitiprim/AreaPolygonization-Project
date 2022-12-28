#include "globaltranstep.h"

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

bool checkValidity(Polygon pol, Segment pr, Segment sq, Segment st, Segment qt)
{
    // a) pr does not intersect with sq and qt
    if (intersect_check(pr, sq))
    {
        if (!commonpoint_check(sq, pr))
        {
            std::cout << "metaji tous " << std::endl;
            return 0;
        }
    }

    if (intersect_check(pr, qt))
    {
        if (!commonpoint_check(qt, pr))
        {
            std::cout << "metaji tous " << std::endl;
            return 0;
        }
    }
    // b) each of the new does not intersect any other
    Vector pv, neigh;

    for (int i = 0; i < pol.size(); i++)
    {
        if (pol[i] == pr.vertex(0))
        { // if pol[i] == p
            continue;
        }

        if (pol[i] == qt.vertex(0))
        { // if pol[i] == q
            continue;
        }

        if (pol[i] == st.vertex(0))
        { // if pol[i] == s
            continue;
        }

        Vector pv;
        pv.push_back(pol[i]);
        neigh = neighbours(pv, pol);
        Point successor = neigh[1]; // find successor of current point

        Segment current = Segment(pol[i], successor);

        if (intersect_check(pr, current))
        { // pr with current
            if (!commonpoint_check(current, pr))
            {
                std::cout << "pr me allo edge " << std::endl;
                return 0;
            }
        }

        if (intersect_check(sq, current))
        { // sq with current
            if (!commonpoint_check(current, sq))
            {
                std::cout << "sq me allo edge " << std::endl;
                return 0;
            }
        }

        if (intersect_check(qt, current))
        {
            if (!commonpoint_check(current, qt))
            { // qt me current
                std::cout << "qt me allo edge " << std::endl;
                return 0;
            }
        }

        neigh.clear();
        pv.clear();
    }

    return 1;
}

/*implementation of global transition step*/
Polygon globaltransitionstep(Polygon pol){
    Polygon newpol;

    int qi = rand() % pol.size();       //select random point q in the polygon
    std::cout << qi << std::endl;
    Point q = pol[qi];
    Vector qv;
    qv.push_back(q);                    //put q into a vector qv

    Vector qneigh = neighbours(qv,pol); //find neighbours of q
    Point p = qneigh[0];                //p is predecessor of q
    Point r = qneigh[1];                //r is successor of q                

    int si = rand() % pol.size();       //select random point s in the polygon
    Point s = pol[si];     
    std::cout << "before " << si << std::endl; 
    while(s==q || s==p || s==r){        //s must not be the same as q,p,r
        si = rand() % pol.size();       //select again
        std::cout << si << std::endl;
        s = pol[si];
    }

    Vector sv;
    sv.push_back(s);                    //put s into a vector sv

    Vector sneigh = neighbours(sv,pol); //find neighbours of s
    Point t = sneigh[1];                //t is the successor of s

    Segment st = Segment(s,t);
    Segment sq = Segment(s,q);
    Segment qt = Segment(q,t);
    Segment pr = Segment(p,r);
    if(checkValidity(pol,pr,sq,st,qt)){
        newpol=changePolygon(pol,qv,st);
    }
    else{
        newpol = pol;
    }
    return newpol;

}

/*check if new polygon is valid*/
/*bool checkValidity(Polygon newpol){
    if(newpol.is_simple()){
        return 1;
    }
    else{
        return 0;
    }
}*/