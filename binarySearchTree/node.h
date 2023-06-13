#ifndef NODE_H
#define NODE_H

struct Node {
  int data;
  Node *left;
  Node *right;
  Node(int data);
};

#endif  

// tree node that contains left & right node pointers for the bst w/int to hold the node's data
