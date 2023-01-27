#include "Node.h"
using namespace std;

Node::Node(Student* newstudent) 
{
  // Give node a pointer to Student class
  next = NULL;
  student = newstudent;
  
}
Node::~Node()
{
  //destructor
  next = NULL;
  student = NULL;
}
Node* Node::getNext()
{
  //return the info of the next node
  return next;
}
void Node::setNext(Node* newnext)
{
  //make next a pointer to the next node
  next = newnext;
}
Student* Node::getStudent()
{
  //return student pointer
  return student;
}
