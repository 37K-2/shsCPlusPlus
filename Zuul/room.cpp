#include <cstring>
#include <vector>
#include <map>
#include "room.h"
#include "item.h"

room::room(){
  items = new vector<item *>();
  exits = new map<char *, room *>();
  description = new char[251];
}

void room::addItem(item* it){
  items->push_back(it);
}

void room::setExit(char* direction, room* rm){
  if(exits->size()==0){
    exits->insert({direction, rm});
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


