#include "changepol.h"



int main(){

    Vector points;
    points.push_back(Point(2,2));
    points.push_back(Point(3,2));
    points.push_back(Point(1,4));
    points.push_back(Point(5,3));
    points.push_back(Point(6,3));
    points.push_back(Point(3,1));

    Polygon pol;
    for(int i=0;i<points.size();i++){
        pol.push_back(points[i]);
    }

    for(const Point& p : pol.vertices() ){
            std::cout << p << std::endl;
    }

    Segment seg(Point(2,2),Point(3,2));
    Vector Path;
    Path.push_back(Point(1,4));
    Path.push_back(Point(5,3));
    Path.push_back(Point(6,3));
    Path.push_back(Point(3,1));

    Polygon newp=changePolygon(pol, Path, seg);

    std::cout << "old:" << std::endl;
    for(const Point& p : pol.vertices() ){
            std::cout << p << std::endl;
    }

    std::cout << "\nnew:" << std::endl;
    for(const Point& p : newp.vertices() ){
            std::cout << p << std::endl;
    }    

}