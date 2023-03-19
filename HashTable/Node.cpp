#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

Node::Node(Student* newStudent) {
  student = newStudent;
  next = nullptr;
}

Node::~Node() {
  delete student;
  next = nullptr;
}

Node* Node::getNext() {
  return next;
}

Student* Node::getStudent() {
  return student;
}

void Node::setNext(Node* newNext) {
  next = newNext;
}
