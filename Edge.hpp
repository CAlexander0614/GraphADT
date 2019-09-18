#ifndef EDGE_H
#define EDGE_H


#include <exception>
#include <vector>
#include "Vertex.hpp"

class Edge{

public:

    Vertex* vertex1;
    Vertex* vertex2;
    
    unsigned long weight;
    
public:
    Edge(Vertex* vertexA, Vertex* vertexB, unsigned long theWeight){
        
        vertex1 = vertexA;
        vertex2 = vertexB;
        weight = theWeight;
        
        
    }
    
    //checks whether edge and vertex are incident
    bool isIncidentOn(Vertex* v){
        
        if(v->label == vertex1->label|| v->label == vertex2->label){
            
            
            return true;
            
            
        } else {
            
            return false;
            
        }
    }
    
    //returns the opposite vertex of an edge
    Vertex* opposite(Vertex* v){
        
        if (isIncidentOn(v) == true){
            
            if(v == vertex1) {
                
                return vertex2;
            
            }else{
                
                
                return vertex1;
            }
            
        } else {
            
            throw std::logic_error("Edge is not incident to vertex");
            
        }
        
        
    }
    
    
    friend class Graph;
    friend class Vertex;
};




#endif
