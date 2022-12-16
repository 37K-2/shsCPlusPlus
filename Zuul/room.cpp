#include <cstring>
#include <vector>
#include <map>
#include "room.h"

parent::room(){
  items = new vector<char *>();
  exits = new map<char *, room *>();
  name = new char[251];
}

void addItem(char* item){
  items->push_back(item);
}

void setExit(char* direction, room* rm){
  if(exits->size()==0){
    exit->insert({direction, rm});
    return;
  }
  map<char*, room*>::iterator it = exits->begin();
  while(it!=exits->end()){
    if(strcmp(it->first, direction) == 0)
      return;
    else{
      exits->insert({direction, rm});
      return;
    }
  }
}


