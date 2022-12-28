#include "localchange.h"


/*function that returns the area of a triangle, given 3 points*/
double trianglearea(Point a, Point b, Point c){
    Polygon triangle;
    triangle.push_back(a);
    triangle.push_back(b);
    triangle.push_back(c);
    double area = abs(triangle.area());

    return area;
}

/*function that returns the area of the convex hull of a polygon*/
double convexhullarea(Polygon cv){
    Point start = Point(cv[0][0],cv[0][1]);      //first point of convex hull
    double cvarea = 0.0;
    for(int i=1; i<=cv.size()-2; i++){
        double trarea = trianglearea(start, Point(cv[i][0],cv[i][1]),Point(cv[i+1][0],cv[i+1][1])); //area of seperate triangles
        cvarea += trarea;       //area of convex hull
    }
    return cvarea;
}

/*computes the area of the polygon*/
double polygonarea(Polygon pol){
    Polygon cv;
    CGAL::convex_hull_2(pol.begin(),pol.end(),std::back_inserter(cv));  //create and store convex hull in polygon cv
    if(!cv.is_counterclockwise_oriented()){
        cv.reverse_orientation();             //make sure vonvex hull orientation is counterclockwise
    }
    double cvarea = convexhullarea(cv);
    if(cv==pol){            //convex hull is similar to pol 
        return cvarea;
    }

    Vector inpoints;
    int i=0, j=0;
    double remove = 0.0;
    Vector cvpoints;
    bool flag,flag2=1;
    for(int i=0; i<cv.size(); i++){
        cvpoints.push_back(Point(cv[i][0],cv[i][1]));   //vector with all the points of the convex hull
    }
    while(j<pol.size()&&flag2){
        int counter = 0;
        flag = 0;
        int index;
        while((!flag) && j<pol.size()){
            std::cout << "This is point " << j << ": " << Point(pol[j][0],pol[j][1]) << std::endl;
            for(int i=0; i<cvpoints.size(); i++){
                if(Point(pol[j][0],pol[j][1])==cvpoints[i]){    //point of polygon is also into the convex hull
                    flag = 1;
                    //pop
                    std::cout << "Found point " << j << ": " << cvpoints[i] << std::endl;
                    break;
                }
            }
            if(!flag){          //point of polygon is not into the convex hull
                inpoints.push_back(Point(pol[j][0],pol[j][1]));
                j++;
                counter++;
            }
        }

        for(int r=0; r<inpoints.size(); r++){
            std::cout << "inpoints list " << inpoints[r] << std::endl;
        }

        if(j==pol.size()){      //end of polygon
            flag2 = 0;
            index = 0;
        }
        else{
            index = j;
        }

        if(counter==1){         //one inner point - not successive with the others
            std::cout << "Calculating triangle " << Point(pol[j-2][0],pol[j-2][1])<< ", " << Point(pol[j-1][0],pol[j-1][1])<< ", " << Point(pol[index][0],pol[index][1])<< std::endl;
            remove += trianglearea(Point(pol[j-2][0],pol[j-2][1]),Point(pol[j-1][0],pol[j-1][1]),Point(pol[index][0],pol[index][1]));
            inpoints.pop_back();        //remove inner point from vector
        }
        else if(counter>1){     //more than 1 successive points
            Polygon temp;
            for(int k=0; k<inpoints.size(); k++){
                temp.push_back(inpoints[k]);
            }
            temp.push_back(Point(pol[index][0],pol[index][1]));
            temp.push_back(Point(pol[j-counter-1][0],pol[j-counter-1][1]));

            std::cout << "recalling" << std::endl;
            remove = polygonarea(temp);
        }
        j++;
    }
    std::cout<<"END polygon area"<<std::endl;
    return (cvarea - remove);
}

/*function that receives the polygon from greedy functions, the polygon after the local change of the 
path and the edge and a boolean value whether maximization or minimization is needed. max=1 -> maximization, 
max=0 -> minimization */
/*bool localchange(Polygon oldpol, Polygon newpol, bool max){
    double oldarea = polygonarea(oldpol);
    std::cout << "pol 1 " << oldarea << std::endl;
    double newarea = polygonarea(newpol);
    std::cout << "pol 2 " << newarea << std::endl;
    if(max){                    //maximazation
        if(oldarea < newarea){  //new polygon has bigger area
            return 1;
        }
        else{
            return 0;
        }
    }
    else{                       //minimization
        if(newarea < oldarea){  //new polygon has smaller area
            return 1;
        }
        else{
            return 0;
        }
    }
}*/


//working with just area of cgal

/*function that receives the polygon from greedy functions, the polygon after the local change of the 
path and the edge and a boolean value whether maximization or minimization is needed. max=1 -> maximization, 
max=0 -> minimization */
bool localchange(Polygon oldpol, Polygon newpol, bool max){
    double oldarea = abs(oldpol.area());
    double newarea = abs(newpol.area());
    std::cout<<" old= "<<oldarea<<" new= "<<newarea<<std::endl;
    if(max){                    //maximazation
        if(oldarea > newarea){  //new polygon has bigger area
            return 1;
        }
        else{
            return 0;
        }
    }
    else{                       //minimization
        if(newarea > oldarea){  //new polygon has smaller area
            return 1;
        }
        else{
            return 0;
        }
    }
}