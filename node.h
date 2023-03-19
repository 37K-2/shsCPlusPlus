#ifndef NODE_H
#define NODE_H

template <class K>
struct linkedListNode{
  linkedListNode *next;
  K info;
  linkedListNode(K info);
};

template <class K>
struct treeNode{
  treeNode *left;
  treeNode *right;
  K info;

  treeNode(K info);

  bool value();
  bool operand();
  bool isNum();
};

template <class K>
struct 

#endif