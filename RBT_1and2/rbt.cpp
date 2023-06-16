#include "rbt.h"

#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// Terminal formatting codes
// used https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal as reference
#define underline "\033[4m"
#define red "\033[31m"
#define reset "\033[0m"

redBlackTree::redBlackTree() {
    this->nullVertex = new vertex();
    this->rootVertex = this->nullVertex;
    this->size = 0;
}

redBlackTree::~redBlackTree() { 
    this->destruct(this->rootVertex); 
}

void redBlackTree::destruct(vertex* current) { // remove all the nodes in the tree
    if (current == this->nullVertex)
        return;
    vertex* left = current->leftVertex;
    vertex* right = current->rightVertex;

    delete current;

    this->destruct(left);
    this->destruct(right);
}

void redBlackTree::addValue(int data) { // add node to tree
    vertex* newvertex = new vertex(this->nullVertex, data);

    vertex* addTo = nullptr; // find node that should be added to
    vertex* current = this->rootVertex;
    while (current != this->nullVertex) {
        addTo = current;
        if (newvertex->value > current->value)
            current = current->rightVertex;
        else
            current = current->leftVertex;
    }

    newvertex->parentVertex = addTo;
    if (addTo == nullptr) // root is null
        this->rootVertex = newvertex;
    else if (newvertex->value > addTo->value)
        addTo->rightVertex = newvertex;
    else
        addTo->leftVertex = newvertex;

    if (newvertex->parentVertex == nullptr) { // root is null
        newvertex->color = 'b'; // set new node to black
        return;
    }

    if (newvertex->parentVertex->parentVertex == nullptr) //node parent is black, if new node parent parent is null then new node parent is root and root doesnt have parent of null (2nd level on tree only)
        return;

    this->additionFix(newvertex); // other cases
}

// Runs through cases 3, 4, and 5 to maintain the properties of a Red-Black Tree
void redBlackTree::additionFix(vertex* cur) {
    vertex* uncle;
    while (cur->parentVertex->isRed()){ // don't fix insertion if the parent's color is black since doesn't violate RBT properties
        if (cur->parentVertex == cur->parentVertex->parentVertex->rightVertex) {
            uncle = cur->parentVertex->parentVertex->leftVertex;
            if (uncle->isRed()) { // both parent & uncle of current node is red
                // set the parent and uncle to black, set grandparent to red
                uncle->color = 'b';
                cur->parentVertex->color = 'b';
                cur->parentVertex->parentVertex->color = 'r';
                cur = cur->parentVertex->parentVertex; // check if current node's grandparent is root
            } else {// uncle is black -> parent is left and node is right OR parent is right and node is left
                if (cur == cur->parentVertex->leftVertex) { // current is the left child, set tree rotation through the current node's parent
                    cur = cur->parentVertex;
                    this->rightRotation(cur);
                }
                // uncle is black.  Parent is left and node is left OR parent is right and node is right, swap the parent and the grandparent 
                cur->parentVertex->color = 'b'; //colours
                cur->parentVertex->parentVertex->color = 'r';
                // set tree rotation through current node's grandparent
                this->leftRotation(cur->parentVertex->parentVertex);
            }
        } 
        else {
            uncle = cur->parentVertex->parentVertex->rightVertex;

            if (uncle->isRed()) {// both the parent and the uncle of the current node is red
                // then set the parent and uncle to black, and set the grandparent to red
                uncle->color = 'b';
                cur->parentVertex->color = 'b';
                cur->parentVertex->parentVertex->color = 'r';
                cur = cur->parentVertex->parentVertex; // check to see if current node's grandparent is root
            } else {// uncle is black.  Parent is left and node is right OR parent is right and node is left
                if (cur == cur->parentVertex->rightVertex) { // current node is the left child
                    // set up a tree rotation through the current node's parent
                    cur = cur->parentVertex;
                    this->leftRotation(cur);
                }
                //  uncle is black, parent is left and node is left OR parent is right and node is right, s wap the parent and the grandparent
                cur->parentVertex->color = 'b'; // colours
                cur->parentVertex->parentVertex->color = 'r';
                // set up a tree rotation through current node's grandparent
                this->rightRotation(cur->parentVertex->parentVertex);
            }
        }
        if (cur == this->rootVertex)
            break;
    }
    this->rootVertex->color = 'b';
}

// remove a node from the tree, used https://www.programiz.com/dsa/red-black-tree as a reference for deletion and deletion fix algorithms.
bool redBlackTree::removeValue(int data) {
    vertex* foundvertex = this->rootVertex;
    vertex* fix;
    vertex* originalVertex;

    // find the node that should be deleted
    while (foundvertex != this->nullVertex) {
        if (foundvertex->value == data)
            break;

        if (foundvertex->value <= data)
            foundvertex = foundvertex->rightVertex;
        else
            foundvertex = foundvertex->leftVertex;
    }

    if (foundvertex == this->nullVertex) // correct node is not found
        return false;

    // store node that we want to delete and the color of that node for later
    originalVertex = foundvertex;
    char foundvertexOriginalColor = originalVertex->color;

    if (foundvertex->leftVertex == this->nullVertex) { // The node to delete has one non-leaf child to the right
        fix = foundvertex->rightVertex;
        this->transplant(foundvertex, foundvertex->rightVertex);
    } 
    else if (foundvertex->rightVertex == this->nullVertex) { // The node to delete has one non-leaf child to the left
        fix = foundvertex->leftVertex;
        this->transplant(foundvertex, foundvertex->leftVertex);
    } 
    else {
        originalVertex = this->getMinimum(foundvertex->rightVertex); // get the in-order successor (the smallest node of the found node's right subtree)
        foundvertexOriginalColor = originalVertex->color; // update the color of the minimum subtree
        fix = originalVertex->rightVertex; // need to fix the right child of minimum subtree

        if (originalVertex->parentVertex == foundvertex)
            fix->parentVertex = originalVertex;
        else {
            this->transplant(originalVertex, originalVertex->rightVertex);
            originalVertex->rightVertex = foundvertex->rightVertex;
            originalVertex->rightVertex->parentVertex = originalVertex;
        }

        this->transplant(foundvertex, originalVertex);
        originalVertex->leftVertex = foundvertex->leftVertex;
        originalVertex->leftVertex->parentVertex = originalVertex;
        originalVertex->color = foundvertex->color;
    }

    delete foundvertex;

    if (foundvertexOriginalColor == 'b') // only fix RBT properties if we're removing a black node, since removing red nodes doesn't violate the properties of an RBT
        this->removalFix(fix);
    return true;
}

// used https://www.programiz.com/dsa/red-black-tree as a reference again to maintain RBT properties after deletion 

void redBlackTree::removalFix(vertex* toFix) {
    vertex* current;

    while (toFix != rootVertex && !toFix->isRed()) {
        if (toFix == toFix->parentVertex->leftVertex){ // node to fix is on the left side of its parent
            current = toFix->parentVertex->rightVertex; // store the right sibling
            if (current->isRed()){ // right child of the parent of our current node is red
                current->color = 'b';
                toFix->parentVertex->color = 'r';
                this->leftRotation(toFix->parentVertex);
                current = toFix->parentVertex->rightVertex;
            }

            if (!current->leftVertex->isRed() && !current->rightVertex->isRed()){ // both the right and the leftChild of our current node is black
                current->color = 'r';
                toFix = toFix->parentVertex;
            } 
            else {
                if (!current->rightVertex->isRed()) { // only the right child of our current node is black
                    current->leftVertex->color = 'b';
                    current->color = 'r';
                    this->rightRotation(current);
                    current = toFix->parentVertex->rightVertex;
                }

                // only the right child of our current node is red
                current->color = toFix->parentVertex->color;
                toFix->parentVertex->color = 'b';
                current->rightVertex->color = 'b';
                this->leftRotation(toFix->parentVertex);
                toFix = this->rootVertex;
            }
        } else{ // same as above but all uses of right and left are swapped (tree is mirrored)
            current = toFix->parentVertex->leftVertex;
            if (current->isRed()) {
                current->color = 'b';
                toFix->parentVertex->color = 'r';
                this->rightRotation(toFix->parentVertex);
                current = toFix->parentVertex->leftVertex;
            }

            if (!current->rightVertex->isRed() && !current->rightVertex->isRed()) {
                current->color = 'r';
                toFix = toFix->parentVertex;
            } 
            else {
                if (!current->leftVertex->isRed()) {
                    current->rightVertex->color = 'b';
                    current->color = 'r';
                    this->leftRotation(current);
                    current = toFix->parentVertex->leftVertex;
                }

                current->color = toFix->parentVertex->color;
                toFix->parentVertex->color = 'b';
                current->leftVertex->color = 'b';
                this->rightRotation(toFix->parentVertex);
                toFix = this->rootVertex;
            }
        }
    }
    toFix->color = 'b'; // node to fix should become black
}

/*
    Get the uncle of any node.
    Will return the node's parent's left node if the given node is on the right.
    Will return the node's parent's right node if the given node is on the left.
*/
vertex* redBlackTree::getUncle(vertex* node) {
    if (node->parentVertex == node->parentVertex->parentVertex->rightVertex)
        return node->parentVertex->parentVertex->leftVertex;
    else
        return node->parentVertex->parentVertex->rightVertex;
}

// rotate the subtrees of an origin node to the left
void redBlackTree::leftRotation(vertex* v) {
    vertex* right = v->rightVertex;
    v->rightVertex = right->leftVertex;
    if (right->leftVertex != this->nullVertex)
        right->leftVertex->parentVertex = v;

    right->parentVertex = v->parentVertex;
    if (v->parentVertex == nullptr) // top of tree
        this->rootVertex = right;
    else if (v == v->parentVertex->leftVertex) // origin is to the right of the parent
        v->parentVertex->leftVertex = right;
    else
        v->parentVertex->rightVertex = right;

    right->leftVertex = v;
    v->parentVertex = right;
}

// Rotate the substrees of an origin node to the right
void redBlackTree::rightRotation(vertex* v) {
    vertex* left = v->leftVertex;
    v->leftVertex = left->rightVertex;
    if (left->rightVertex != this->nullVertex)
        left->rightVertex->parentVertex = v;

    left->parentVertex = v->parentVertex;
    if (v->parentVertex == nullptr)
        this->rootVertex = left;
    else if (v == v->parentVertex->rightVertex)
        v->parentVertex->rightVertex = left;
    else
        v->parentVertex->leftVertex = left;

    left->rightVertex = v;
    v->parentVertex = left;
}

// replace the node being deleted with its successor or predecessor node while maintaining properties of the RBT
void redBlackTree::transplant(vertex* toDelete, vertex* replacement) {
    if (toDelete->parentVertex == nullptr) // top of tree
        this->rootVertex = replacement;
    else if (toDelete == toDelete->parentVertex->leftVertex)
        toDelete->parentVertex->leftVertex = replacement;
    else
        toDelete->parentVertex->rightVertex = replacement;
    replacement->parentVertex = toDelete->parentVertex;
}

// get the minimum (predecessor) node of any node
vertex* redBlackTree::getMinimum(vertex* v) {
    while (v->leftVertex != this->nullVertex)
        v = v->leftVertex;
    return v;
}

// to visualize the tree
void redBlackTree::display(vertex* cur, vector<char> indent, bool left) {
    if (cur == this->nullVertex) // at end of subtree
        return;
    // print and update for indentation
    for (vector<char>::iterator it = indent.begin(); it != indent.end(); it++)
        cout << *it << "  ";
    if (left)
        indent.push_back(' ');
    else
        indent.push_back('|');
    // print node value, position, and color
    cout << (cur == this->rootVertex ? "T" : (left ? "L" : "R")) << "--->";
    cout << (cur->isRed() ? red : "") << underline << cur->value << reset << endl;
    // display subtrees
    display(cur->rightVertex, indent, false);
    display(cur->leftVertex, indent, true);
}

// wrapper function to display the tree
void redBlackTree::displayTree() {
    vector<char> indent;
    this->display(this->rootVertex, indent, false);
}

// search for a value in the tree
bool redBlackTree::findValue(int val) {
    vertex* current = this->rootVertex; // start at the root
    while (true) {
        if (current == this->nullVertex) // if at null node then value doesn't exist
            return false;
        if (current->value == val) // node found
            return true;

        // continue to next node depending on if the value is less than or greater than the current node
        if (current->value > val)
            current = current->leftVertex;
        else
            current = current->rightVertex;
    }
}