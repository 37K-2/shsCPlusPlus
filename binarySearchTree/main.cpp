// Binary Search Tree By: Aaron Guo, Period: 6
// Program is about Binary Search Tree w/recursive iteration

#include <stdlib.h>
#include <time.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#include "binarySearchTree.h"
#include "node.h"
using namespace std;

// commands
const char commandAdd[] = "ADD";
const char optionManual[] = "MANUAL";
const char done[] = "DONE";
const char optionFile[] = "FILE";
const char commandRemove[] = "REMOVE";
const char commandSearch[] = "SEARCH";
const char commandDisplay[] = "DISPLAY";
const char commandClear[] = "CLEAR";
const char commandQuit[] = "QUIT";

int main() {
  BinarySearchTree *b = new BinarySearchTree();

  cout << "Binary Search Tree" << endl;

  while (true) {
    cout << "ADD, REMOVE, SEARCH, DISPLAY, or QUIT" << endl; //display cmd
    cout << "> "; // get info
    char cmd[8];
    cin >> cmd;

    if (strcmp(cmd, commandAdd) == 0) {  // add numbers
      cout << "MANUAL or FILE" << endl;
      cout << "> "; // get info
      char opt[7];
      cin >> opt;

      if (strcmp(opt, optionManual) == 0) {  // input via console and not file
        cout << "Enter integers, seperated by spaces. Type \"DONE\" when finished." << endl;

        char input[17];
        char count = 0;
        int skipped = 0;
        while (true) {  // inputs seperated by space
          cin >> input;
          if (strcmp(input, done) == 0)  // tells that user is done inputting numbers
            break;
          int value;
          sscanf(input, "%d", &value);  // check input for numbers
          if (value <= 0 || value > 999)  // numbers must be in 0 and 999
            skipped++;
          else
            b->add(value);
          count++;
        }
        if (skipped > 0) 
          cout << skipped << " numbers were skipped." << endl;
        cout << "Added " << (count - skipped) << " numbers." << endl;
      }
      if (strcmp(opt, optionFile) == 0) {  // input via file
        cout << " Enter file name > "; // get file name
        char filename[261];
        cin >> filename;

        cout << "Reading in numbers... ";
        vector<int> numbers; //put numbers from file into vector
        int numberCount = 0;

        ifstream numbersFile(filename);  // file stream
        if (numbersFile.is_open()) {     // if file is accessable then read until there is no more
          int val;
          while (!numbersFile.eof()) {
            numbersFile >> val;
            numbers.push_back(val);
            numberCount++;
          }
          numbersFile.close();

          // sort numbers & check if passes requirements
          int skipped = 0;
          for (int i = 0; i < numberCount; i++) {
            if (numbers[i] <= 0 || numbers[i] > 1000)
              skipped++;
            else
              b->add(numbers[i]);
          }

          if (skipped > 0)
            cout << "Warning: " << skipped
                 << " numbers were skipped.  Make sure your numbers are "
                    "between 1 and 1000, exclusive."
                 << endl;
          cout << "Added " << (numberCount - skipped) << " numbers." << endl;
        } else
          cout << "Failed to open file: " << filename << endl;
      }
    }
    if (strcmp(cmd, commandRemove) == 0) {  // remove number
      cout << "Enter value to remove > "; // get info
      int number;
      cin >> number;

      if (b->search(number)) 
        b->remove(number);    // remove number if exists in tree
      else
        cout << "That number isn't in the tree!" << endl;  // number not in tree
    }
    if (strcmp(cmd, commandSearch) == 0) {  // find specific number
      cout << "Enter value to search for > ";
      int number;
      cin >> number;

      if (b->search(number))  
        cout << "Found " << number << " in the tree." << endl;  // if number in bst then print that it exists
      else
        cout << "Did not find " << number << " in the tree." << endl;  // number does not exist in bst
    }
    if (strcmp(cmd, commandDisplay) == 0) {  // print
      cout << endl;
      b->display();
      cout << endl;
    }
    if (strcmp(cmd, commandClear) == 0) {  // clear
      delete b;
      b = new BinarySearchTree();
      cout << "Cleared the tree!" << endl;
    }
    if (strcmp(cmd, commandQuit) == 0)  // exit out of program
      break;
  }

  delete b;
  return 0;
}
