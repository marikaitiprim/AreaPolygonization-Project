#include "algorithms.h"

SegmentVector protectedpoints(Vector sorted){
    Point afterfirst;
    Point beforelast;
    for(int i=1;i<sorted.size();i++){
        if(sorted[i][1]<sorted[0][1]){
            afterfirst=sorted[i];
            break;
        }
    }
    for(int i=sorted.size()-2;i>0;i--){
        if(sorted[i][1]<sorted[sorted.size()-1][1]){
            beforelast=sorted[i];
            break;
        }
    }
    Segment left=Segment( sorted[0], afterfirst);
    Segment right=Segment( beforelast, sorted[sorted.size()-1]);
    std::cout<<"left= "<<left<<" right= "<<right<<std::endl;
    SegmentVector temp;
    temp.push_back(left);
    temp.push_back(right);
    return temp;
}

/*incremental algorithm*/
Polygon incremental(Vector* points,int edgeselect,bool x, bool sm){    //points -> from main (inputs.cpp)
    clock_t t;
    int cutoff = 500*points->size();
    int tms = (int)((float)clock()*1000/CLOCKS_PER_SEC);        //starting  milliseconds
    int tml;
    //sorting points
    Vector sortedpoints = sortv(points,x,sm);

    //initiate A - starting triangle
    Polygon polyg=triangle(&sortedpoints);

    for(int i=0; i<sortedpoints.size(); i++){       //for each point

        Point p(sortedpoints[i][0],sortedpoints[i][1]);
        
        SegmentVector sv = intersect(&p,&polyg);        //find visble edges      
        SegmentVector segv = alledges(p,polyg,sv);

        tml = (int)((float)clock()*1000/CLOCKS_PER_SEC) - tms;      //milliseconds until now
        if(tml>= cutoff){       //check cutoff
            Polygon fail;
            return fail;
        }

        Segment e;
        if(segv.size()==0){     //if a point has no visible edges return an empty polygon
            Polygon fail;
            return fail;
        }
        else if(segv.size()==1){     //if a point has no visible edges return an empty polygon
            e=segv[0];
        }
        else{
            e = edgeselection(&segv,&p,edgeselect); //select the appropriate edge
        }
        Polygon* pointpol = &polyg;
        Polygon polyg = insertpoint(pointpol,&p,&e);        //insert to polygon

        tml = (int)((float)clock()*1000/CLOCKS_PER_SEC) - tms;      //milliseconds until now
        if(tml>= cutoff){       //check cutoff
            Polygon fail;
            return fail;
        }

    }
    return polyg;
}

//only for subdivision
Polygon incrementalsub(Vector* points,int edgeselect,bool x, bool sm, bool start,SegmentVector protect){  

    //sorting points
    Vector sortedpoints = sortv(points,x,sm);
    Polygon polyg=rectangle(&sortedpoints,protect);     //instead of a triangle, create a rectangle of all 4 protected points or a triangle, of 2 protected and another one
    for(int i=0; i<sortedpoints.size(); i++){       //for each point
        Point p(sortedpoints[i][0],sortedpoints[i][1]);
        SegmentVector sv = intersect(&p,&polyg);        //find visble edges  
        SegmentVector segv = alledges(p,polyg,sv);
        if(protect.size()==1){      //first or last subset
            SegmentVector::iterator fi=std::find(segv.begin(),segv.end(),protect[0]);   //search if the protected line is on the vible ones of the current point
            if(fi!=segv.end()){
                segv.erase(std::find(segv.begin(),segv.end(),protect[0]));      //if it is erase it
            }
        }
        else{
            SegmentVector::iterator fi=std::find(segv.begin(),segv.end(),protect[0]);   //same as above but for both protected segments
            if(fi!=segv.end()){
                segv.erase(std::find(segv.begin(),segv.end(),protect[0]));
            }
            SegmentVector::iterator se=std::find(segv.begin(),segv.end(),protect[1]);
            if(se!=segv.end()){
                segv.erase(std::find(segv.begin(),segv.end(),protect[1]));
            }
        }
        Segment e;  
        if(segv.size()==0){     //if a point has no visible edges return an empty polygon
            Polygon fail;
            return fail;
        }
        else if(segv.size()==1){     //if a point has no visible edges return an empty polygon
            e=segv[0];
        }
        else{
            e = edgeselection(&segv,&p,edgeselect); //select the appropriate edge
        }
        Polygon* pointpol = &polyg;
        Polygon polyg = insertpoint(pointpol,&p,&e);        //insert to polygon

    }
    return polyg;
}


/*convex_hull algorithm */
Polygon convex_hull(Vector* points,int edgeselect){    //points -> from main (inputs.cpp)

    Polygon pol;
    Vector temp = *points;
    CGAL::convex_hull_2(points->begin(),points->end(),std::back_inserter(pol));  //create and store convex hull in polygon pol

    for(int i=0; i<pol.size(); i++){
        temp.erase(std::find(temp.begin(),temp.end(),pol[i]));  //remove points of the convex hull from the vector
    }

    while(temp.size()!=0){              //repeat until all points are in the polygon
        Point cl;
        Segment seg;
        PSpair pa;
        PairVector pairs;
        for(int i=0; i<pol.size(); i++){        //for each edge of the polygon
            if(i==pol.size()-1){
                seg = Segment(pol[i],pol[0]);
            }
            else{
                seg = Segment(pol[i],pol[i+1]);
            }
            cl = closest(temp,seg,pol);             //find its closest point
            if(cl >= Point(0,0)){        //no visible points for this seg
                pa= std::make_pair(cl,seg);
                pairs.push_back(pa);
            } 
        }
        PSpair e;
        if((pairs.size()==0)&&(temp.size()!=0)){
            std::cout<<temp.size()<<" remain(s) that have no visible edge."<<std::endl;
            return pol;
        }
        else if(pairs.size()==1){
            e=pairs[0];
        }
        else{
            e = edgeselection2(&pairs,edgeselect);   //select edge according to the option
        }

        Polygon* pointpol = &pol;
        Polygon pol = insertpoint(pointpol,&(e.first),&(e.second));      //insert point into polygon
        
        temp.erase(std::find(temp.begin(),temp.end(),e.first)); 

    }
    

    return pol;
}

//only for subdivision
Polygon convex_hullsub(Vector* points,int edgeselect, bool start, SegmentVector protect){   
    Polygon pol;
    Vector temp = *points;
    Vector sortedpoints = sortv(points, 1, 1);
    CGAL::convex_hull_2(points->begin(), points->end(), std::back_inserter(pol)); // create and store convex hull in polygon pol

    for (int i = 0; i < pol.size(); i++)
    {
        temp.erase(std::find(temp.begin(), temp.end(), pol[i])); // remove points of the convex hull from the vector
    }
    for (int i = 0; i < pol.size(); i++)
    {
        if(protect.size()==1 && start==1){              //first subset
            if (pol[i] == protect[0][1] && pol[i - 1] != protect[0][0])
            {
                pol.insert(pol.vertices_begin() + i, protect[0][0]);            //since the first protected point is already in (smallest x),
                temp.erase(std::find(temp.begin(), temp.end(), protect[0][0])); // add the second point and erase it from vector of points
            }
        }
        else if(protect.size()==1 && start==0){         //last subset
            if (pol[i] == protect[0][0] && pol[i + 1] != protect[0][1])
            {
                pol.insert(pol.vertices_begin() + i + 1, protect[0][1]);        //same as above, but now the last point is in and we need to add the third.
                temp.erase(std::find(temp.begin(), temp.end(), protect[0][1]));
            }
        }
        else{                                                                   //both from above apply here
            if (pol[i] == protect[0][0] && pol[i + 1] != protect[0][1])
            {
                pol.insert(pol.vertices_begin() + i + 1, protect[0][1]);
                temp.erase(std::find(temp.begin(), temp.end(), protect[0][1]));
                
            }
            else if (pol[i] == protect[1][1] && pol[i - 1] != protect[1][0])
            {
                pol.insert(pol.vertices_begin() + i, protect[1][0]);
                temp.erase(std::find(temp.begin(), temp.end(), protect[1][0]));
            }                    

        }

    }

    while (temp.size() != 0){ // repeat until all points are in the polygon
        Point cl;
        Segment seg;
        PSpair pa;
        PairVector pairs;
        for (int i = 0; i < pol.size(); i++){ // for each edge of the polygon
            if (i == pol.size() - 1){
                seg = Segment(pol[i], pol[0]);
            }
            else{
                seg = Segment(pol[i], pol[i + 1]);
            }
            if(protect.size()==1){          //first or last subset
                if (seg == protect[0]){     //if the segment we are currently in, is protected, don't add a point to it.
                    cl = Point(-1, -1);
                }
                else{
                    cl = closest(temp, seg, pol); // find its closest point
                }
            }
            else{                           //same as above for internal subsets
                if (seg == protect[0]){
                    cl = Point(-1, -1);
                }
                else if (seg == protect[1]){
                    cl = Point(-1, -1);
                }
                else{
                    cl = closest(temp, seg, pol); // find its closest point
                }
            }
            if (cl >= Point(0, 0)){ // no visible points for this seg
                pa = std::make_pair(cl, seg);
                pairs.push_back(pa);
            }
        }
        PSpair e;
        if ((pairs.size() == 0) && (temp.size() != 0)){

            std::cout << temp.size() << " remain(s) that have no visible edge." << std::endl;

            if(edgeselect!=1){                                                      //if the convex hull failed, try using random instead of min
                return convex_hullsub(points,1,start,protect);
            }
            else{                                                               //if random failed, return empty polygon
                Polygon fail;
                return fail;
            }

        }
        else if(pairs.size()==1){
            e=pairs[0];
        }
        else{
            e = edgeselection2(&pairs,edgeselect);   //select edge according to the option
        }

        Polygon *pointpol = &pol;
        Polygon pol = insertpoint(pointpol, &(e.first), &(e.second)); // insert point into polygon

        temp.erase(std::find(temp.begin(), temp.end(), e.first));
    }

    return pol;
}