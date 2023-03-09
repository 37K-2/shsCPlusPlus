#include <cstring>
#include <iostream>
#include "music.h"
using namespace std;

music::music(){
  title = new char[101];
  year = 1950;
  artist = new char[101];
  duration = 0;
  publisher = new char[101];
}

music::~music(){
  delete title;
  delete artist;
  delete publisher;
}

void music::setArtist(char inputArtist[101]){
  strcpy(artist, inputArtist);
}
void music::setDuration(float inputDuration){
  duration = inputDuration;
}
void music::setPublisher(char inputPublisher[101]){
  strcpy(publisher, inputPublisher);
}
void music::print(){
  cout << "Song: " << title << "\nArtist: " << artist << "\nDuration: " << duration << "\nPublisher: " << publisher << "\nYear: " << year << endl;
}
