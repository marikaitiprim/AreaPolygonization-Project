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
//Polygon incremental(Vector* points,int edgeselect,bool x, bool sm, bool start, SegmentVector protect){    //points -> from main (inputs.cpp)

    //sorting points
    Vector sortedpoints = sortv(points,x,sm);
    // bool skipf=false;
    // bool skipl=false;
    // if(protect.size()==1&&start==true){
    //     skipf=true;
    // }
    // else{
    //     skipl=true;
    // }

    SegmentVector protect=protectedpoints(sortedpoints);


    Polygon polyg=rectangle(&sortedpoints,protect);

    for(int i=0; i<sortedpoints.size(); i++){       //for each point

        Point p(sortedpoints[i][0],sortedpoints[i][1]);
        
        SegmentVector sv = intersect(&p,&polyg);        //find visble edges  
        std::cout<<" sv size="<<sv.size()<<std::endl;  
        SegmentVector segv = alledges(p,polyg,sv);
        std::cout<<" start segv size="<<segv.size()<<std::endl;  
        

        SegmentVector::iterator fi=std::find(segv.begin(),segv.end(),protect[0]);
        SegmentVector::iterator se=std::find(segv.begin(),segv.end(),protect[1]);
        if(se!=segv.end()/*&&skipl==false*/){
            segv.erase(std::find(segv.begin(),segv.end(),protect[1]));
        }
        if(fi!=segv.end()/*&&skipf==false*/){
            segv.erase(std::find(segv.begin(),segv.end(),protect[0]));
        }

        std::cout<<" end segv size="<<segv.size()<<std::endl;  
        Segment e = edgeselection(&segv,&p,edgeselect); //select the appropriate edge

        Polygon* pointpol = &polyg;
        Polygon polyg = insertpoint(pointpol,&p,&e);        //insert to polygon

    }
    return polyg;
}


/*convex_hull algorithm */
Polygon convex_hull(Vector* points,int edgeselect){    //points -> from main (inputs.cpp)
//Polygon convex_hull(Vector* points,int edgeselect, bool start, SegmentVector protect){    //points -> from main (inputs.cpp)
    std::cout<<"IN CONVEX HULL"<<std::endl;
    Polygon pol;
    Vector temp = *points;
    Vector sortedpoints = sortv(points,1,1);
    SegmentVector protect=protectedpoints(sortedpoints);
    CGAL::convex_hull_2(points->begin(),points->end(),std::back_inserter(pol));  //create and store convex hull in polygon pol

    // bool skipf=false;
    // bool skipl=false;
    // if(protect.size()==1&&start==true){
    //     skipf=true;
    // }
    // else{
    //     skipl=true;
    // }

    for(int i=0; i<pol.size(); i++){
        temp.erase(std::find(temp.begin(),temp.end(),pol[i]));  //remove points of the convex hull from the vector
    }
    std::cout<<"convex"<<std::endl;
    std::cout<<pol<<std::endl;

     for(int i=0; i<pol.size(); i++){
        if(pol[i]==protect[0][0]&&pol[i+1]!=protect[0][1]/*&&skipf==false*/){
            pol.insert(pol.vertices_begin()+i+1,protect[0][1]);
            temp.erase(std::find(temp.begin(),temp.end(),protect[0][1]));
        }
        else if(pol[i]==protect[1][1]&&pol[i-1]!=protect[1][0]/*&&skipl==false*/){
            pol.insert(pol.vertices_begin()+i,protect[1][0]); 
            temp.erase(std::find(temp.begin(),temp.end(),protect[1][0]));
        }
     }
     std::cout<<"after"<<std::endl;
    std::cout<<pol<<std::endl;


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
            if(seg==protect[0]/*&&skipf==false*/){
                cl=Point(-1,-1);
            }
            else if(seg==protect[1]/*&&skipl==false*/){
                cl=Point(-1,-1);
            }
            else{
                cl = closest(temp,seg,pol);             //find its closest point
            }
            if(cl >= Point(0,0)){        //no visible points for this seg
                pa= std::make_pair(cl,seg);
                pairs.push_back(pa);
            }
        }
        if((pairs.size()==0)&&(temp.size()!=0)){
            std::cout<<temp.size()<<" remain(s) that have no visible edge."<<std::endl;
            return pol;
        }

        PSpair e = edgeselection2(&pairs,edgeselect);   //select edge according to the option

        Polygon* pointpol = &pol;
        Polygon pol = insertpoint(pointpol,&(e.first),&(e.second));      //insert point into polygon
        
        temp.erase(std::find(temp.begin(),temp.end(),e.first)); 

    }
    

    return pol;
}