#ifndef RBT_H
#define RBT_H

#include <vector>

#include "node.h"

using namespace std;

class redBlackTree {
private:
    vertex* root;
    vertex* nullVertex;
    int size;

    void destruct(vertex*);

    void display(vertex*, vector<char>, bool);

    void leftRotation(vertex*);
    void rightRotation(vertex*);
    void transplant(vertex*, vertex*);

    vertex* getUncle(vertex*);
    vertex* getMinimum(vertex*);

    void additionFix(vertex*);
    void removalFix(vertex*);

public:
    redBlackTree();
    ~redBlackTree();

    void addValue(int);
    bool removeValue(int);
    bool findValue(int);
    void displayTree();
};

#endif 

//self-balancing binary search tree (RBT)
