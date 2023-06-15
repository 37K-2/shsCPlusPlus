#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "heap.h"

using namespace std;

const char cmdADD[] = "ADD";
const char addOptionMANUAL[] = "MANUAL";
const char addOptionFILE[] = "FILE";
const char addDONE[] = "DONE";
const char cmdREMOVE[] = "REMOVE";
const char removeOptionMAX[] = "MAX";
const char removeOptionALL[] = "ALL";
const char cmdDisplay[] = "DISPLAY";
const char cmdHELP[] = "help";
const char cmdQUIT[] = "QUIT";

int main()
{
    Heap *heap = new Heap(100);
    char cmd[8];

    cout << "Heap - Max Heap" << endl;

    while (true){
        cout << "--------------------------------------------" << endl << endl;
        cout << "Type ADD, REMOVE, DISPLAY, HELP, or QUIT" << endl;
        cout << "> ";
        cin >> cmd;

        if (strcmp(cmd, cmdADD) == 0){
            if (heap->isHeapFull())
                cout << "Heap is full." << endl;
            else{
                cout << "MANUAL or FILE" << endl;
                cout << "> ";

                char opt[7];
                cin >> opt;

                if (strcmp(opt, addOptionMANUAL) == 0){
                    cout << "Enter integers seperated with space. Type \"DONE\" when finished." << endl;

                    char input[17];
                    char count = 0;
                    int skipped = 0;
                    while (true){
                        if (heap->isHeapFull()){
                            cout << "Heap is full." << endl;
                            break;
                        }
                        cin >> input;
                        if (strcmp(input, addDONE) == 0)
                            break;
                        int value;
                        sscanf(input, "%d", &value);
                        if (value <= 0 || value > 1000)
                            skipped++;
                        else
                            heap->insert(value);
                        count++;
                    }
                    if (skipped > 0)
                        cout << skipped << " numbers were skipped due to not being between 1 and 1000." << endl;
                    cout << "Added " << (count - skipped) << " numbers." << endl;
                }
                if (strcmp(opt, addOptionFILE) == 0){
                    vector<int> numbers;
                    int numberCount = 0;

                    ifstream numbersFile("numbers.txt");
                    if (numbersFile.is_open()){
                        int val;
                        while (!numbersFile.eof()){
                            numbersFile >> val;
                            numbers.push_back(val);
                            numberCount++;
                        }
                        numbersFile.close();
                    }
                    cout << "finished." << endl;

                    cout << numberCount << " numbers were found.  How many do you want to add? ";
                    int amount;
                    cin >> amount;
                    if (amount < 0)
                        cout << "Number must be positive." << endl;
                    else{
                        if (amount > numberCount)
                            amount = numberCount;

                        int skipped = 0;

                        for (int i = 0; i < amount; i++){
                            if (heap->isHeapFull()){
                                cout << "Heap is full." << endl;
                                amount = i;
                                break;
                            }

                            if (numbers[i] <= 0 || numbers[i] > 1000)
                                skipped++;
                            else
                                heap->insert(numbers[i]);
                        }

                        cout << "Added " << (amount - skipped) << " numbers." << endl;
                    }
                }
            }
        }
        if (strcmp(cmd, cmdREMOVE) == 0){
            cout << "Type \"MAX\" to remove only the max number, \"ALL\" to remove everything." << endl;
            cout << "> ";

            char opt[8];
            cin >> opt;

            if (strcmp(opt, removeOptionMAX) == 0){
                int oldSize = heap->getHeapSize();
                int oldMax = heap->extractMax();
                int nwSize = heap->getHeapSize();
                int nwMax = heap->getMax();
                cout << "Old max value: " << oldMax << "   Old size: " << oldSize << endl;
                if (nwSize > 0)
                    cout << "New max value: " << nwMax << "   New size: " << nwSize << endl;
                else
                    cout << "New heap size is zero, no new max value exists." << endl;
            }
            if (strcmp(opt, removeOptionALL) == 0)
            {
                int size = heap->getHeapSize();
                cout << "Extracted numbers:" << endl;
                while (heap->getHeapSize() != 0){
                    cout << heap->extractMax() << " ";
                }
                cout << endl;
                cout << size << " numbers were removed from the heap." << endl;
            }
        }
        if (strcmp(cmd, cmdDisplay) == 0)
            heap->printHeap(0, 0);
        if (strcmp(cmd, cmdQUIT) == 0){
            delete heap;
            break;
        }
    }

    return 0;
}