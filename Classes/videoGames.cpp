#include <cstring>
#include <iostream>
#include "videoGames.h"
using namespace std;

videoGame::videoGame(){
  title = new char[101];
  year = 1950;
  publisher = new char[101];
  rating = 0.0;
}

videoGame::~videoGame(){
  delete title;
  delete publisher;
}

void videoGame::setPublisher(char inputPub[101]){
  strcpy(publisher, inputPub);
}
void videoGame::setRating(float inputRating){
  rating = inputRating;
}
void videoGame::print(){
  cout << "Video Game:\nTitle: " << title << "\nPublisher: " << publisher << "\nYear Published: " << year << "\nRating: " << rating << endl;
}
