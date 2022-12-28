#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include "sort.h"
#include "triangle.h"
#include "intersect.h"
#include "edgeselection.h"
#include "line.h"
#include "close.h"
#include "insertpoint.h"

Polygon incremental(Vector* ,int ,bool , bool);
Polygon convex_hull(Vector* ,int );

#endif