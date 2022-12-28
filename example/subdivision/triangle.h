#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                                     Point;
typedef std::vector<Point>                            Vector;
typedef K::Segment_2                                 Segment;
typedef std::vector<Segment>                            SegmentVector;
typedef CGAL::Polygon_2<K>                           Polygon;


Polygon triangle(Vector*);
Polygon rectangle(Vector*, SegmentVector);

#endif