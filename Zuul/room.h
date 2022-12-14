#include <vector>
#include <map>
using namespace std

class room{
 public:
  room();
  vector<char*> items;
  map<char*, room*> exits;
  char name[251];
  
  void addItem(char* item);
  void setExit(char* direction, room* rm);
};
