#ifndef SUBDIVISION_H
#define SUBDIVISION_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>
#include <cstdlib>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                                     Point;
typedef std::vector<Point>                            Vector;
typedef CGAL::Polygon_2<K>                           Polygon; 
typedef std::vector<Vector>                          Subsets;

Subsets splitsubsets(Vector, int );

#endif