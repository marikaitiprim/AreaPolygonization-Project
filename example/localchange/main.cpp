#include "localchange.h"


int main(){

    Vector points;
    points.push_back(Point(0,1));
    points.push_back(Point(0,5));
    points.push_back(Point(2,4));
    points.push_back(Point(4,6));
    points.push_back(Point(4,2));
    points.push_back(Point(8,5));
    points.push_back(Point(8,0));
    points.push_back(Point(3,0));

    Vector points2;
    points2.push_back(Point(0,0));
    points2.push_back(Point(0,6));
    points2.push_back(Point(2,4));
    points2.push_back(Point(3,5));
    points2.push_back(Point(4,4));
    points2.push_back(Point(6,6));
    points2.push_back(Point(6,0));

    Polygon pol;
    for(int i=0;i<points.size();i++){
        pol.push_back(points[i]);
    }

    Polygon pol2;
    for(int i=0;i<points2.size();i++){
        pol2.push_back(points2[i]);
    }

    if(!pol.is_counterclockwise_oriented()){
        pol.reverse_orientation();             //make sure polygon orientation is counterclockwise
    }

    if(!pol2.is_counterclockwise_oriented()){
        pol2.reverse_orientation();             //make sure polygon orientation is counterclockwise
    }

    std::cout << pol << std::endl;
    std::cout << pol2 << std::endl;

    std::cout << "first with cgal 1 " << abs(pol.area()) << std::endl;
    std::cout << "first with cgal 2 " << abs(pol2.area()) << std::endl;

    std::cout << "my fun " <<  std::endl;

    bool flag = localchange(pol,pol2,1);
    //std::cout << flag << std::endl;
    
}