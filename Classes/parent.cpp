#include <cstring>
#include "parent.h"

parent::parent(){}
parent::~parent(){}
void parent::print(){}

char* parent::getTitle(){
  return title;
}
int parent::getYear(){
  return year;
}
void parent::setTitle(char inputTitle[101]){
  strcpy(title, inputTitle);
}
void parent::setYear(int inputYear){
  year = inputYear;
}
