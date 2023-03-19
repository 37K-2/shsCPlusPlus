// Linked Lists pt.2 By: Aaron Guo, Period 6
// Actual code which should function as student list
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
        if(strcmp(cmd, ADD) == 0) //add something to list
            addStudent(linkedlist);
        if(strcmp(cmd, PRINT) == 0) { //printing the list
            if(linkedlist->getSize() == 0){
                cout << "List is empty :(" << endl; //print if list is empty
            } else {
                linkedlist->printNode(linkedlist->getHead()); //print function from linked list class
                cout << endl;
            }
        }
        if(strcmp(cmd, DELETE) == 0) //delete something from list
            deleteStudent(linkedlist);
        if(strcmp(cmd, AVG) == 0) //avg values (gpa) from list
            averageStudent(linkedlist);
        if(strcmp(cmd, QUIT) == 0){ //quit function
            cout << "TEEHEE" << endl;
            delete linkedlist;
            break;
        }
    }
    return 0;
}

void addStudent(LinkedList* linkedlist){
    Student* student = new Student();
    
    cout << "First Name: "; //inputs
    cin >> student->firstName;
    cout << "Last Name: ";
    cin >> student->lastName;
    cout << "ID: ";
    cin >> student->id;
    cout << "GPA: ";
    cin >> student->gpa;

    if(linkedlist->idExists(student->id)){ //check if id already exists
        cout << "ID already exists." << endl;
        delete student;
        return;
    }
    linkedlist->add(linkedlist->getHead(), NULL, student, true); //add to list
    cout << "Added Student" << endl;
}

void deleteStudent(LinkedList* linkedlist){
    if(linkedlist->getSize() == 0){ // check if list is empty
        cout << "List is empty :(" << endl;
        return;
    }
    cout << "Enter ID to delete: ";
    int id;
    cin >> id;
    if (!linkedlist->idExists(id)){ //if id doesnt exist then print couldnt find id
        cout << "I couldn't find the ID :(" << endl;
        return;
    }
    linkedlist->remove(linkedlist->getHead(), NULL, id); //remove student
    cout << "Deleted!" << endl;
}

void averageStudent(LinkedList* linkedlist){ //find average gpa of students
    if(linkedlist->getSize() == 0){ //if size of linked list is 0 then list is empty (no gpa)
        cout << "List is empty :(" << endl;
        return;
    }
    float* avg = linkedlist->getAverageGpa(); //gpa of students
    cout << "Average GPA of Students: " << *avg << endl;
    delete avg;
}