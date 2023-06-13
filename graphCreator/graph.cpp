#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#include "graph.h"
#include "types.h"

#define reset "\033[0m"
#define green "\033[32m"

using namespace std;

graph::graph() {
    this->nodeCount = 0;
}

graph::~graph() {
    vector<node*>::iterator it;
    for (it = this->nodes.begin(); it != this->nodes.end(); it++) {
        vector<edge*>::iterator it1;
        for (it1 = (*it)->connections.begin(); it1 != (*it)->connections.end(); it1++) {
            delete *it1;
        }
        (*it)->connections.clear();
        delete *it;
    }
    this->nodes.clear();
}

// returns true if the nodeCount = 20
bool graph::isFull() {
    return this->nodeCount == 20;
}

// returns true if the nodeCount = zero
bool graph::isEmpty() {
    return this->nodeCount == 0;
}

bool graph::add(node* node_) {
    node* found = this->find(node_->label);
    if (found != nullptr)
        return false;
    this->nodes.push_back(node_);
    this->nodeCount++;
    return true;
}

// remove node with the given label from the graph
bool graph::remove(char* label) {
    // find the node
    vector<node*>::iterator foundNode;
    for (foundNode = this->nodes.begin(); foundNode != this->nodes.end(); foundNode++) {
        // got the node
        if (strcmp((*foundNode)->label, label) == 0) {
            // iterate through the node
            vector<edge*>::iterator connection;
            for (connection = (*foundNode)->connections.begin(); connection != (*foundNode)->connections.end(); connection++) {
                node* end = (*connection)->end;

                this->removeConnection(*foundNode, end);
                break;
            }
            delete *foundNode;
            this->nodes.erase(foundNode);
            this->nodeCount--;
            return true;
        }
    }
    return false;
}

// remove a connection between two nodes in the graph (does not remove nodes)
bool graph::removeConnection(node* first, node* second) {
    bool removed = false;
    // iterate through the connections for both nodes, since the connection could start at either one

    // interate through connections of the first node
    vector<edge*>::iterator it1;
    for (it1 = first->connections.begin(); it1 != first->connections.end(); it1++) {
        if ((*it1)->end == second) {
            delete *it1;
            first->connections.erase(it1);
            removed = true;
            break;
        }
    }

    // iterate through connections of the second node
    vector<edge*>::iterator it2;
    for (it2 = second->connections.begin(); it2 != second->connections.end(); it2++) {
        if ((*it2)->end == first) {
            delete *it2;
            second->connections.erase(it2);
            removed = true;
            break;
        }
    }
    return removed;
}

// find node with the label
node* graph::find(char* label) {
    vector<node*>::iterator it;
    for (it = this->nodes.begin(); it != this->nodes.end(); it++) {
        if (strcmp((*it)->label, label) == 0)
            return *it;
    }
    return nullptr;
}


void graph::printAdjacencyMatrix() { //print adjacency matrix, to show which nodes are connected to which. X meaning that two nodes are connected, while O means they are not connected
    // create adjacency matrix
    vector<vector<bool>> adjacencyMatrix(this->nodeCount, vector<bool>(this->nodeCount)); //create a vector of this->nodeCount bool vectors (each size this->nodeCount)
    for (int i = 0; i < this->nodeCount; i++) {
        for (int j = 0; j < this->nodeCount; j++) {
            node* first = this->nodes[i];
            node* second = this->nodes[j];
            bool connected = false;
            if (first->isConnectedTo(second))
                connected = true;
            adjacencyMatrix[i][j] = connected;
        }
    }

    for (int j = -1; j < this->nodeCount; j++) {
        for (int i = -1; i < this->nodeCount; i++) {
            if (j == -1 & i == -1) {
                cout << "   ";
                continue;
            }

            if (j == -1) { // print  top row of node labels
                int len = strlen(this->nodes[i]->label);
                int spacesCount = 3 - len;
                if (len == 1)
                    cout << " " << this->nodes[i]->label << " ";
                else
                    cout << this->nodes[i]->label << " ";

                continue;
            }

            if (i == -1) // print the side column of node labels
            {
                int len = strlen(this->nodes[j]->label);
                int spacesCount = 3 - len;
                cout << this->nodes[j]->label;
                for (int i = 0; i < spacesCount; i++) {
                    cout << " ";
                }
                continue;
            }

            if (adjacencyMatrix[i][j])
                cout << " " << green << "X" << reset << " ";
            else
                cout << " O ";
        }
        cout << endl;
    }
}

// get index of a node that matches the label of the given node
int graph::indexOf(node* node_) {
    vector<node*>::iterator it;
    for (it = this->nodes.begin(); it != this->nodes.end(); it++) {
        if (strcmp((*it)->label, node_->label) == 0)
            return it - this->nodes.begin();
    }
    return -1;
}

// get index of a node that matches the given label
int graph::indexOf(char* label) {
    vector<node*>::iterator it;
    for (it = this->nodes.begin(); it != this->nodes.end(); it++) {
        if (strcmp((*it)->label, label) == 0)
            return it - this->nodes.begin();
    }
    return -1;
}

// get index of the smallest unvisited node
int graph::minDistanceIndex(vector<float> distances, vector<bool> visited) {
    float minimum = INT_MAX;
    int index;

    for (int i = 0; i < this->nodeCount; i++) {
        if (!visited[i] && distances[i] < minimum) {
            minimum = distances[i];
            index = i;
        }
    }

    return index;
}

// Djikstra's algorithm (to find shortest path)
void graph::printShortestPath(node* start, node* end) {
    // vectors for recording info from Djikstra's algorithm
    vector<float> distances;
    vector<bool> visited;
    vector<char*> previousNodes;

    // prepare vectors
    for (int i = 0; i < this->nodeCount; i++) {
        distances.push_back(INT_MAX); // distance at infinity (they're unknown)
        visited.push_back(false); // set all nodes to "not visited"
        char lmao[1];
        strcpy(lmao, "");
        previousNodes.push_back(lmao); // set all of the previous nodes to nothing
    }

    int startIndex = this->indexOf(start);
    int endIndex = this->indexOf(end);

    distances[startIndex] = 0.0f; // distance from a node to itself should be 0

    // process for every node
    for (int i = 0; i < this->nodeCount; i++) {
        int idx = this->minDistanceIndex(distances, visited); // get the index of the smallest unvisited node
        visited[idx] = true; // visited node

        // iterate through all nodes again to update shortest distances and previous nodes for each node in the list
        for (int j = 0; j < this->nodeCount; j++) {
            // if node "j" not visited and node "i" is connected to the node "j",
            // current minimum node added to the current node's connection's weight is smaller than the actual distance between nodes "i" and "j"
            
            if (!visited[j] && this->nodes[idx]->isConnectedTo(this->nodes[j]) && distances[idx] + this->nodes[idx]->getConnectionTo(this->nodes[j])->weight < distances[j]) {
                // update previous nodes
                if (j == 0) {
                    char lmao[1];
                    strcpy(lmao, "");
                    previousNodes[j] = lmao;
                } else
                    previousNodes[j] = this->nodes[idx]->label;
                // update shortest distances
                distances[j] = distances[idx] + this->nodes[idx]->getConnectionTo(this->nodes[j])->weight;
            }
        }
    }

    node* current = end;
    vector<char*> path;

    // continue searching forshortest path until we hit a distance of infinity, or current node doesn't have a previous node
    while (true) {
        int currentIndex = this->indexOf(current);
        float distance = distances[currentIndex];
        if (distance == INT_MAX) // distance is infinity -> no connection between our current node and its previous node
        {
            cout << "No valid path found between nodes \"" << start->label << "\" and \"" << end->label << "\"" << endl;
            return;
        }
        path.push_back(current->label); // add the current node to the path vector
        char* previousLabel = previousNodes[currentIndex];
        if (strcmp(previousLabel, "") == 0) // if the label of the current node's previous node is nonexistent, then is at end of path
            break;
        // update the current node to the current node's previous node
        int previousIndexOf = this->indexOf(previousLabel);
        current = this->nodes[previousIndexOf];
    }

    // print out the path in reverse since nodes are added starting at the end of the path
    vector<char*>::reverse_iterator it;
    for (it = path.rbegin(); it != path.rend(); it++)
        cout << (*it) << " -> ";
    cout << "END" << endl;

    // print out the final path length
    cout << "Path length: " << distances[endIndex] << endl;
}

// use Djikstra's algorithm to find the shortest path to each node from a given starting node
void graph::printAllPaths(node* start) {
    // vectors for info from Djikstra's algorithm
    vector<float> distances;
    vector<bool> visited;
    vector<char*> previousNodes;

    // prepare the vectors
    for (int i = 0; i < this->nodeCount; i++) {
        distances.push_back(INT_MAX); // distances start at infinity (they're unknown)
        visited.push_back(false); // set all nodes to not visited
        char lmao[1];
        strcpy(lmao, "");
        previousNodes.push_back(lmao); // set all of the previous nodes to nothing
    }

    int startIndex = this->indexOf(start);

    distances[startIndex] = 0.0f; // distance from a node to the same node should be 0

    // repeat for every node
    for (int i = 0; i < this->nodeCount; i++) {
        int idx = this->minDistanceIndex(distances, visited); // get the index of the smallest unvisited node
        visited[idx] = true; // We've visited this node

        // iterate through all nodes again to update shortest distances and previous nodes for each node in list
        for (int j = 0; j < this->nodeCount; j++) {
            /*
                if node "j" isn't visited and node "i" is connected to the node "j",
                the current minimum node added to the current node's connection's weight is smaller than the actual distance between nodes "i" and "j"
            */
            if (!visited[j] && this->nodes[idx]->isConnectedTo(this->nodes[j]) && distances[idx] + this->nodes[idx]->getConnectionTo(this->nodes[j])->weight < distances[j]) {
                // update previous nodes
                if (j == 0) {
                    char lmao[1];
                    strcpy(lmao, "");
                    previousNodes[j] = lmao;
                } else
                    previousNodes[j] = this->nodes[idx]->label;

                // update shortest distances
                distances[j] = distances[idx] + this->nodes[idx]->getConnectionTo(this->nodes[j])->weight;
            }
        }
    }

    // print out all paths in a neat table
    cout << "Node    Distance from source node    Previous node" << endl;
    for (int i = 0; i < this->nodeCount; i++) {
        int len = strlen(this->nodes[i]->label);
        if (distances[i] == INT_MAX) {
            if (len == 1)
                cout << this->nodes[i]->label << "       NO PATH" << endl;
            else
                cout << this->nodes[i]->label << "      NO PATH" << endl;
        }
        else {
            if (len == 1)
                cout << this->nodes[i]->label << "       " << distances[i] << "                          " << previousNodes[i] << endl;
            else
                cout << this->nodes[i]->label << "      " << distances[i] << "                          " << previousNodes[i] << endl;
        }
    }
}