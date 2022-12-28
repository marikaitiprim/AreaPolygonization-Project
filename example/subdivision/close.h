#ifndef CLOSE_H
#define CLOSE_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>
#include <iostream>
#include <map>
#include <iterator>
#include "line.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                                     Point;
typedef K::Segment_2                                 Segment;
typedef std::vector<Point>                            Vector;
typedef std::vector<Segment>                   SegmentVector;
typedef CGAL::Polygon_2<K>                           Polygon; 



Point closest(Vector,Segment,Polygon);
std::multimap<Point,Segment> storeclosest(Segment*, Point* , std::multimap<Point,Segment>* );


#endif