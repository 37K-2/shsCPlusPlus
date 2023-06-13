#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

#include "types.h"

using namespace std;

class graph {
private:
    vector<node*> nodes;
    int nodeCount;
    edge* getShortestConnector(node*);
    int minDistanceIndex(vector<float>, vector<bool>);

public:
    graph();
    ~graph();
    bool isFull();
    bool isEmpty();
    bool add(node*);
    bool remove(char*);
    bool removeConnection(node*, node*);
    node* find(char*);
    void printAdjacencyMatrix();
    void printShortestPath(node*, node*);
    void printAllPaths(node*);
    int indexOf(node*);
    int indexOf(char*);
};

#endif 

// performs operation of the graph, and used to find the shortest path between two nodes (aka Djikstra's algorithm)
// some important functions are: add, remove, find, printShortestPath, printAllPaths, printAdjacencyMatrix, etc
