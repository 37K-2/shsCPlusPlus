#include <iostream>
#include "node.h"
using namespace std;

Node::Node(Student* student){
  this->student=student;
}

Node::~Node(){
  delete student;
}

Node* Node::getNext(){
  return this->nextNode;
}

void Node::setNext(Node* nextNode){
  this->nextNode = nextNode;
}

Student* Node::getStudent(){
  return this->student;
}

void Node::setStudent(Student* student){
  this->student = student;
}
