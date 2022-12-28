#include "globaltranstep.h"

/*return 1 if the 2 segments have a common point, else 0*/
bool commonpoint_checkg(Segment a, Segment b){
    if(a.vertex(0)==b.vertex(0) || a.vertex(0)==b.vertex(1) || a.vertex(1)==b.vertex(0) || a.vertex(1)==b.vertex(1)){
        return 1;
    }
    return 0;
}

bool checkValidity(Polygon pol, Segment pr, Segment sq, Segment st, Segment qt)
{
    // a) pr does not intersect with sq and qt
    if (intersect_check(pr, sq))
    {
        if (!commonpoint_checkg(sq, pr))
        {
            return 0;
        }
    }

    if (intersect_check(pr, qt))
    {
        if (!commonpoint_checkg(qt, pr))
        {
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
            if (!commonpoint_checkg(current, pr))
            {
                return 0;
            }
        }

        if (intersect_check(sq, current))
        { // sq with current
            if (!commonpoint_checkg(current, sq))
            {
                return 0;
            }
        }

        if (intersect_check(qt, current))
        {
            if (!commonpoint_checkg(current, qt))
            { // qt me current
                return 0;
            }
        }

        neigh.clear();
        pv.clear();
    }

    return 1;
}

/*implementation of global transition step*/
Polygon globaltransitionstep(Polygon pol,bool subdivision,Point qlast, Point qfirst){
    Polygon newpol;
    int qi = rand() % pol.size();       //select random point q in the polygon
    Point q = pol[qi];
    Vector qv;
    qv.push_back(q);                    //put q into a vector qv

    Vector qneigh = neighbours(qv,pol); //find neighbours of q
    Point p = qneigh[0];                //p is predecessor of q
    Point r = qneigh[1];                //r is successor of q       

    if(subdivision){
        if(qlast!=Point(-1,-1)){            //not last subset
            while(q==qlast || r==qlast){        //q and r must not be the common point q of the 2 subsets
                qi = rand() % pol.size();       //select random point q in the polygon
                q = pol[qi];
                if(!qv.empty()){
                    qv.clear();
                }
                qv.push_back(q);                    //put q into a vector qv
                qneigh = neighbours(qv,pol);        //find neighbours of q
                p = qneigh[0];                //p is predecessor of q
                r = qneigh[1];                //r is successor of q  
            }
        }
        if(qfirst!=Point(-1,-1)){       //not first subset
            while(q==qfirst || p==qfirst){        //q and p must not be the common point q of the 2 subsets
                qi = rand() % pol.size();       //select random point q in the polygon
                q = pol[qi];
                if(!qv.empty()){
                    qv.clear();
                }
                qv.push_back(q);                    //put q into a vector qv
                qneigh = neighbours(qv,pol);        //find neighbours of q
                p = qneigh[0];                //p is predecessor of q
                r = qneigh[1];                //r is successor of q  
            }
        }
    }           

    int si = rand() % pol.size();       //select random point s in the polygon
    Point s = pol[si];     
    while(s==q || s==p || s==r){        //s must not be the same as q,p,r
        si = rand() % pol.size();       //select again
        s = pol[si];
    }

    Vector sv;
    sv.push_back(s);                    //put s into a vector sv
    Vector sneigh = neighbours(sv,pol); //find neighbours of s
    Point t = sneigh[1];                //t is the successor of s

    if(subdivision){
        if(qlast!=Point(-1,-1)){            //not last subset
            int counter = 0;
            while(s==q || s==p || s==r || t==qlast){        //s must not be the same as q,p,r and qmeet
                si = rand() % pol.size();       //select again
                s = pol[si];
                if(!sv.empty()){
                    sv.clear();
                }
                sv.push_back(s);                    //put s into a vector sv
                Vector sneigh = neighbours(sv,pol); //find neighbours of s
                Point t = sneigh[1];                //t is the successor of s
                counter++;
                if(counter>3*pol.size()){           //upper bound - cannot find any point to change
                    return pol;
                }
            } 
        }
        if(qfirst!=Point(-1,-1)){            //not first subset
            int counter = 0;
            while(s==q || s==p || s==r || s==qfirst){        //s must not be the same as q,p,r and qmeet
                si = rand() % pol.size();       //select again
                s = pol[si];
                if(!sv.empty()){
                    sv.clear();
                }
                counter++;
                if(counter>3*pol.size()){
                    return pol;
                }
            } 
            sv.push_back(s);                    //put s into a vector sv
            Vector sneigh = neighbours(sv,pol); //find neighbours of s
            Point t = sneigh[1];                //t is the successor of s
        }
    }


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