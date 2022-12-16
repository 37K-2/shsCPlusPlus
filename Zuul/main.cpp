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
const char INVENTORY_COMMAND[] = "inventory";
const char HELP_COMMAND[] = "help";
const char QUIT_COMMAND[] = "quit";

int main() {
    // gacha ticket - added
    item* gacha_ticket = new item();
    strcpy(gacha_ticket->description, "gacha-ticket");
    // airi fly plane - added
    item* airi_fly_plane = new item();
    strcpy(airi_fly_plane->description, "airi-fly-plane");
    // kanade ballin - added
    item* kanade_ballin = new item();
    strcpy(kanade_ballin->description, "kanade-ballin");
    // paid crystals - added
    item* paid_crystals = new item();
    strcpy(paid_crystals->description, "crystals-g");
    // level 36 ap - added
    item* level_36_ap = new item();
    strcpy(level_36_ap->description, "level-36-ap");

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

    r16->setExit(EXIT_RIGHT, r5);

    r20->setExit(EXIT_DOWN, r22);
    r20->setExit(EXIT_RIGHT, r15);
    r20->addItem(level_36_ap);

    r22->setExit(EXIT_UP, r20);
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
    r15->setExit(EXIT_LEFT, r20);

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

    room* currentRoom = r1;
    vector<item*>* inventory = new vector<item*>();

    while(true) {
        cout << currentRoom->description << endl;
        cout << "Type \"help\" to view your available commands." << endl;
        cout << " > ";
        char cmd1[101]; // make it large to prevent bugs
        cin >> cmd1;
        cout << "Your command is: " << cmd1 << endl;
    }


    return 0;
}