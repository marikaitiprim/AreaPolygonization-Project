#ifndef SORTV_H
#define SORTV_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                                     Point;
typedef std::vector<Point>                            Vector;

Vector sortv(Vector*, bool, bool);

#endif