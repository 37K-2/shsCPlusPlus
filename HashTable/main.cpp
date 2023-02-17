// Hash Table By: Aaron Guo, Period 6
// Actual code which should function as student list, but using a hashmap + chaining + rehashing :O
#include <iostream>
#include <cstring>
#include <iomanip>
#include "node.h"
//#include "linkedList.h"
#include "student.h"
using namespace std;

//commands
const char ADD[] = "ADD"; 
const char PRINT[] = "PRINT";
const char DELETE[] = "DELETE";
const char QUIT[] = "QUIT";
const char AVG[] = "AVERAGE";
const char RANDOM[] = "RANDOM";

//function prototypes
void addStudent(Node** array, int arrSize, int** collisionCount);
//void deleteStudent(Node** array, int arrSize, int** collisionCount);
//void averageStudent(Node** array, int arrSize);
void rehash(Node** array, int arrSize, int** collisionCount);
int hashFunc(int id, int arraySize);

int main(){
    int arrSize = 128;
    Node** array = new Node*[arrSize];
    for (int x = 0; x<arrSize; x++){
        array[x] = nullptr;
    }
    int** collisionCount = new int*[arrSize];
    for (int x = 0; x<arrSize; x++){
        collisionCount[x] = 0;
    }

    cout << "Student List C++ (Hash Table Version)" << endl;
    cout << fixed << setprecision(2); //set to hundredths

    char cmd[8]; //command

    while(true){
        cout << "Type 'ADD', 'PRINT', 'DELETE', 'AVERAGE', 'RANDOM', 'QUIT': " << endl;
        cout << "-> ";
        cin >> cmd;
        if(strcmp(cmd, ADD) == 0) //add something to list
            addStudent(array, arrSize, collisionCount);
        if(strcmp(cmd, PRINT) == 0) { //printing the list
            for(int x=0; x<arrSize; x++){
                if(array[x] != NULL){
                    cout << "Hashed ID: " << x << endl;
                    Node* next = array[x];
                    while(next != NULL){
                        cout << "Unhashed ID: " << next->getStudent()->id << endl;
                        cout << "   First Name: " << next->getStudent()->firstName << endl;
                        cout << "   Last Name: " << next->getStudent()->lastName << endl;
                        cout << "   GPA: " << next->getStudent()->gpa << endl;
                        next = next->getNext();
                    }
                    cout << endl;
                }
            }
        }
        /*
        if(strcmp(cmd, DELETE) == 0) //delete something from list
            deleteStudent(linkedlist);
        if(strcmp(cmd, AVG) == 0) //avg values (gpa) from list
            averageStudent(linkedlist);
        if(strcmp(cmd, QUIT) == 0){ //quit function
            cout << "TEEHEE" << endl;
            delete linkedlist;
            break;
        }
        */
    }
    return 0;
}

void addStudent(Node** array, int arrSize, int** collisionCount){
    Student* student = new Student();
    
    cout << "First Name: "; //inputs
    cin >> student->firstName;
    cout << "Last Name: ";
    cin >> student->lastName;
    cout << "ID: ";
    cin >> student->id;
    cout << "GPA: ";
    cin >> student->gpa;

    int hashedNum = hashFunc(student->id, arrSize);
    
    if (array[hashedNum] == NULL && collisionCount[hashedNum] == 0){
        array[hashedNum] = new Node(student);
        collisionCount[hashedNum]++;
    }
    else{
        Node* newStudent = new Node(student);
        Node* next = array[hashedNum];
        while (next->getNext() != NULL){
            next = next->getNext();
        }
        next->setNext(newStudent);
        collisionCount[hashedNum]++;
    }
    //function to rehash if collisionCount > 3
    
    cout << "Added Student" << endl;
}

void rehash(Node** oldArray, int oldArrSize, int** oldCollisionCount){
    int newSize = oldArrSize*2;
    Node** newArray = new Node*[newSize];
    for (int x = 0; x<newSize; x++){
        newArray[x] = nullptr;
    }
}

/*
void deleteStudent(LinkedList* linkedlist){
    cin.ignore();
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
*/
int hashFunc(int id, int arraySize){
    //cout << id%arraySize << endl;
    return id%arraySize;
}