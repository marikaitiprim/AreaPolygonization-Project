// /home/angelos/CGAL-5.5.1/scripts//cgal_create_CMakeLists -s sort
// cmake -DCGAL_DIR=/home/angelos/CGAL-5.5.1 .
// make


#include "pathlist.h"

/*This function combines two Pathlists into one.
*Pathlist a will enter first, while b will be second.
*/
Pathlist combine(Pathlist a, Pathlist b){
    Pathlist c;
    Vector Path;
    for(int i=0;i<a.size();i++){
        Path.clear();
        for(int j=0;j<a[i].size(); j++){
            Path.push_back(a[i][j]);
        }
        c.push_back(Path);
    }
    for(int i=0;i<b.size();i++){
        Path.clear();
        for(int j=0;j<b[i].size();j++){
            Path.push_back(b[i][j]);
        }
        c.push_back(Path);
    }
    return c;
}

/*This function takes the number of points in a path and the polygon
*and creates a vector called pathlist, which is a vector containing vectors of points.
*/
Pathlist createpaths(int pointnum, Polygon pol){
    Pathlist temp;
    int x=100;
    if(pol.size()>5000){
        x=1000;
    }
    if(pointnum<2){
        return temp;
    }
    Vector Path;
    int p=0;
    for(int i=0;i<pol.size();i++){
        Path.clear();
        for(int j=0;j<pointnum;j++){
            if(i+j>=pol.size()){
                p=i+j-pol.size();
            }
            else{
                p=i+j;
            }
           
            Path.push_back(pol[p]);
        }
        if(pol.size()>600){
            if(rand()%(pol.size()/x)==0){
            temp.push_back(Path);
            }
        }
        else{
            temp.push_back(Path);
        }
        
    }
    if(pointnum>2){
        Pathlist rest=createpaths(pointnum-1,pol);
        return combine(temp,rest);
    }
    else{
        return temp;
    }
    
}