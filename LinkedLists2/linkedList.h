#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "node.h"
#include "student.h"
#include <iostream>
using namespace std;

class LinkedList{
  private:
    Node *head;
    int size;
    void printNode(Node *cur);
    void getAverageGpa(Node *cur, float *gpaSum);
    void add(Node *cur, Node *prev, Student *newStudent, bool isHead);
    void remove(Node *cur, Node *prev, int id);

  public:
    LinkedList();
    ~LinkedList();

    bool idExists(int id);
    float *getAverageGpa();
    void printList();
    int getSize();
    Node *getHead();
};
#endif