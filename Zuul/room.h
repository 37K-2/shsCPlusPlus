#ifndef ROOM_H
#define ROOM_H

#include <map>
#include <vector>
#include "item.h"

using namespace std;

class room{
 public:
  room();
  vector<item*>* items;
  map<char*, room*>* exits;
  char* description;
  
  void addItem(item* it);
  void setExit(char* direction, room* rm);
};

#endif // ROOM_H