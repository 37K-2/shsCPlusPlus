#include <stdlib.h>
#include <time.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#include "node.h"
#include "rbt.h"

using namespace std;

// commands
const char cmdAdd[] = "ADD";
const char optManual[] = "MANUAL";
const char flagDone[] = "DONE";
const char optFile[] = "FILE";
const char cmdSearch[] = "SEARCH";
const char cmdDelete[] = "DELETE";
const char cmdDisplay[] = "DISPLAY";
const char cmdQuit[] = "QUIT";

int main() {
    redBlackTree* tree = new redBlackTree();

    cout << "Red Black Tree" << endl;

    while (true) {
        cout << "-------------------------------------" << endl;
        cout << "ADD, DISPLAY, SEARCH, DELETE, or QUIT" << endl;
        cout << " > ";
        char cmd[8];
        cin >> cmd;

        if (strcmp(cmd, cmdAdd) == 0) { // add numbers
            // display info and get user input
            cout << "MANUAL or FILE" << endl;
            cout << " > ";
            char opt[7];
            cin >> opt;

            if (strcmp(opt, optManual) == 0) { // manual input
                cout << "Add by typing integers seperated by spaces. Type ""\"DONE\" when finished."<< endl;

                char input[17];
                char count = 0;
                int skipped = 0;
                while (true) { // get input
                    cin >> input;
                    if (strcmp(input, flagDone) == 0) // to indicate there is no more numbers to be inputted
                        break;
                    int value;
                    sscanf(input, "%d", &value); // scan for numbers
                    if (value <= 0 || value > 999) // must be between 0 and 999
                        skipped++;
                    else
                        tree->addValue(value);
                    count++;
                }
                if (skipped > 0)
                    cout << "Make sure numbers are between 0 and 999." << endl;
                cout << "Added " << (count - skipped) << " numbers." << endl;
            }
            if (strcmp(opt, optFile) == 0) { // input via file
                cout << "Enter file name > ";
                char filename[261];
                cin >> filename;

                // get all numbers in the file (space separated)
                vector<int> numbers;
                int numberCount = 0;

                ifstream numbersFile(filename); // create the file stream
                if (numbersFile.is_open()) { // if file is accessible, continuously read space-separated integers from the file until the end of the stream is reached
                    int val;
                    while (!numbersFile.eof()) {
                        numbersFile >> val;
                        numbers.push_back(val);
                        numberCount++;
                    }
                    numbersFile.close();

                    // sort through all numbers to make sure they are in the range
                    int skipped = 0;
                    for (int i = 0; i < numberCount; i++) {
                        if (numbers[i] <= 0 || numbers[i] > 1000)
                            skipped++;
                        else
                            tree->addValue(numbers[i]);
                    }

                    if (skipped > 0)
                        cout << "Make sure numbers are between 0 and 999." << endl;
                    cout << "Added " << (numberCount - skipped) << " numbers." << endl;
                } 
                else
                    cout << "Failed to open file: " << filename << endl;
            }
        }
        if (strcmp(cmd, cmdSearch) == 0) {
            cout << "Enter a number to search for: ";
            int number;
            cin >> number;
            bool found = tree->findValue(number);
            if (found)
                cout << "The value " << number << " was found!" << endl;
            else
                cout << "The value " << number << " was not found!" << endl;
        }
        if (strcmp(cmd, cmdDelete) == 0) {
            cout << "Enter a number to delete: " << endl;
            int number;
            cin >> number;
            bool result = tree->removeValue(number);
            if (result)
                cout << number << " successfully removed." << endl;
            else
                cout << "Failed to remove " << number << "." << endl;
        }
        if (strcmp(cmd, cmdDisplay) == 0) // display the RBT
            tree->displayTree();
        if (strcmp(cmd, cmdQuit) == 0) // quit
            break;
    }

    delete tree;
    return 0;
}