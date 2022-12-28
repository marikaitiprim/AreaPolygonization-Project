#ifndef EDGESELECTION_H
#define EDGESELECTION_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Segment_2.h>
#include <iostream>
#include <cstdlib>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Segment_2 Segment;       
typedef std::vector<Point> Vector;
typedef std::vector<Segment> SegmentVector;
typedef CGAL::Polygon_2<K> Polygon;
typedef std::pair<Point,Segment> PSpair;
typedef std::vector<PSpair> PairVector;




Segment edgeselection(SegmentVector*, Point*, int );


PSpair edgeselection2(PairVector*, int );

#endif