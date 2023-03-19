/* Zuul (C++ Version) By: Aaron Guo, Period: 6
* You are stuck in a room, and you need to get all 5 items and arrive in room/sector 23 to escape
* TL;DR/Summary: Basically Zuul but coded in C++.
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "item.h"
#include "room.h"

using namespace std;

char EXIT_UP[] = "up";
char EXIT_DOWN[] = "down";
char EXIT_LEFT[] = "left";
char EXIT_RIGHT[] = "right";

const char LOOK_COMMAND[] = "look";
const char TAKE_COMMAND[] = "take";
const char DROP_COMMAND[] = "drop";
const char GO_COMMAND[] = "go";
const char INVENTORY_COMMAND[] = "inv";
const char HELP_COMMAND[] = "help";
const char QUIT_COMMAND[] = "quit";

int main() {
    // gacha ticket
    item* gacha_ticket = new item();
    strcpy(gacha_ticket->description, "gacha-ticket");
    // airi fly plane
    item* airi_fly_plane = new item();
    strcpy(airi_fly_plane->description, "airi-fly-plane");
    // kanade ballin
    item* kanade_ballin = new item();
    strcpy(kanade_ballin->description, "kanade-ballin");
    // paid crystals
    item* paid_crystals = new item();
    strcpy(paid_crystals->description, "paid-crystals");
    // level 36 ap=
    item* level_36_ap = new item();
    strcpy(level_36_ap->description, "level-36-ap");

    //rooms
    room* r1 = new room();
    strcpy(r1->description, "You're in Sector 1 of the maze.");
    room* r2 = new room();
    strcpy(r2->description, "You're in Sector 2 of the maze.");
    room* r3 = new room();
    strcpy(r3->description, "You're in Sector 3 of the maze.");
    room* r4 = new room();
    strcpy(r4->description, "You're in Sector 4 of the maze.");
    room* r5 = new room();
    strcpy(r5->description, "You're in Sector 5 of the maze.");
    room* r6 = new room();
    strcpy(r6->description, "You're in Sector 6 of the maze.");
    room* r7 = new room();
    strcpy(r7->description, "You're in Sector 7 of the maze.");
    room* r8 = new room();
    strcpy(r8->description, "You're in Sector 8 of the maze.");
    room* r9 = new room();
    strcpy(r9->description, "You're in Sector 9 of the maze.");
    room* r10 = new room();
    strcpy(r10->description, "You're in Sector 10 of the maze.");
    room* r11 = new room();
    strcpy(r11->description, "You're in Sector 11 of the maze.");
    room* r12 = new room();
    strcpy(r12->description, "You're in Sector 12 of the maze.");
    room* r13 = new room();
    strcpy(r13->description, "You're in Sector 13 of the maze.");
    room* r14 = new room();
    strcpy(r14->description, "You're in Sector 14 of the maze.");
    room* r15 = new room();
    strcpy(r15->description, "You're in Sector 15 of the maze.");
    room* r16 = new room();
    strcpy(r16->description, "You're in Sector 16 of the maze.");
    room* r17 = new room();
    strcpy(r17->description, "You're in Sector 17 of the maze.");
    room* r18 = new room();
    strcpy(r18->description, "You're in Sector 18 of the maze.");
    room* r19 = new room();
    strcpy(r19->description, "You're in Sector 19 of the maze.");
    room* r20 = new room();
    strcpy(r20->description, "You're in Sector 20 of the maze.");
    room* r21 = new room();
    strcpy(r21->description, "You're in Sector 21 of the maze.");
    room* r22 = new room();
    strcpy(r22->description, "You're in Sector 22 of the maze.");
    room* r23 = new room();
    strcpy(r23->description, "You're in Sector 23 of the maze.");

    //set all exits
    r16->setExit(EXIT_RIGHT, r5);

    r20->setExit(EXIT_LEFT, r13);
    r20->addItem(level_36_ap);

    r21->setExit(EXIT_RIGHT, r15);
    r21->setExit(EXIT_DOWN, r22);

    r22->setExit(EXIT_UP, r21);
    r22->setExit(EXIT_DOWN, r23);
    r22->addItem(airi_fly_plane);

    r23->setExit(EXIT_UP, r22);

    r17->setExit(EXIT_DOWN, r5);
    r17->addItem(paid_crystals);

    r5->setExit(EXIT_UP, r17);
    r5->setExit(EXIT_DOWN, r15);
    r5->setExit(EXIT_LEFT, r16);
    r5->setExit(EXIT_RIGHT, r1);

    r15->setExit(EXIT_UP, r5);
    r15->setExit(EXIT_LEFT, r21);

    r7->setExit(EXIT_RIGHT, r2);

    r14->setExit(EXIT_RIGHT, r4);

    r8->setExit(EXIT_DOWN, r2);

    r2->setExit(EXIT_UP, r8);
    r2->setExit(EXIT_DOWN, r1);
    r2->setExit(EXIT_LEFT, r7);
    r2->setExit(EXIT_RIGHT, r6);

    r1->setExit(EXIT_UP, r2);
    r1->setExit(EXIT_DOWN, r4);
    r1->setExit(EXIT_LEFT, r5);
    r1->setExit(EXIT_RIGHT, r3);
    r1->addItem(gacha_ticket);

    r4->setExit(EXIT_UP, r1);
    r4->setExit(EXIT_DOWN, r13);
    r4->setExit(EXIT_LEFT, r14);
    r4->setExit(EXIT_RIGHT, r12);

    r13->setExit(EXIT_UP, r4);
    r13->setExit(EXIT_RIGHT, r20);

    r6->setExit(EXIT_DOWN, r18);
    r6->setExit(EXIT_LEFT, r2);

    r18->setExit(EXIT_UP, r6);

    r12->setExit(EXIT_LEFT, r4);

    r19->setExit(EXIT_RIGHT, r9);
    r19->addItem(kanade_ballin);
    
    r9->setExit(EXIT_LEFT, r19);
    r9->setExit(EXIT_DOWN, r3);

    r3->setExit(EXIT_UP, r9);
    r3->setExit(EXIT_DOWN, r11);
    r3->setExit(EXIT_LEFT, r1);
    r3->setExit(EXIT_RIGHT, r10);

    r11->setExit(EXIT_UP, r3);
    
    r10->setExit(EXIT_LEFT, r3);

    //current room & inv
    room* currentRoom = r1;
    vector<item*>* inventory = new vector<item*>();

    while(true) {
        //start
        cout << currentRoom->description << endl;
        cout << "Type \"help\" to view your available commands." << endl;
        cout << " > ";
        char cmd1[101]; // make it large to prevent bugs
        char cmd2[101];
        cin >> cmd1;
        cout << "Your command is: " << cmd1 << endl;

        //commands
        if(strcmp(cmd1, LOOK_COMMAND) == 0) {
            //look for room
            cout << "There are " << currentRoom->exits->size() << " exits in this room: " << endl;
            map<char *, room *>::iterator it = currentRoom->exits->begin(); // the exits of the room
            for (auto it = currentRoom->exits->begin(); it != currentRoom->exits->end(); it++)
            {
                cout << "   " << it->first;
            }
            cout << endl;
            if (currentRoom->items->size() > 0)
            {
                //item exits in this room
                cout << "There's also an item called \"" << currentRoom->items->at(0)->description << "\"..." << endl;
            }
        }
        //take item
        if(strcmp(cmd1, TAKE_COMMAND) == 0) {
            cout << "What would you like to take?" << endl;
            cout << " > ";
            cin >> cmd2;

            int idx = 0;
            vector<item*>::iterator it;
            bool found = false;
            for (it = currentRoom->items->begin(); it < currentRoom->items->end(); it++)
            {
                //attempt to find item and put in inv, erase from room
                if (strcmp((*it)->description, cmd2) == 0)
                {
                inventory->push_back(currentRoom->items->at(idx));
                currentRoom->items->erase(currentRoom->items->begin() + idx);
                cout << "You picked up the \"" << cmd2 << "\" that was in the room." << endl;
                cout << "Type \"inventory\" to view your inventory at any time." << endl;
                found = true;
                break;
                }
                idx++;
            }
            if (!found) //item does not exist (or in the room)
            {
                cout << "I couldn't find that item anywhere..." << endl;
            }
        }
        //drop item
        if(strcmp(cmd1, DROP_COMMAND) == 0) {
            cout << "What would you like to drop?" << endl;
            cout << " > ";
            cin >> cmd2;

            int idx = 0;
            vector<item*>::iterator it;
            for (it = inventory->begin(); it < inventory->end(); it++)
            {
                if (strcmp((*it)->description, cmd2) == 0)
                {
                    //same thing as take except the opposite, attempt to find item and put in room, erase from inv.
                    currentRoom->items->push_back(inventory->at(idx));
                    inventory->erase(inventory->begin() + idx);
                    cout << "You dropped the \"" << cmd2 << "\" into the room." << endl;
                    cout << "Type \"inventory\" to view your inventory at any time." << endl;
                }
                idx++;
            }
        }

        //direction
        if(strcmp(cmd1, GO_COMMAND) == 0) {
            cout << "What direction would you like to go? (";
            int count = 0;
            map<char *, room *>::iterator it1 = currentRoom->exits->begin();
            for (auto it1 = currentRoom->exits->begin(); it1 != currentRoom->exits->end(); it1++)
            {
                //prints out the exits for the room
                if(count == currentRoom->exits->size()) {
                    cout << it1->first << ") > ";
                } else {
                    cout << it1->first << "/";
                }
                count++;
            }
            cout << ") > ";
            cin >> cmd2;

            bool roomExists = false;
            map<char *, room *>::iterator it2 = currentRoom->exits->begin();
            for (auto it2 = currentRoom->exits->begin(); it2 != currentRoom->exits->end(); it2++)
            {
                if (strcmp(it2->first, cmd2) == 0) {
                    roomExists = true;
                    currentRoom = it2->second;
                    //if at ending room (room/sector 23)
                    if (strcmp(currentRoom->description, r23->description) == 0) { // The player is in the "winning" room
                        //win condition is to have all 5 items
                        if(inventory->size() != 5) {
                            cout << "Collect all 5 items to escape the maze! (You need " << (5 - inventory->size()) << " more)" << endl;
                            //push player back to room/sector 22
                            currentRoom = r22;
                            break;
                        } else {
                            //good job (?)
                            cout << "You successfully tiered and got rank #1 in the event!" << endl;
                            cout << "Thanks for playing." << endl;
                            return 0;
                        }
                    }
                    else {
                        cout << "You moved rooms." << endl << currentRoom->description << endl;
                        break;
                    }
                }
            }
            if (!roomExists)
            {
                //room does not exist, or rather, an exit
                cout << "There isn't an exit there!" << endl;
            }
        }
        //check inv
        if(strcmp(cmd1, INVENTORY_COMMAND) == 0) {
            if(inventory->size() == 0) {
                cout << "Your inventory is empty!" << endl;
            } else {
                //print out inv contents
                cout << "You have the following items:" << endl;
                vector<item*>::iterator it;
                for(it = inventory->begin(); it < inventory->end(); it++) {
                    cout << "   " << (*it)->description;
                }
                cout << endl;
            }
        }
        //help stuff
        if(strcmp(cmd1, HELP_COMMAND) == 0) {
            cout << "Project Sekai Grind - Command Help" << endl;
            cout << "Your available commands are:" << endl;
            cout << "   look - Look around a room for possible exits and items." << endl;
            cout << "   take - Take items from a room." << endl;
            cout << "   drop - Drop items from your inventory into the room that you're cuurrently in." << endl;
            cout << "   go - Move around the map by going from room to room." << endl;
            cout << "   inv - Check your inventory." << endl;
            cout << "   help - Display this message." << endl;
            cout << "   quit - Quit the game." << endl;
        }
        //quit command
        if(strcmp(cmd1, QUIT_COMMAND) == 0) {
            cout << "Thank you so much for playing!" << endl;
            return 0;
        }
    }

    
    return 0;
}
