#include "intersect.h"

/*
a simple function that takes two segments and checks if they intersect.
*/
bool intersect_check(Segment a, Segment b){
    return CGAL::do_intersect(a,b);
}

/*
*A function that accepts a point and a polygon, creates the convex hull of the polygon,
*and for each segment of the convex hull, checks whether the lines from the point to the
*bottom edge of that segment, from the point to the middle edge of that segment and from
*that point to the top edge of the segment, intersect with any of the segments in the
*convex hull. This function returns a Vector of Segments which contains the visible segments.
*/
SegmentVector intersect(Point* a, Polygon* p){
    if(!p->is_counterclockwise_oriented()){
        p->reverse_orientation();                                       //make sure polygon orientation is counterclockwise,
    }                                                                   //as demanded for convex hull
    Polygon temp;
    CGAL::convex_hull_2(p->begin(),p->end(),std::back_inserter(temp));  //create and store convex hull in polygon temp
    SegmentVector b;                                                    //b holds the visible segments.
    for(int i=0; i<temp.size();i++){
        int j=0;
        if(i+1!=temp.size()){
            j=i+1;
        }
        Point mid(((temp[i][0]+temp[j][0])/2),((temp[i][1]+temp[j][1])/2));     //mid is the middle of the line
        Segment first(*a,temp[i]);
        Segment second(*a,mid);                                         //the three segments needed to check for visibility
        Segment third(*a,temp[j]);
        bool flag=0;
        for(int k=0; k<temp.size();k++){                                //see whether lines intersect with any segment from the convex hull
            int l=0;
            if(k+1!=temp.size()){
                l=k+1;
            }
            
            Segment polline(temp[k],temp[l]);
            if(temp[i]!=temp[k]&&temp[i]!=temp[l]){                     //we don't have to test segments whose edges touch the convex hull
                if(intersect_check(first, polline)){
                flag=1;
                break;
                }
            }
            if(temp[i]!=temp[k]&&temp[j]!=temp[l]){
                if(intersect_check(second, polline)){
                    flag=1;
                    break;
                }
            }
            if(temp[j]!=temp[k]&&temp[j]!=temp[l]){
                if(intersect_check(third, polline)){
                flag=1;
                break;
                }
            }
        }
        if(flag!=1){
            b.push_back(Segment(temp[i],temp[j]));                      
        }
        
    }
    return b;                                                           //if all went well, this is not empty
};