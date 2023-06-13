#include <vector>

#include "types.h"

using namespace std;

// return true if found connection to provided other node (if not null)
bool node::isConnectedTo(node* other) {
    return this->getConnectionTo(other) != nullptr;
}

// get edge object for the connection between the current node and the provided other node
edge* node::getConnectionTo(node* other) {
    vector<edge*>::iterator it;
    for (it = this->connections.begin(); it != this->connections.end(); it++) {
        if ((*it)->end == other)
            return *it;
    }
    return nullptr;
}