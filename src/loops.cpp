// /home/angelos/CGAL-5.5.1/scripts//cgal_create_CMakeLists -s sort
// cmake -DCGAL_DIR=/home/angelos/CGAL-5.5.1 .
// make

#include "loops.h"

/*
*A function that creates a vector of all the edges in a polygon
*/
SegmentVector edgeslist(Polygon pol){
    SegmentVector temp;
    for(int i=0;i<pol.size()-1;i++){
        temp.push_back(Segment(pol[i],pol[i+1]));
    }
    temp.push_back(Segment(pol[pol.size()-1],pol[0]));
    return temp;
}

/*function to find neighbours of the path*/
Vector neighbours(Vector V, Polygon pol){
    Vector neigh;

    Point a;
    if(pol[0]==V[0]){           //1st point of polgon is also 1st point of the path
        neigh.push_back(pol[pol.size()-1]);
        if(pol[pol.size()-1]==V[V.size()-1]){   //last point in the polygon is also the last in the path
            neigh.push_back(pol[0]);
            return neigh;
        }
    }

    a = pol[0];
    for(int i=1; i<pol.size(); i++){        //for each vertex in the polygon
        if(pol[i]==V[0]){                       //if the point of the vertex is equal to the first point of the path
            neigh.push_back(a);         //first neighbour
            break;
        }
        a = pol[i];
    }

    if(pol[pol.size()-1]==V[V.size()-1]){   //last point in the polygon is also the last in the path
        neigh.push_back(pol[0]);
        return neigh;
    }

    bool flag = 0;
    for(int i=0; i<pol.size(); i++){        //for each vertex in the polygon
        if(flag){
            neigh.push_back(pol[i]);        //second neighbour
            break;
        }
        if(pol[i]==V[V.size()-1]){                       //if the point of the vertex is equal to the last point of the path
            flag = 1;
        }
    }
    return neigh;

}

/*
*This function takes in the polygon, a double representing the threshold, the list of edges and the list of paths
*and finds the best combinations of paths and edges to swift in order to create the polygon we need. Applying local_search
*algorithm.
*/
Polygon loops(Polygon polygon, double threshold,int L , bool maxmin){
    double DA=threshold+1.0;
    Segment e;
    Vector V;
    edgepath ep;
    EdgePath T;
    double areas;
    if(maxmin){
        areas = 0.0;
    }else{
        areas = polygon.area();
    }
    Polygon pol = polygon;
    int counter = 0;
    bool flag = 0;
    while(DA>=threshold){
        SegmentVector edgelist=edgeslist(pol);
        Pathlist Paths=createpaths(L, pol);     
        for(int i=0; i<edgelist.size();i++){
            e=edgelist[i];
            for(int j=0;j<Paths.size();j++){
                V=Paths[j];
                
                if ((std::find(V.begin(), V.end(), e[0]) != V.end())||(std::find(V.begin(), V.end(), e[1]) != V.end())) {
                    continue;
                }
                
                Polygon created=changePolygon(pol,V,e);
                if(created.is_simple()){
                    if(localchange(pol.area(),created.area(),maxmin)){        //compare polygon areas
                        counter = 0;
                        if(localchange(areas,created.area(),maxmin)){      //compare new polygon area with previous areas
                            ep.e = e;
                            ep.v = V;
                            if(!T.empty()){
                                T.clear();
                            }
                            T.push_back(ep);    //insert pair into the vector T
                            areas = created.area();
                        }
                    }
                    else{
                        counter++;
                        if(counter>3*L){            //too many iterations without better solution
                            flag = 1;
                            break;
                        }
                    }
                }
            }
        }
        
        Polygon Snew = applyChanges(T,pol);

        DA = difference(pol,Snew);
        pol = Snew;
        if(!T.empty()){
            T.clear();
        }
        if(flag){
            return pol;
        }
    }
    return pol; 
}
