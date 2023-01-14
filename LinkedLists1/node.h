#ifndef NODE_H
#define NODE_H
#include <iostream>
#include "student.h"
using namespace std;

class Node{
 public:
  Node(Student* student); // node takes in a student
  ~Node(); // for destructor

  Node* getNext(); //get the next node
  Student* getStudent(); // get the next student
  void setNext(Node* nextNode); // set next node
  void setStudent(Student* student); // set next student
  
 private:
  Student* student; // required variables (student)
  Node* nextNode; //required variables (nextnode)
};

#endif
