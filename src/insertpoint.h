#ifndef INSERTPOINT_H
#define INSERTPOINT_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Segment_2.h>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;       
typedef CGAL::Polygon_2<K> Polygon;

Polygon insertpoint(Polygon* , Point* , Segment* );


#endif