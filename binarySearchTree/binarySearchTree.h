#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "node.h"

class binarySearchTree{
 public:
  binarySearchTree();
  ~binarySearchTree();
  void add (int data);
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
  void destructor(Node *current);
};

#endif

