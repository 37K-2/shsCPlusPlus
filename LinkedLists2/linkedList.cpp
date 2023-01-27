#include <iostream>
#include <cstring>
#include "linkedList.h"

using namespace std;

LinkedList::LinkedList(){
    this->head = NULL;
    this->size = 0;
}

LinkedList::~LinkedList(){
    Node* cur = head;
    while(cur != NULL){
        Node *temp = cur->getNext();
        delete cur;
        cur = temp;
    }  
}

void LinkedList::add(Node *cur, Node* prev, Student *newStudent, bool isHead){
    if (cur == NULL && isHead) {  // 0 elements in list
        this->head = new Node(newStudent);
        this->size = 1;
        return;
    }
    if(cur->getNext() == NULL){ //1 element in list
        if(newStudent->id < cur->getStudent()->id){ //new student is less than cur student then set before
            Node *nodePointer = new Node(newStudent);
            if(prev != NULL)
                prev->setNext(nodePointer);
            else
                this->head = nodePointer;
            nodePointer->setNext(cur);
            this->size++;
        }
        else{
            cur->setNext(new Node(newStudent));
            this->size++;
        }
        return;
    }
    if(newStudent->id < cur->getStudent()->id){ //new student is less than cur student then set before
        Node *nodePointer = new Node(newStudent);
        if(prev != NULL)
            prev->setNext(nodePointer);
        else
            this->head = nodePointer;
        nodePointer->setNext(cur);
        this->size++;
    }
    else{
        this->add(cur->getNext(), cur, newStudent, false);
    }

}

void LinkedList::remove(Node* cur, Node* prev, int id){
    if(cur == NULL)
        return;
    if(cur->getStudent()->id == id){
        Node *next = cur->getNext();
        if(prev != NULL && next != NULL){
            delete cur;
            prev->setNext(next);
            this->size--;
        }
        else{
            if(prev == NULL){
                this->head = next;
                delete cur;
                this->size--;
            }
            if(next == NULL){
                prev->setNext(NULL);
                delete cur;
                this->size--;
            }
        }
        return;
    }
    this->remove(cur->getNext(), cur, id);
}

bool LinkedList:: idExists(int id){
    Node* cur = this->head;
    while(cur != NULL){
        if(cur->getStudent()->id == id)
            return true;
        cur = cur->getNext();
    }
    return false;
}

void LinkedList::getAverageGpa(Node* cur, float* gpaSum){
    if(cur == NULL)
        return;
    (*gpaSum) += cur->getStudent()->gpa;
    this->getAverageGpa(cur->getNext(), gpaSum);
}

float* LinkedList::getAverageGpa(){
    float* gpaSum = new float(0);
    Node* cur = this->head;
    this->getAverageGpa(cur, gpaSum);
    (*gpaSum) /= this->size;
    return gpaSum;
}

void LinkedList::printNode(Node* cur){
    if(cur == NULL)
        return;
    cout << "Student Name: " << cur->getStudent()->firstName << " " << cur->getStudent()->lastName << "   ID: " << cur->getStudent()->id << "   GPA: " << cur->getStudent()->gpa << endl;
    this->printNode(cur->getNext());
}

int LinkedList::getSize(){
    return this->size;
}

Node* LinkedList::getHead(){
    return this->head;
}