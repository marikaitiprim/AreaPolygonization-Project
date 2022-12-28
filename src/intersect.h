#ifndef INTERSECT_H
#define INTERSECT_H

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


bool intersect_check(Segment , Segment );
SegmentVector intersect(Point*, Polygon*);

#endif