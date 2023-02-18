// Hash Table By: Aaron Guo, Period 6
// Actual code which should function as student list, but using a hashmap + chaining + rehashing :O
#include <iostream>
#include <cstring>
#include <iomanip>
#include "node.h"
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
void addStudent(Node** &array, int &arrSize);
void deleteStudent(Node** &array, int &arrSize);
void rehash(Node** &array, int &arrSize);
int hashFunc(int id, int arraySize);

int main(){
    int arrSize = 128;
    Node** array = new Node*[arrSize];
    for (int x = 0; x<arrSize; x++){
        array[x] = nullptr;
    }

    cout << "Student List C++ (Hash Table Version)" << endl;
    cout << fixed << setprecision(2); //set to hundredths

    char cmd[8]; //command

    while(true){
        cout << "Type 'ADD', 'PRINT', 'DELETE', 'RANDOM', 'QUIT': " << endl;
        cout << "-> ";
        cin >> cmd;
        if(strcmp(cmd, ADD) == 0) //add something to list
            addStudent(array, arrSize);
        if(strcmp(cmd, PRINT) == 0) { //printing the list
            for(int x=0; x<arrSize; x++){
                if(array[x] != nullptr){
                    cout << "Hashed ID: " << x << endl;
                    Node* next = array[x];
                    while(next != nullptr){
                        cout << "Unhashed ID: " << next->getStudent()->id << endl;
                        cout << "   Name: " << next->getStudent()->firstName << " " << next->getStudent()->lastName << endl;
                        cout << "   GPA: " << next->getStudent()->gpa << endl;
                        next = next->getNext();
                    }
                    cout << endl;
                }
            }
        }
        if(strcmp(cmd, DELETE) == 0) //delete something from list
            deleteStudent(array, arrSize);
        if(strcmp(cmd, QUIT) == 0){ //quit function
            cout << "TEEHEE" << endl;
            break;
        }
    }
    return 0;
}

void addStudent(Node** &array, int &arrSize){
    Student* student = new Student();
    int collisionCount = 0;
    
    cout << "First Name: "; //inputs
    cin >> student->firstName;
    cout << "Last Name: ";
    cin >> student->lastName;
    cout << "ID: ";
    cin >> student->id;
    cout << "GPA: ";
    cin >> student->gpa;

    int hashedNum = hashFunc(student->id, arrSize);
    
    if (array[hashedNum] == nullptr)
        array[hashedNum] = new Node(student);
    else{
        collisionCount++;
        Node* newStudent = new Node(student);
        Node* next = array[hashedNum];
        while (next->getNext() != nullptr){
            next = next->getNext();
            collisionCount++;
        }
        next->setNext(newStudent);
    }
    //function to rehash if collisionCount > 3
    if(collisionCount >= 3)
        rehash(array, arrSize);
    
    cout << "Added Student" << endl;
}

void rehash(Node** &oldArray, int &oldArrSize){
    cout << "Rehashing..." << endl;
    int newArrSize = oldArrSize*2;
    Node** newArray = new Node*[newArrSize];
    int collisionCount = 0;
    for (int x = 0; x<newArrSize; x++){
        newArray[x] = nullptr;
    }

    for(int x = 0; x<oldArrSize; x++){
        if(oldArray[x] != nullptr){
            Node* next = oldArray[x];
            while(next != nullptr){
                //cout << "hi" << endl;
                Student* student = new Student();
                strcpy(student->firstName, next->getStudent()->firstName);
                strcpy(student->lastName, next->getStudent()->lastName);
                student->id = next->getStudent()->id;
                student->gpa = next->getStudent()->gpa;

                int newHashedNum = hashFunc(student->id, newArrSize);

                if (newArray[newHashedNum] == nullptr)
                    newArray[newHashedNum] = new Node(student);
                else{
                    collisionCount++;
                    Node* newStudent = new Node(student);
                    Node* next2 = newArray[newHashedNum];
                    while (next2->getNext() != nullptr){
                        next2 = next2->getNext();
                        collisionCount++;
                    }
                    next2->setNext(newStudent);
                }
                next = next->getNext();
            }
        }
    }

    oldArray = newArray;
    oldArrSize = newArrSize;

    cout << "Finished Rehashing" << endl;

    if(collisionCount >= 3)
        rehash(oldArray, oldArrSize);
}

void deleteStudent(Node** &array, int &arrSize){
    int id;
    cout << "Enter ID to delete: " << endl;
    cin >> id;
    int hashedNum = hashFunc(id, arrSize);

    Node* previous = nullptr;
    Node* current = array[hashedNum];
    bool firstItr = true;
    
    while(current != nullptr){
        if(current->getStudent()->id == id){
            if(firstItr){
                Node* temp = current->getNext();
                delete current;
                array[hashedNum] = temp;
                cout << "Deleted!" << endl;
                return;
            }
            else{
                previous->setNext(current->getNext());
                delete current;
                array[hashedNum] = previous;
                cout << "Deleted!" << endl;
                return;
            }
        }
        firstItr = false;
        previous = current;
        current = current->getNext();
    }
    cout << "ID doesn't exist. :(" << endl;
}

int hashFunc(int id, int arraySize){
    //cout << id%arraySize << endl;
    return id%arraySize;
}