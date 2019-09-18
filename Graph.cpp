
#include "Edge.hpp"
#include "Vertex.hpp"
#include "Graph.hpp"
#include <exception>
#include <string>
#include <tuple>
#include <algorithm>
#include <queue>
#include <map>
#include <climits>

//adds a vertex to the graph but DOES not connect it
 void Graph::addVertex( std::string label){

     for(int i = 0; i < int(vertices.size()); i++){
         
         if(vertices[i]->label == label){
             
             throw std::logic_error("Vector with that label already exists");
             
         }
     }
     
     //if vertex doesn't exist it is added to vertices vector
     
     Vertex* newVertex = new Vertex(label);
     
     vertices.push_back(newVertex);
     
 }

//adds and edge with a weight to 2 vertices
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    
    //makes sure vertex won't connect to itself
    if(label1 == label2){
        
        throw std::logic_error("Vertices cannot connect to themself");
        
    }
    
    bool vert1Found = false;
    bool vert2Found = false;
    
    Vertex* vert1 = nullptr;
    Vertex* vert2 = nullptr;
    
    //Searches for the 2 vertices
    for(int i = 0; i < int(vertices.size()); i++){
        
        if(vertices[i]->label == label1){
            
                
                vert1Found = true;
                vert1 = vertices[i];
                
            }
        
        
        if(vertices[i]->label == label2) {
            
            vert2Found = true;
            vert2 = vertices[i];
            
        }
        

    }
    
    
    //if both vertices found connect them with edge and add edge to vector of edges else throw error
    if(vert1Found && vert2Found){
        
        Edge* newEdge = new Edge(vert1, vert2, weight);
        
        edges.push_back(newEdge);
        
        vert1->adjVerts.push_back(vert2);
        vert2->adjVerts.push_back(vert1);
    
    } else {
        
        throw std::logic_error("Vertex not found");
        
    }
    
}


//removes an edge between 2 vertices
void Graph::removeEdge(std::string label1, std::string label2){
    
   
        
    //finds both vertices and assigns them to a & b
    Vertex* a = findVertex(label1);
    Vertex* b = findVertex(label2);
    
    //check whether the vertices share an edge and removes each vertex from the others adjacency list
    if(a->isAdjacentTo(b)){
        
        Edge* e;
        
        a->removeAdjacency(b);
        b->removeAdjacency(a);
        
        //find edge in edges vector and remove it
        for(int i = 0; i < int(edges.size()); i++){
            
            if( (edges[i]->vertex1 == a || edges[i]->vertex2 == a) && (edges[i]->vertex1 == b || edges[i]-> vertex2 == b) ) {
                
                e = edges[i];
                
                edges.erase(edges.begin()+i);
                
                delete e;
            }
            
        
        }
        
    } else {
        
        throw std::logic_error("Edge not found");
        
    }
    
    
}


unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){
 
    
    std::vector<std::string> prevNodes(vertices.size(), "0");
    
   

    std::vector<unsigned long> distances;
    std::map<int, Vertex*> vertexMap;
    
    //maps each vertex to a number
    for(int i = 0; i < int(vertices.size()); i++){
        
        vertexMap.insert( std::pair<int, Vertex*>(i, vertices[i]) );
        
    }
    
    Vertex* start = findVertex(startLabel); //returns vertex with startLabel
    Vertex* end = findVertex(endLabel); //returns vertex with endLabel
    
    std::priority_queue<std::pair <Vertex*, unsigned long>, std::vector<std::pair<Vertex*, unsigned long> >, std::greater<std::pair<Vertex*, unsigned long> > > pq; //creates a priority queue that holds a vertex and it's weight as nodes
    
    
    std::vector< std::vector< std::pair < Vertex*, unsigned long> > > adjList; //2D vector that holds adjacent vertices
    
    //std::vector< std::vector < std::string > > vertPath;
    
    
    
    //initializes the adjaceny list 2D vector rows
    for(int i = 0; i < int(vertices.size()); i++){
        
        std::vector<std::pair< Vertex*, unsigned long> > row;
        adjList.push_back(row);
        
    }
    
    
    
    //fills the rows the pairs of vertices and their distance from start node
    for(int i = 0; i < int(vertices.size()); i++) {
        
        std::vector<Edge*> incEdges = getIncEdges(vertices[i]);
        
        for(int j = 0; j < int(incEdges.size()); j++) {
            
            Edge* e = incEdges[j];
            
            unsigned long aWeight = incEdges[j]->weight;
            
            Vertex* v = e->opposite(vertices[i]);
            
            adjList[i].push_back(std::make_pair(v, aWeight));
            
        }
        
        
        
    }
    
    
    //sets all initial distances to infinity
    for(int i = 0; i < int(adjList.size()); i++){
        
        
        distances.push_back(ULONG_MAX);
        
    }
  
  
    pq.push(std::make_pair(start, 0));
    
    distances[retrieveKey(vertexMap, start)] = 0; //sets the distance from start node to itself as 0
    
    //Finds the shortest path and will update the path if a shorter one is found
    while (!pq.empty()) {
        
        
        Vertex* vert = pq.top().first;
        
        
        
        pq.pop();
        
        
        int u = retrieveKey(vertexMap, vert);
        
        for( int i = 0; i < int(adjList[u].size()); i++){
            
            
        
            Vertex* vertFriend = adjList[u][i].first;
            
            int v = retrieveKey(vertexMap, vertFriend);

            std::string x = vert->getLabel();
            
            unsigned long weight = adjList[u][i].second;
            
            if(distances[v] > distances[u] + weight){
                
                distances[v] = distances[u] + weight;
             
                pq.push(std::make_pair(vertFriend, distances[v]));
                
                prevNodes[v] = vert->getLabel();
           
            }
            
        
            
        }
        
        
    }
    
    //Creates a vector of the path of nodes starting with the end node and goes backwards to start
    Vertex* x = end;
    while(x != start){
     
        std::string add = x->getLabel();
        
        path.push_back(add);
        
        int j = retrieveKey(vertexMap, x);
     
       
        x = findVertex(prevNodes[j]);
       
    }
    
    std::reverse(path.begin(), path.end()); // reverses the vector
    
    path.insert(path.begin(), start->getLabel()); //appends the start vertex to the beginning of the vector


    return distances[retrieveKey(vertexMap, end)];
    
}

    
    




void Graph::removeVertex(std::string label){
    
    std::vector<int> indexToDelete;   //a vector that stores the indexes of vertices to be deleted
    Vertex* vertexToDelete = findVertex(label);
    Edge* edgeToDelete = nullptr;
    Vertex* opposite;
    
 
    int y = 0; //used to save the index number of the vertex so it can be deleted
    
    //find vertex in vetrices vector
    for(int i = 0; i < int(vertices.size()); i++) {
     
        if(vertices[i] == vertexToDelete){
            
            y = i;
            break;
        }
        
    }
    
    
    
    //find the edges that are incident with vertex to delete and adds the index number to a vector
    for(int i = 0; i < int(edges.size()); i++){
        
      
        if(edges[i]->isIncidentOn(vertexToDelete)){
            
            opposite = edges[i]->opposite(vertexToDelete);
            
            opposite->removeAdjacency(vertexToDelete);      //remove vertex to be deleted from adjacency list of other vertex
            
            indexToDelete.push_back(i);
        
        }
        
        
    }
    
    //deletes edges that contain the vertex to be deleted started with the highest index number
    for(int i = int((indexToDelete.size()-1)); i >= 0; i--){
        
        
        edgeToDelete = edges[indexToDelete[i]];
        
        edges.erase(edges.begin()+indexToDelete[i]);

        delete edgeToDelete;
    }
  

    
    
    //removes vertex from vertices vector
    vertices.erase(vertices.begin() + y);
    delete vertexToDelete;
        
 
}

     
bool Graph::vertexExists(std::string label){
    
    for(int i = 0; i < int(vertices.size()); i++){
        
        if(vertices[i]->label == label){
            
            return true;
            
        }
     
    }
    
    return false;
}



Vertex* Graph::findVertex(std::string label){
    
    if(vertexExists(label)){
        
        for(int i = 0; i <  int(vertices.size()); i++){
            
            if(vertices[i]->label == label){
                
                return vertices[i];
                
            }
            
            
        }
        
        
    } else {
        
        throw std::logic_error("Vertex not found.");
        
    }
    
    return nullptr;
}





std::vector<Edge*> Graph::getIncEdges(Vertex* v){
    
    std::vector<Edge*> incEdges;
    
    for(int i = 0; i < int(edges.size()); i++){
        
        if( (edges[i]->vertex1 == v || edges[i]->vertex2 == v) && (edges[i]->vertex1 == v || edges[i]-> vertex2 == v) ) {
            
            incEdges.push_back(edges[i]);
            
            
        }
        
    }
    
    return incEdges;
    
}

unsigned long Graph::smallestWeight(std::vector<Edge*> e){
 
    unsigned long toReturn = e[0]->weight;
    
    for(int i = 0; i < int(e.size()); i++){
        
        if(e[i]->weight < toReturn){
            
            toReturn = e[i]->weight;
        }
    }
    
    return toReturn;
}

//Traverses to the vertex on the opposite of the edge
Vertex* Graph::visitVert(std::vector<Edge*> e, unsigned long x, Vertex* vert){
 
    Vertex* v = nullptr;
    
    for(int i = 0; i < int(e.size()); i++){
        
        if(e[i]->weight == x){
            
            v = e[i]->opposite(vert);
            
        }
    
        
    }
    return v;
}

//retrieves key from map by VALUE; the key integer will be used as an index for other vectors
int Graph::retrieveKey(std::map<int, Vertex*> m, Vertex* v){

    std::map<int, Vertex*>::const_iterator it;
    int key = -1;
    
    for (it = m.begin(); it != m.end(); ++it)
    {
        if (it->second == v)
        {
            key = it->first;
            break;
        }
    }

    return key;
    
}
