#include "line.h"

/*
*A function that accepts a point and a polygon and the list of visible lines of convex_hull,
*that checks whether the lines inside the lines of convex hull are visible.
*This function returns a Vector of Segments which contains the visible segments of the polygon.
*/
SegmentVector alledges(Point a, Polygon pol, SegmentVector Seg){
    
    SegmentVector b;

    for(int i=0;i<Seg.size();i++){                                                      //take every visible line from convex hull
        int start=0;
        int end=0;
        Point stpoint=Seg[i][0];
        Point enpoint=Seg[i][1];

        for(int i=0;i<pol.size();i++){                                                 //get all the lines inside that
            if(pol[i]==stpoint){
                start=i;
            }
            if(pol[i]==enpoint){
                end=i;
            }
        }


        if((end-start==1&&end>start)||(end+pol.size()-start==1&&end<start)){         //if there are no additional lines, the line is visible
            b.push_back(Seg[i]);
        }
        else{                                                                        //else check if every line inside that line is visible
            Point prev=pol[start];

            int adi=0;
            if(end<start){
                adi=pol.size();                                                     //in case we have a line that starts at the last points of a polygon and ends at the first
            }
            int temp=0;
            for(int i=start; i<=end+adi;i++){
                temp=i;
                if(i>=pol.size()){
                    i=i-adi;
                }
                if(i!=start){
                    Segment line(prev,pol[i]);
                    if(!lineintersect(a,line,pol)){
                        b.push_back(line);                                          //add visible lines to the vector
                    }
                    prev=pol[i];
                }
                i=temp;
                temp=0;
            }
        }
    
    }
    
    return b;                                                           //if all went well, this is not empty
};