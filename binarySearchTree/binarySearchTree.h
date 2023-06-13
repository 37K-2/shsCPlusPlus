#ifndef BST_H
#define BST_H

#include "node.h"

class BinarySearchTree {
 public:
  BinarySearchTree();
  ~BinarySearchTree();
  void add(int data);
  void remove(int data);
  bool search(int data);
  void display();

 private:
  Node *root;
  int size;
  Node *add(Node *current, int data);
  Node *remove(Node *current, int data);
  bool search(Node *current, int data);
  void display(Node *current, bool left, int depth);
  Node *minValueNode(Node *current);
  void destruct(Node *current);
};

#endif 

// recreates bst. uses the node from node.h with the left and right in order to sort, left being < than parent and right being > than parent
