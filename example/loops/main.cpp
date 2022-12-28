#include "loops.h"


int main(){

    /*Vector points;
    points.push_back(Point(2,2));
    points.push_back(Point(3,2));
    points.push_back(Point(1,4));
    points.push_back(Point(5,3));
    points.push_back(Point(3,1));
    */

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

    Polygon pol;
    for(int i=0;i<points.size();i++){
        pol.push_back(points[i]);
    }

    for(const Point& p : pol.vertices() ){
            std::cout << p << std::endl;
    }

    /*SegmentVector seg;
    Segment line(Point(2,2),Point(1,4));
    Segment line2(Point(1,4),Point(3,1));
    Segment line3(Point(5,3),Point(2,2));
    seg.push_back(line);
    seg.push_back(line2);
    seg.push_back(line3);

    Vector path;
    path.push_back(Point(7,3));
    path.push_back(Point(5,3));
    path.push_back(Point(3,4));

    Segment edge = Segment(Point(3,1),Point(7,0));

    Vector neigh = neighbours(path,pol);
    std::cout << "neighbours " << neigh[0] << "," << neigh[1]<< std::endl;
    Polygon oldpol = removing(edge,path);
    std::cout << "remove polygon " << oldpol<< std::endl;
    Polygon newpol = adding(path, neigh[0], neigh[1]);
    std::cout << "add polygon " << newpol<< std::endl;*/


    //SegmentVector res=edgeslist(pol);
    //Pathlist temp=createpaths(4, pol);
    Polygon n=loops(pol, 1.0, 4, 0);
    std::cout << "Polygon area start " << pol.area() << std::endl;
    std::cout << "Polygon area end " << n.area() << std::endl;
    // for(int i=0;i<res.size();i++){
    //     std::cout << res[i][0]<<" - "<<res[i][1] << std::endl;
    // }
    
}