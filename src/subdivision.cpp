#include "subdivision.h"

/*This function takes in a vector of points and the amount of points that will be on a subset,
*splits them, if we are not on the last subset we check if the last point has two lower points
*and if not we go back one point or front depending where the higher point is.
*/
Subsets splitsubsets(Vector points, int m){
    int n=points.size();
    Vector sortpoints = sortv(&points,1,1);              //sort points by increasing x

    int start=0,end=m, k = (int)(n/m);
    if(n%m>0){
        k++;
    }
    Subsets subsets;                    //vector to store all the subsets
    for(int i=0; i<k; i++){             //for every subset
        Vector sub;

        if(i==k-1){                     //last subset
            for(int j=start; j<n; j++){   //push remaining points in the subset
                sub.push_back(sortpoints[j]);
            }
            subsets.push_back(sub);
            break;
        }

        for(int j=start; j<end; j++){   //push m-1 points in the subset
            sub.push_back(sortpoints[j]);
        }
        if(i<k-1){                      //not in the last subset
            while(sub.size()>0){
                if(sub[sub.size()-1][1]>sub[sub.size()-2][1]&&sub[sub.size()-1][1]>sortpoints[start+sub.size()][1]){
                    subsets.push_back(sub);         //push subset in vector with subsets
                    start=start+sub.size()-1;
                    end = start + m;
                    break;
                }
                else if(sub[sub.size()-1][1]<sub[sub.size()-2][1]){
                    sub.pop_back();
                }
                else if(sub[sub.size()-1][1]<sortpoints[start+sub.size()][1]){
                    sub.push_back(sortpoints[start+sub.size()]);
                }
            }
        }
        if(end>n){
            end=n;
        }
    }

    return subsets;

}

/*subdivision case for simulated annealing. bool incremental = 1 if greedy algorithm incremental
has been selected, 0 if convex hull*/
Polygon subdivision(Vector points,int m, bool inc, int edgeselect,int L, bool maxmin){
    Subsets subs = splitsubsets(points,m);
    Polygons pols;
    SegmentVector protect;
    if(inc){                //incremental algorithm
        for(int i=0; i<subs.size(); i++){       //for every subset
            Polygon pol;
            if(i==0){                       //first subset
                Vector subset = subs[i];
                Segment right = Segment(subset[subset.size()-2],subset[subset.size()-1]);
                protect.push_back(right);
                pol = incrementalsub(&subs[i],edgeselect,1,1,1,protect);
                subset.clear();
                if(pol.is_empty()){
                    pol = convex_hullsub(&subs[i],edgeselect,1,protect);
                    if(pol.is_empty()){
                        return pol;
                    }
                }
            }
            else if(i==subs.size()-1){      //last subset
                Vector subset = subs[i];
                Segment left = Segment(subset[0],subset[1]);
                protect.push_back(left);
                pol = incrementalsub(&subs[i],edgeselect,1,0,0,protect);
                subset.clear();
                if(pol.is_empty()){
                    pol = convex_hullsub(&subs[i],edgeselect,0,protect);
                    if(pol.is_empty()){
                        return pol;
                    }
                }
            }
            else{
                Vector subset = subs[i];
                Segment right = Segment(subset[subset.size()-2],subset[subset.size()-1]);
                Segment left = Segment(subset[0],subset[1]);
                protect.clear();
                protect.push_back(left);
                protect.push_back(right);
                pol = incrementalsub(&subs[i],edgeselect,1,1,0,protect);
                subset.clear();
                if(pol.is_empty()){
                    pol = convex_hullsub(&subs[i],edgeselect,0,protect);
                    if(pol.is_empty()){
                        return pol;
                    }
                }
            }
            pols.push_back(pol);
            protect.clear();
        }
    }
    else{                           //convex_hull algorithm
        for(int i=0; i<subs.size(); i++){       //for every subset
            Polygon pol;
            if(i==0){                       //first subset
                Vector subset = subs[i];
                Segment right = Segment(subset[subset.size()-2],subset[subset.size()-1]);
                protect.push_back(right);
                pol = convex_hullsub(&subs[i],edgeselect,1,protect); 
                subset.clear();
                if(pol.is_empty()){
                    return pol;
                }
            }
            else if(i==subs.size()-1){      //last subset
                Vector subset = subs[i];
                Segment left = Segment(subset[0],subset[1]);
                protect.push_back(left);
                pol = convex_hullsub(&subs[i],edgeselect,0,protect);
                subset.clear();
                if(pol.is_empty()){
                    return pol;
                }
            }
            else{
                Vector subset = subs[i];
                Segment right = Segment(subset[subset.size()-2],subset[subset.size()-1]);
                Segment left = Segment(subset[0],subset[1]);
                protect.push_back(left);
                protect.push_back(right);
                pol = convex_hullsub(&subs[i],edgeselect,0,protect);
                subset.clear();
                if(pol.is_empty()){
                    return pol;
                }
            }
            pols.push_back(pol);
            protect.clear();
        }
    }

    Polygons globalpols;

    Vector subset = subs[0];                    //first polygon
    Polygon newpol = localglobalstep(pols[0],2,L,maxmin,1,subset[subset.size()-1],Point(-1,-1));
    globalpols.push_back(newpol);

    for(int i=1; i<pols.size()-1; i++){         //inner polygons
        subset = subs[i];
        newpol = localglobalstep(pols[i],2,L,maxmin,1,subset[subset.size()-1],subset[0]);
        globalpols.push_back(newpol);
    }

    subset = subs[subs.size()-1];                    //last polygon
    newpol = localglobalstep(pols[pols.size()-1],2,L,maxmin,1,Point(-1,-1),subset[0]);
    globalpols.push_back(newpol);

    Polygon merged;
    if(pols.size()>1){          //more than 2 polygons
        merged = mergePolygon(pols[0],pols[1]);
        if(pols.size()>3){      //more than 3 polygons
            for(int i=2; i<pols.size(); i++){
                merged = mergePolygon(merged,pols[i]);
            }
        }
    }
    else{                       //one polygon only
        merged = pols[0];
    }

    Polygon finalpol = localglobalstep(merged,1,L,maxmin,0,Point(-1,-1),Point(-1,-1));

    return finalpol;

}