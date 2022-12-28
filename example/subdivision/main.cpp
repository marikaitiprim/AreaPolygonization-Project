#include "subdivision.h"
#include "algorithms.h"



int main(){

    Vector points;
    points.push_back(Point(1,3));
    points.push_back(Point(3,1));
    points.push_back(Point(7,0));
    points.push_back(Point(10,3));
    points.push_back(Point(9,6));
    points.push_back(Point(7,3));
    points.push_back(Point(5,3));
    points.push_back(Point(3,4));
    points.push_back(Point(0,6));

    Vector points2;
    points2.push_back(Point(0,5));
    points2.push_back(Point(1,4));
    points2.push_back(Point(2,2));
    points2.push_back(Point(4,2));
    points2.push_back(Point(5,4));
    points2.push_back(Point(6,6));
    points2.push_back(Point(3,4));


    Polygon pol;
    for(int i=0;i<points.size();i++){
        pol.push_back(points[i]);
    }

    for(const Point& p : pol.vertices() ){
            std::cout << p << std::endl;
    }


    Polygon res=incremental(&points,1, true, true);
    for(const Point& p : res.vertices() ){
            std::cout << p << std::endl;
    }
    res.clear();
    res=convex_hull(&points,1);
    for(const Point& p : res.vertices() ){
            std::cout << p << std::endl;
    }

    res=convex_hull(&points2,1);
    for(const Point& p : res.vertices() ){
            std::cout << p << std::endl;
    }

    Subsets s = splitsubsets(points,2);
}