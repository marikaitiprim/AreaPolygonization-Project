#ifndef LOOP_H
#define LOOP_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>
#include <iostream>
#include "pathlist.h"
#include "localchange.h"
#include "changepol.h"
#include "globalchange.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                                     Point;
typedef K::Segment_2                                 Segment;
typedef std::vector<Point>                            Vector;
typedef std::vector<Segment>                   SegmentVector;
typedef CGAL::Polygon_2<K>                           Polygon;

Vector neighbours(Vector , Polygon );
Polygon removing(Segment , Vector );
Polygon adding(Vector , Point , Point );
SegmentVector edgeslist(Polygon);
Polygon loops(Polygon, double, int,bool);


#endif