#ifndef LINE_H
#define LINE_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                                     Point;
typedef K::Segment_2                                 Segment;
typedef std::vector<Point>                            Vector;
typedef std::vector<Segment>                   SegmentVector;
typedef CGAL::Polygon_2<K>                           Polygon; 



SegmentVector alledges(Point, Polygon, SegmentVector);

/*
*This function checks whether point that connects with the segment given, intersect
*with the polygon and returns true if they do, false if they don't.
*/
inline bool lineintersect(Point a, Segment s, Polygon p){
    if(!p.is_counterclockwise_oriented()){
        p.reverse_orientation();                                       //make sure polygon orientation is counterclockwise,
    }

    Point mid(((s[0][0]+s[1][0])/2),((s[0][1]+s[1][1])/2));     //mid is the middle of the line
    Segment first(a,s[0]);
    Segment second(a,mid);                                         //the three segments needed to check for visibility
    Segment third(a,s[1]);
    bool flag=0;
    for(int i=0; i<p.size(); i++){
        int j=0;
        if(i+1!=p.size()){
            j=i+1;
        }
        Segment polline(p[i],p[j]);
        if(s[0]!=p[i]&&s[0]!=p[j]){                     //we don't have to test segments whose edges touch the convex hull
                if(CGAL::do_intersect(first, polline)){
                    return true;
                }
            }
            if((s[0]!=p[i]&&s[1]!=p[j])&&(s[1]!=p[i]&&s[0]!=p[j])){
                if(CGAL::do_intersect(second, polline)){
                    return true;
                }
            }
            if(s[1]!=p[i]&&s[1]!=p[j]){
                if(CGAL::do_intersect(third, polline)){
                    return true;
                }
            }
    }
    return false;
}


#endif