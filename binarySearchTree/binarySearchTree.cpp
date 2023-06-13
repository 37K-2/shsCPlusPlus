#include "binarySearchTree.h"

#include <iomanip>
#include <iostream>

#define underlineFormat "\033[4m"
#define resetFormat "\033[24m"

using namespace std;

BinarySearchTree::BinarySearchTree() {
  this->root = nullptr;
  this->size = 0;
}

BinarySearchTree::~BinarySearchTree() {
  this->destruct(this->root);  // remove nodes recusively
}

void BinarySearchTree::destruct(Node *current) {
  if (current == nullptr)  // end of tree or dne
    return;

  Node *left = current->left;
  Node *right = current->right;

  delete current;

  destruct(left);  // run on both left and right
  destruct(right);
}

void BinarySearchTree::add(int data) {  // add number to tree
  if (this->root == nullptr) {          // if root dne, create
    this->root = new Node(data);
    return;
  }
  this->add(this->root, data);
}

Node *BinarySearchTree::add(Node *current, int data) {
  if (current == nullptr)  // did not find a place to add the value
    return new Node(data);

  // insert data
  if (data > current->data)  // insert right, if data is greater than current
    current->right = add(current->right, data);
  else if (data < current->data)  // same thing as above but left side
    current->left = add(current->left, data);
  return current;  // return node after inserting
}

void BinarySearchTree::remove(int data) {
  this->root = this->remove(this->root, data);
}

Node *BinarySearchTree::remove(Node *current, int value) {
  if (current == nullptr)  // value doesn't exist
    return current;
  if (value < current->data)  // move left
    current->left = this->remove(current->left, value);
  else if (value > current->data)  // move right
    current->right = this->remove(current->right, value);
  else {
    if (current->left == nullptr &&
        current->right == nullptr) {  // node has no child
      delete current;
      current = nullptr;
    } else if (current->left == nullptr) {  // right node exists, but not left
      Node *temp = current;
      current = current->right;
      delete temp;
    } else if (current->right == nullptr) {  // left node exists, but not right
      Node *temp = current;
      current = current->left;
      delete temp;
    } else {  // node has 2 children
      Node *temp = this->minValueNode(
          current->right);  // find min value of the children nodes
      current->data = temp->data;
      current->right = this->remove(current->right, temp->data);
    }
  }
  return current;
}

bool BinarySearchTree::search(int data) {
  return this->search(this->root, data);
}

bool BinarySearchTree::search(Node *current, int data) {
  if (current == nullptr)  // value doesn't exist
    return false;
  if (current->data == data)  // data found
    return true;
  if (data < current->data)  // move left
    return search(current->left, data);
  else  // move right
    return search(current->right, data);
}

void BinarySearchTree::display() { this->display(this->root, false, 0); }

/*
    Private recursive display function

    Params:
     - Node *current: the current leaf
     - bool left: if the current leaf is a left node or a right node
     - int depth: how far the line should be indented
*/
void BinarySearchTree::display(Node *current, bool left, int depth) {
  if (current == nullptr)  // end of list
    return;
  display(current->right, false,
          depth + 1);  // First display the right subtree (at the top)

  cout << setw(depth * 5) << "";  // Set up correct formatting

  if (left)  // arrows for child nodes n stuff idk
    cout << "\\";
  else {
    if (current != this->root) cout << "/";
  }

  cout << underlineFormat << current->data << resetFormat
       << endl;  // Add a bit of underlining and print the data
  display(current->left, true,
          depth + 1);  // Then display the left subtree (at the bottom)
}

Node *BinarySearchTree::minValueNode(
    Node *node) {  // find min value of child nodes
  Node *current = node;
  while (current && current->left != nullptr) {
    current = current->left;
  }
  return current;
}
