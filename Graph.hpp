
#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.hpp"
#include "Vertex.hpp"
#include "GraphBase.hpp"
#include <string>
#include <vector>
#include <map>



class Graph : public GraphBase{

public:


void addVertex(std::string label);
void removeVertex(std::string label);
void addEdge(std::string label1, std::string label2, unsigned long weight);
void removeEdge(std::string label1, std::string label2);
unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
bool vertexExists(std::string label);


    
Vertex* findVertex(std::string label);

std::vector<Edge*> getIncEdges(Vertex* v);

unsigned long smallestWeight(std::vector<Edge*> e);

Vertex* visitVert(std::vector<Edge*> e, unsigned long x, Vertex* vert);
    
int retrieveKey(std::map<int, Vertex*>, Vertex*);

std::vector<Vertex*> vertices;
std::vector<Edge*> edges;

};


#endif
