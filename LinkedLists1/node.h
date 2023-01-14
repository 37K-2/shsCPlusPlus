#ifndef NODE_H
#define NODE_H
#include <iostream>
#include "student.h"
using namespace std;

class Node{
 public:
  Node(Student* student); // node constructor 
  ~Node(); // for destructor

  Node* getNext(); //get the next node
  Student* getStudent(); // get the next student
  void setNext(Node* nextNode); // set next node that is pointed to
  void setStudent(Student* student); // set next student that is pointed to
  
 private:
  Student* student; // student pointer
  Node* nextNode; // node pointer
};

#endif
