#include "pathlist.h"


int main(){

    Vector points;
    points.push_back(Point(2,2));
    points.push_back(Point(3,2));
    points.push_back(Point(1,4));
    points.push_back(Point(5,3));
    points.push_back(Point(3,1));

    Polygon pol;
    for(int i=0;i<points.size();i++){
        pol.push_back(points[i]);
    }

    for(const Point& p : pol.vertices() ){
            std::cout << p << std::endl;
    }

   Pathlist temp;
   temp=createpaths(5, pol);
   std::cout <<"size= "<<temp.size()<< std::endl;

   for(int i=0; i<temp.size();i++){
    std::cout <<"\ni="<<i;
    for(int j=0; j<temp[i].size();j++){
        std::cout <<" -"<< temp[i][j];
    }
   }
   std::cout<< std::endl;

   for(const Point& p : pol.vertices() ){
            std::cout << p << std::endl;
    }
    std::cout<< std::endl;

   pol.erase(pol.vertices_begin()+1);

   for(const Point& p : pol.vertices() ){
            std::cout << p << std::endl;
    }

}