#ifndef NODE_H
#define NODE_H
#include <iostream>
#include "Student.h"
using namespace std;

class Node {
 public:
  Node(Student* newstudent);
  ~Node();
  Node* getNext();
  Student* getStudent();
  void setNext(Node* newnext);
  Node* next; 
  Student* student;

};
#endif
