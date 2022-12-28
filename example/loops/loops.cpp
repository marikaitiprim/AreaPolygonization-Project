// /home/angelos/CGAL-5.5.1/scripts//cgal_create_CMakeLists -s sort
// cmake -DCGAL_DIR=/home/angelos/CGAL-5.5.1 .
// make

#include "loops.h"

/*
*A function that creates a vector of all the edges in a polygon
*/
SegmentVector edgeslist(Polygon pol){
    std::cout<<" IN EDGELIST"<<std::endl;
    SegmentVector temp;
    for(int i=0;i<pol.size()-1;i++){
        temp.push_back(Segment(pol[i],pol[i+1]));
    }
    temp.push_back(Segment(pol[pol.size()-1],pol[0]));
    return temp;
}

/*function to find neighbours of the path*/
Vector neighbours(Vector V, Polygon pol){
    std::cout<<" IN NEIGHBOURS"<<std::endl;
    Vector neigh;

    Point a;
    if(pol[0]==V[0]){           //1st point of polgon is also 1st point of the path
        neigh.push_back(pol[pol.size()-1]);
    }

    a = pol[0];
    for(int i=1; i<pol.size(); i++){        //for each vertex in the polygon
        if(pol[i]==V[0]){                       //if the point of the vertex is equal to the first point of the path
            neigh.push_back(a);         //first neighbour
        }
        a = pol[i];
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
    if(pol[pol.size()-1]==V[V.size()-1]){   //last point in the polygon is also the last in the path
        neigh.push_back(pol[0]);
    }
    std::cout<<" OUT NEIGHBOURS"<<std::endl;
    return neigh;

}

/*function that creates the small polygon we remove*/
Polygon removing(Segment e, Vector V){
    std::cout<<" IN REMOVING"<<std::endl;
    Polygon pol;
    pol.push_back(e.vertex(0));    //insert points of edge to be replaced
    pol.push_back(e.vertex(1));
    for(int i=0; i<V.size(); i++){
        pol.push_back(V[i]);        //insert points of the path
    }
    return pol;
}

/*function that creates the small polygon we add*/
Polygon adding(Vector V, Point a, Point b){
    std::cout<<" IN ADDING"<<std::endl;
    Polygon pol;
    pol.push_back(a);    //insert points of edge to be added
    for(int i=0; i<V.size(); i++){
        pol.push_back(V[i]);        //insert points of the path
    }
    pol.push_back(b);
    return pol;
}

/*
*This function takes in the polygon, a float representing the threshold, the list of edges and the list of paths
*and finds the best combinations of paths and edges to swift in order to create the polygon we need.
*more comments should be added once the function is complete. For now it prints the combinations it uses.
*/
Polygon loops(Polygon pol, double threshold,int L , bool maxmin){
    std::cout<<" IN LOOPS"<<std::endl;
    double DA=threshold+1.0;
    Segment e;
    Vector V;
    edgepath ep;
    EdgePath T;
    while(DA>=threshold){
        SegmentVector edgelist=edgeslist(pol);
        Pathlist Paths=createpaths(4, pol);     //change L
        for(int i=0; i<edgelist.size();i++){
            e=edgelist[i];
            for(int j=0;j<Paths.size();j++){
                V=Paths[j];
                
                // std::cout<<"edge is: "<<e[0]<<" - "<<e[1]<<"\t and path is: ";
                // for (int g=0;g<V.size();g++){
                //     std::cout<<V[g]<<" -> ";
                // }
                if ((std::find(V.begin(), V.end(), e[0]) != V.end())||(std::find(V.begin(), V.end(), e[1]) != V.end())) {
                    std::cout<<"\nskipped\n";
                    continue;
                }
                std::cout<<"\n";
                Vector neigh = neighbours(V,pol);
                //std::cout << "-------------------neighbours ---------------" << neigh[0] << "," << neigh[1] << std::endl;
                Polygon oldpol = removing(e,V);
                //std::cout << "-------------------removing polygon ---------------" << oldpol << " with size "<< oldpol.size()<< std::endl;
                Polygon newpol = adding(V,neigh[0],neigh[1]);
                //std::cout << "-------------------adding polygon ---------------" << newpol<< " with size "<< newpol.size() << std::endl;
                Polygon created=changePolygon(pol,V,e);
                //std::cout<<"___________________created has size:"<<created.size()<<std::endl;
                if(created.is_simple()){
                    if(localchange(oldpol,newpol,maxmin)){
                    ep.e = e;
                    ep.v = V;
                    T.push_back(ep);    //insert pair into the vector T
                    }
                    std::cout << "EIMAI MESA " << std::endl;
                }
            }
        }
        
        Polygon Snew = applyChanges(T,pol);
        DA = difference(pol,Snew);
        if(DA>=threshold){
            pol = Snew;
        }
        T.clear();
    }
    return pol; //pol will have to change with the name of the new polygon
}
