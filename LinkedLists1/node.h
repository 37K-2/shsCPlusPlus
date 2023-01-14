#ifndef NODE_H
#define NODE_H
#include <iostream>
#include "student.h"
using namespace std;

class Node{
 public:
  Node(Student* student);
  ~Node();

  Node* getNext();
  Student* getStudent();
  void setNext(Node* nextNode);
  void setStudent(Student* student);
  
 private:
  Student* student;
  Node* nextNode;
};

#endif
