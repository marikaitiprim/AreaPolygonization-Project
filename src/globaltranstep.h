#ifndef GLOBALTRANSTEP_H
#define GLOBALTRANSTEP_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>
#include <cstdlib>
#include <iostream>
#include "loops.h"
#include "intersect.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                                     Point;
typedef std::vector<Point>                            Vector;
typedef CGAL::Polygon_2<K>                           Polygon; 
typedef K::Segment_2                                Segment;


Polygon globaltransitionstep(Polygon,bool,Point,Point,int);

#endif