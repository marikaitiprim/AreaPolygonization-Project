#include "merge.h"



int main(){

        Vector points;
        points.push_back(Point(2,2));
        points.push_back(Point(3,2));
        points.push_back(Point(1,4));
        points.push_back(Point(5,3));
        points.push_back(Point(6,3));
        points.push_back(Point(3,1));

        Vector points2;
        points2.push_back(Point(6,3));
        points2.push_back(Point(7,2));
        points2.push_back(Point(9,4));
        points2.push_back(Point(8,3));
        points2.push_back(Point(10,3));
        points2.push_back(Point(11,1));

        Polygon pol;
        for(int i=0;i<points.size();i++){
                pol.push_back(points[i]);
        }

        Polygon pol2;
        for(int i=0;i<points2.size();i++){
                pol2.push_back(points2[i]);
        }

        for(const Point& p : pol.vertices() ){
                std::cout << p << std::endl;
        }
        std::cout << "_____" << std::endl;
        for(const Point& p : pol2.vertices() ){
                std::cout << p << std::endl;
        }


        Polygon newp=mergePolygon(pol, pol2);

        std::cout << "_____" << std::endl;
        for(const Point& p : newp.vertices() ){
                std::cout << p << std::endl;
        }

}