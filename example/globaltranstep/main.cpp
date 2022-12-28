#include "globaltranstep.h"


int main(){

    /*Vector points;
    points.push_back(Point(2,2));
    points.push_back(Point(3,2));
    points.push_back(Point(1,4));
    points.push_back(Point(5,3));
    points.push_back(Point(3,1));
    */

    /*Vector points;
    points.push_back(Point(1,3));
    points.push_back(Point(3,1));
    points.push_back(Point(7,0));
    points.push_back(Point(10,3));
    points.push_back(Point(9,6));
    points.push_back(Point(7,3));
    points.push_back(Point(5,3));
    points.push_back(Point(3,4));
    points.push_back(Point(0,6));*/

    Vector points;
    points.push_back(Point(0,2));
    points.push_back(Point(4,0));
    points.push_back(Point(4,4));
    points.push_back(Point(8,2));
    points.push_back(Point(8,5));
    points.push_back(Point(3,5));
    points.push_back(Point(0,4));

    Polygon pol;
    for(int i=0;i<points.size();i++){
        pol.push_back(points[i]);
    }

    for(const Point& p : pol.vertices() ){
            std::cout << p << std::endl;
    }

    srand(time(NULL));
    Polygon newpol = globaltransitionstep(pol);
    std::cout << newpol << std::endl;
    
}