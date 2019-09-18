#ifndef VERTEX_H
#define VERTEX_H
#include <string>
#include <vector>


#include <iostream>




class Vertex{

public:
    
    std::string label;
    std::vector<Vertex*> adjVerts;

    bool visited;

public:
    
    Vertex(std::string theLabel){
     
        label = theLabel;
        visited = false;
      
    }
    
    //checks wheter vertices are adjacent
    bool isAdjacentTo(Vertex* v){
        
        for(int i = 0; i < int(adjVerts.size()); i++){
            
            if(v == adjVerts[i]) {
                
                return true;
                
            }
            
        }
        return false;
    }

    //removes a vertex from another vertex's ajacency list
    void removeAdjacency(Vertex* v){
     
        for(int i = 0; i < int(adjVerts.size()); i++){
            
            
            if(adjVerts[i] == v) {
                
                adjVerts.erase(adjVerts.begin()+i);
                
                
            }
            
        
        }

    }
    
    //returns the vertex label
    std::string getLabel(){
    
        return label;
    }
    

    //prints a vertex's adjacent vertexs
    void printAdjVerts() {
     
        
        for(int i = 0; i < int(adjVerts.size()); i++){
            
            std::cout << adjVerts[i]->getLabel() << " ";
        }
        
    }
    
    
 
    
    friend class Graph;
    friend class Edge;
};

    
    

    
    



#endif 

