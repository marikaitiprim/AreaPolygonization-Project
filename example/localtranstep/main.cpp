//making a kd-tree
#include "localtranstep.h"

int main(){

    /*Vector points;
    points.push_back(Point(0,2));
    points.push_back(Point(2,3));
    points.push_back(Point(4,0));
    points.push_back(Point(4,4));
    points.push_back(Point(8,2));
    points.push_back(Point(8,5));*/

    Vector points;
    points.push_back(Point(0,2));
    points.push_back(Point(4,0));
    points.push_back(Point(4,4));
    points.push_back(Point(8,2));
    points.push_back(Point(8,5));
    points.push_back(Point(3,5));
    points.push_back(Point(0,4));

    
    /*Vector points2;
    points2.push_back(Point(6,6));
    points2.push_back(Point(0,6));
    points2.push_back(Point(3,5));
    points2.push_back(Point(4,4));
    points2.push_back(Point(2,4));
    points2.push_back(Point(6,0));
    points2.push_back(Point(0,0));*/

    Polygon pol;
    for(int i=0;i<points.size();i++){
        pol.push_back(points[i]);
    }

    for(const Point& p : pol.vertices() ){
            std::cout << p << std::endl;
    }

    srand(time(NULL));
    Polygon newpol = localtransitionstep(pol);

    std::cout << "newpol:" << std::endl;

    for(const Point& p : newpol.vertices() ){
            std::cout << p << std::endl;
    }
    
}