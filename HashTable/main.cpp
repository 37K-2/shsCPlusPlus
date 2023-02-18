// Hash Table By: Aaron Guo, Period 6
// Actual code which should function as student list, but using a hashmap + chaining + rehashing :O

//imports and packages and stuff
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <vector>
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
void randomGenerate(Node** &array, int &arrSize);
int hashFunc(int id, int arraySize);
bool idExists(int id, Node** &array, int arrSize);

int main(){
    //array size is 128, make array full of nullptr
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
            //goes through entire array, checks if theres something there, and prints
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
        if(strcmp(cmd, RANDOM) == 0) // randomize generation
            randomGenerate(array, arrSize);
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
    int id = -1;
    
    cout << "First Name: "; //inputs
    cin >> student->firstName;
    cout << "Last Name: ";
    cin >> student->lastName;
    cout << "ID: ";
    cin >> id;
    while(idExists(id, array, arrSize)){ //making sure that an id cannot be used twice
        cout << "ID is already used!" << endl;
        cout << "ID: ";
        cin >> id;
    }
    student->id = id;
    cout << "GPA: ";
    cin >> student->gpa;

    int hashedNum = hashFunc(student->id, arrSize); //find hash sum
    
    if (array[hashedNum] == nullptr) //if first in hashtable then make it the head
        array[hashedNum] = new Node(student);
    else{ // start counting if there are more than 3 collisions, as well as link the nodes together
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
    if(collisionCount >= 3) // if collision count more than 3 then rehash
        rehash(array, arrSize);
    collisionCount = 0; //reset collision count
    
    cout << "Added Student" << endl;
}

void rehash(Node** &oldArray, int &oldArrSize){
    cout << "Rehashing..." << endl;
    int newArrSize = oldArrSize*2; //make the size of the new hash *2,
    Node** newArray = new Node*[newArrSize]; // fill hash with nullptr
    int collisionCount = 0;
    for (int x = 0; x<newArrSize; x++){
        newArray[x] = nullptr;
    }

    for(int x = 0; x<oldArrSize; x++){ //loop through everything in old array, check if there are values in slot
        if(oldArray[x] != nullptr){ // if there are values in slot then put them in the new array with new hash
            Node* next = oldArray[x];
            while(next != nullptr){
                //cout << "hi" << endl;
                Student* student = new Student();
                strcpy(student->firstName, next->getStudent()->firstName);
                strcpy(student->lastName, next->getStudent()->lastName);
                student->id = next->getStudent()->id;
                student->gpa = next->getStudent()->gpa;

                int newHashedNum = hashFunc(student->id, newArrSize); // new hash

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

    oldArray = newArray; // set the previous arrays & sizes to the new ones
    oldArrSize = newArrSize;

    cout << "Finished Rehashing" << endl;
}

void deleteStudent(Node** &array, int &arrSize){
    int id; //give id to delete
    cout << "Enter ID to delete: " << endl;
    cin >> id;
    int hashedNum = hashFunc(id, arrSize); //find hash num of id

    Node* previous = nullptr;
    Node* current = array[hashedNum];
    bool firstItr = true;
    
    while(current != nullptr){ //loop through the array[hash]
        if(current->getStudent()->id == id){ //if id is here then delete
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
    cout << "ID doesn't exist. :(" << endl; //else id is not found and big RIP
}

void randomGenerate(Node** &array, int &arrSize){
    int studentNum = 0; //ask how much students to generate
    cout << "Number of Students to Generate: ";
    cin >> studentNum;

    vector<char*> firstNames, lastNames; //vector full of all student names + how much there are
    int firstNamesCount = 0, lastNamesCount = 0;

    ifstream firstNamesFile("firstNames.txt"); //open file, put some of the names into vector, close file
    if(firstNamesFile.is_open()){
        char temp[31];
        while(!firstNamesFile.eof()){  
            firstNamesFile >> temp;
            firstNames.push_back(new char[31]); 
            // cout << firstNames[firstNamesCount] << temp <<endl;
            strcpy(firstNames[firstNamesCount], temp);
            firstNamesCount++;
        }
        firstNamesFile.close();
    }
    ifstream lastNamesFile("lastNames.txt"); //same as first names but with last names
    if(lastNamesFile.is_open()){
        char temp[31];
        while(!lastNamesFile.eof()){   
            lastNamesFile >> temp;
            lastNames.push_back(new char[31]);
            strcpy(lastNames[lastNamesCount], temp);
            lastNamesCount++;
        }
        lastNamesFile.close();
    }

    srand(time(0)); //random
    int collisionCount = 0;
    
    int searchingID = 0;
    for(int x=0; x<studentNum; x++){ //search through whole list
        Student* student = new Student();

        int randomFirstName = rand() % 1000; //randomize first name and put it in
        strcpy(student->firstName, firstNames[randomFirstName]);
        int randomLastName = rand() % 1000; //same except last name
        strcpy(student->lastName, firstNames[randomLastName]);

        while(true){
            if(idExists(searchingID, array, arrSize)) //making sure only 1 id per person
                searchingID++;
            else
                break;
        }
        student->id = searchingID;
        student->gpa = (double)(rand()%500)/100; //some random GPA randomizer maker thing

        int hashedNum = hashFunc(student->id, arrSize); //find hashnum
    
        if (array[hashedNum] == nullptr) //if first one in array then it is head
            array[hashedNum] = new Node(student);
        else{ //otherwise make linked list of nodes
            collisionCount++;
            Node* newStudent = new Node(student);
            Node* prev = nullptr;
            Node* curr = array[hashedNum];
            while (curr != nullptr){
                prev = curr;
                curr = curr->getNext();
                collisionCount++;
            }
            prev->setNext(newStudent);
        }
        //function to rehash if collisionCount > 3
        if(collisionCount >= 3) //rehash if there are more than 3 in a hash.
            rehash(array, arrSize);
        collisionCount = 0;
    }
    

    cout << "Generated " << studentNum << " Students." << endl;

}

int hashFunc(int id, int arraySize){
    //cout << id%arraySize << endl;
    return id%arraySize; //hash funct is just remainder of id and arraySize
}

bool idExists(int id, Node** &array, int arrSize){
    int hash = hashFunc(id, arrSize); //hashNum
    Node* current = array[hash];
    while(current != nullptr){ //loop through array to see if id exists
        if(current->getStudent()->id == id)
            return true; //oh hey it does exist
        current = current->getNext();
    }
    //cout << exists << endl;
    return false; //it does not exist
}