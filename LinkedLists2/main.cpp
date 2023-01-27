// Linked Lists pt.1 By: Aaron Guo, Period 6
// Test if node.h and node.cpp actually works (if it makes a linked list)
#include <iostream>
#include <cstring>
#include "node.h"
#include "student.h"
using namespace std;

const char ADD_CMD[] = "ADD";
const char PRINT_CMD[] = "PRINT";
const char DELETE_CMD[] = "DELETE";
const char QUIT_CMD[] = "QUIT";
const char AVG_CMD[] = "AVERAGE";

void addStudent()

int main(){
    // set current node counting and the first node to nothing (null)
    Node* currentNode = NULL;
    Node* firstNode = NULL;
    
    // add students via first and last name, id, and gpa, and insert into the list
    Student *s1 = new Student();
    strcpy(s1->firstName, "Aaron");
    strcpy(s1->lastName, "Guo");
    s1->id = 419452;
    s1->gpa = 4.14;
    Node *id1 = new Node(s1);
    firstNode = id1;

    Student *s2 = new Student();
    strcpy(s2->firstName, "Ena");
    strcpy(s2->lastName, "Shinonome");
    s2->id = 430010;
    s2->gpa = 2.57;
    Node *id2 = new Node(s2);
    id1->setNext(id2); // connect the two nodes via setNext

    Student *s3 = new Student();
    strcpy(s3->firstName, "Airi");
    strcpy(s3->lastName, "Momoi");
    s3->id = 319218;
    s3->gpa = 6.32;
    Node *id3 = new Node(s3);
    id2->setNext(id3);

    currentNode = firstNode; //set the first node to be the current node

    while(currentNode != NULL) {
        cout << "Student Name: " << currentNode->getStudent()->firstName << " " << currentNode->getStudent()->lastName << "\nID: " << currentNode->getStudent()->id << "\nGPA: " << currentNode->getStudent()->gpa << endl;
        currentNode = currentNode->getNext();
    }//print out the nodes

    /*
    for(int x=0; x<currentNode->getStudent(); x++){
        cout << "Student Name: " << currentNode->getStudent()->firstName << " " << currentNode->getStudent()->lastName << "\nID: " << currentNode->getStudent()->id << "\nGPA: " << currentNode->getStudent()->gpa << endl;
        currentNode = currentNode->getNext();
    }
    */
    return 0;
}
