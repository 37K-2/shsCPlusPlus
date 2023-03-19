/* Student List (C++ Version) by: Aaron Guo, Period 6
 *
 * Takes in first and last name of the person, their ID and GPA via vectors
 * Add = add person, print = print list, delete = delete person, quit = quit program
 */

//required packages
#include <iostream>
#include <iomanip>
#include <cstring>
#include <ctype.h>
#include <vector>

using namespace std;

//struct for the student
struct Student{
  int id; // takes in ID of student
  float gpa; //takes in GPA of student
  char firstname[20]; //takes in First name of student
  char lastname[20]; // takes in last name of the student
};

// commands, needed for strcmp
const char ADD[] = "ADD"; // to add
const char PRINT[] = "PRINT"; // to print
const char DELETE[] = "DELETE"; // to delete
const char QUIT[] = "QUIT"; // to quit

// function prototypes
void readInStudent(vector<Student*>* studentlist); //take in students' name
void printStudents(vector<Student*>* studentlist); //print students' name
void deleteStudent(vector<Student*>* studentlist); //delete students' name

// main method
int main() {

  vector<Student*> students; //vector being used to store students

  cout << fixed << setprecision(2); //set GPA to be rounded to 2 decimals
  cout << "ADD to add student, PRINT to print students, DELETE to delete student, QUIT to quit program. Enter in Console below:" << endl;

  char cmd[7]; // big enough for largest command and the null char needed for strcmp

  while (true) {
    cout << "> ";
    cin >> cmd;

    // commands
    if (strcmp(cmd, ADD) == 0) 
      readInStudent(&students); //read in student
    if (strcmp(cmd, PRINT) == 0) 
      printStudents(&students); //print student
    if (strcmp(cmd, DELETE) == 0) 
      deleteStudent(&students); //delete student
    if (strcmp(cmd, QUIT) == 0) 
      break; //end program
  }

  return 0;
}

void readInStudent(vector<Student*>* studentlist) {
  Student* student = new Student(); //make a new student struct

  cout << "First name: "; 
  cin >> student->firstname; //take in first name, put it in struct
  cout << "Last name: ";
  cin >> student->lastname; //take in last name, put it in struct
  cout << "ID: ";
  cin >> student->id; //take in id, put it in struct
  cout << "GPA: ";
  cin >> student->gpa; // take in gpa, put it in struct


  for (vector<Student*>::iterator iter = studentlist->begin(); iter < studentlist->end(); iter++) { //from the start of vector to the end, increment by 1
    if ((*iter)->id == student->id) { //if the vector id is equal to the student id
      cout << "The id you entered already exists" << endl; // id already exists, don't add the person in
      return;
    }
  }

  studentlist->push_back(student); //push the struct into the vector

  cout << "Added" << endl; // tell the value has been added
}

void printStudents(vector<Student*>* studentlist) {
  cout << "All students:" << endl;
  for (vector<Student*>::iterator iter = studentlist->begin(); iter < studentlist->end(); iter++) { // from start of vector to end, increment by 1
    cout << (*iter)->firstname << " " << (*iter)->lastname << ", " << (*iter)->id << ", " << (*iter)->gpa << endl; // format to print out everything along with details
  }
}

void deleteStudent(vector<Student*>* studentlist) {
  cout << "Enter id: ";
  int id;
  cin >> id; //take in id to prepare delete of student

  bool found = false; //first assume the id doesnt exist
  int idx = 0;
  for (vector<Student*>::iterator iter = studentlist->begin(); iter < studentlist->end(); iter++) { // from start of vector to end, increment by 1
    if ((*iter)->id == id) { //if id is found IN the vector
      found = true; // make found true
      delete* iter; // delete the object in memory
      studentlist->erase(studentlist->begin() + idx); // remove the struct from the vector
      break;
    }
    idx++;
  }

  if (!found) { //if not found just print not found
    cout << "Not found" << endl;
    return;
  }

  cout << "Deleted" << endl; // print value has been deleted

}
