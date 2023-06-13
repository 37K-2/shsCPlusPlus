#ifndef TYPES_H
#define TYPES_H

#include <vector>

using namespace std;

// forward declarations
struct node;

struct edge {
    node* start;
    node* end;
    float weight;
};

struct node {
    char label[3];
    vector<edge*> connections;
    bool isConnectedTo(node*);
    edge* getConnectionTo(node*);
};

#endif 

// edge struct defines an edge, or a connection, between two nodes and holds a specified weight which is to be used in Djikstra's algorithm.
// node struct defines a graph node, and has a label (2 characters max) and a list of connections (edge objects).
