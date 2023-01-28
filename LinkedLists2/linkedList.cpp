#include <iostream>
#include <cstring>
#include "linkedList.h"

using namespace std;

LinkedList::LinkedList(){
    this->head = NULL;
    this->size = 0;
}

LinkedList::~LinkedList(){ // current = head, loop and delete cur
    Node* cur = head;
    while(cur != NULL){
        Node *temp = cur->getNext();
        delete cur;
        cur = temp;
    }  
}

void LinkedList::add(Node *cur, Node* prev, Student *newStudent, bool isHead){
    if (cur == NULL && isHead) {  // 0 elements in list then none
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
            nodePointer->setNext(cur); //add student + increase size
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
        nodePointer->setNext(cur); //basically the same code as above
        this->size++;
    }
    else{
        this->add(cur->getNext(), cur, newStudent, false); //recursive
    }

}

void LinkedList::remove(Node* cur, Node* prev, int id){ //same thing as add but uses destructor/delete to remove
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

bool LinkedList:: idExists(int id){ //check if id exists via looping and checking each node
    Node* cur = this->head;
    while(cur != NULL){
        if(cur->getStudent()->id == id)
            return true;
        cur = cur->getNext();
    }
    return false;
}

void LinkedList::getAverageGpa(Node* cur, float* gpaSum){ //find the average gpa
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

void LinkedList::printNode(Node* cur){ //print function
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