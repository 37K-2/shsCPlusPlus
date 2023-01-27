// Linked Lists pt.1 By: Aaron Guo, Period 6
// Test if node.h and node.cpp actually works (if it makes a linked linkedlist)
#include <iostream>
#include <cstring>
#include <iomanip>
#include "node.h"
#include "linkedList.h"
#include "student.h"
using namespace std;

//commands
const char ADD[] = "ADD"; 
const char PRINT[] = "PRINT";
const char DELETE[] = "DELETE";
const char QUIT[] = "QUIT";
const char AVG[] = "AVERAGE";

//function prototypes
void addStudent(LinkedList* linkedlist);
void deleteStudent(LinkedList* linkedlist);
void averageStudent(LinkedList* linkedlist);

int main(){
    cout << "Student List C++" << endl;
    cout << fixed << setprecision(2); //set to hundredths

    LinkedList* linkedlist = new LinkedList(); //new linkedlist

    char cmd[8]; //command

    while(true){
        cout << "Type 'ADD', 'PRINT', 'DELETE', 'AVERAGE', 'QUIT': " << endl;
        cin >> cmd;
        if(strcmp(cmd, ADD) == 0)
            addStudent(linkedlist);
        if(strcmp(cmd, PRINT) == 0) {
            if(linkedlist->getSize() == NULL){
                cout << "List is empty :(" << endl;
            } else {
                linkedlist->printNode(linkedlist->getHead());
                cout << endl;
            }
        }
        if(strcmp(cmd, DELETE) == 0)
            deleteStudent(linkedlist);
        if(strcmp(cmd, AVG) == 0)
            averageStudent(linkedlist);
        if(strcmp(cmd, QUIT) == 0){
            cout << "TEEHEE" << endl;
            delete linkedlist;
            break;
        }
    }
    return 0;
}

void addStudent(LinkedList* linkedlist){
    Student* student = new Student();
    
    cout << "First Name: ";
    cin >> student->firstName;
    cout << "Last Name: ";
    cin >> student->lastName;
    cout << "ID: ";
    cin >> student->id;
    cout << "GPA: ";
    cin >> student->gpa;

    if(linkedlist->idExists(student->id)){
        cout << "ID already exists." << endl;
        delete student;
        return;
    }
    linkedlist->add(linkedlist->getHead(), NULL, student, true);
    cout << "Added Student" << endl;
}

void deleteStudent(LinkedList* linkedlist){
    if(linkedlist->getSize() == NULL){
        cout << "List is empty :(" << endl;
        return;
    }
    cout << "Enter ID to delete: ";
    int id;
    cin >> id;
    if (!linkedlist->idExists(id)){
        cout << "I couldn't find the ID :(" << endl;
        return;
    }
    linkedlist->remove(linkedlist->getHead(), NULL, id);
    cout << "Deleted!" << endl;
}

void averageStudent(LinkedList* linkedlist){
    if(linkedlist->getSize() == NULL){
        cout << "List is empty :(" << endl;
        return;
    }
    float* avg = linkedlist->getAverageGpa();
    cout << "Average GPA of Students: " << *avg << endl;
    delete avg;
}