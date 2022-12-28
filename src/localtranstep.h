#ifndef LOCALTRANSTEP_H
#define LOCALTRANSTEP_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>
#include <cstdlib>
#include <iostream>
#include "changepol.h"
#include "intersect.h"
#include "loops.h"

#include <CGAL/Kd_tree.h>
#include <CGAL/Search_traits_2.h>
#include <CGAL/Fuzzy_iso_box.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Segment_2 Segment;
typedef CGAL::Search_traits_2<K>                      Traits;
typedef CGAL::Kd_tree<Traits>                         Tree;
typedef K::Point_2                                     Point;
typedef std::vector<Point>                            Vector;
typedef CGAL::Polygon_2<K>                           Polygon;
typedef CGAL::Fuzzy_iso_box<Traits>                 Fuzzybox;
typedef std::vector<int>    Xy;

Polygon localtransitionstep(Polygon);

#endif