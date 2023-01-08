#ifndef SUBDIVISION_H
#define SUBDIVISION_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>
#include <cstdlib>
#include <iostream>
#include "algorithms.h"
#include "sort.h"
#include "localglobalstep.h"
#include "merge.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                                     Point;
typedef std::vector<Point>                            Vector;
typedef CGAL::Polygon_2<K>                           Polygon; 
typedef std::vector<Vector>                          Subsets;
typedef std::vector<Polygon>                          Polygons;

Subsets splitsubsets(Vector, int );
Polygon subdivision(Vector,int , bool, int,int, bool , int);
Polygon subdivisionPol(Polygon,int, bool, int,int, bool, int);

#endif