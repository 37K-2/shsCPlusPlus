#include <cstring>
#include <iostream>
#include "movie.h"
using namespace std;

movie::movie(){
  title = new char[101];
  year = 1950;
  director = new char[101];
  duration = 0;
  rating = 0.0;
}
movie::~movie(){
  delete title;
  delete director;
}
void movie::setDirector(char inputDirector[101]){
  strcpy(director, inputDirector);
}
void movie::setDuration(int inputDuration){
  duration = inputDuration;
}
void movie::setRating(float inputRating){
  rating = inputRating;
}
void movie::print(){
  cout << "Movie: " << title << "\nYear: " << year << "\n Director: " << director << "\nDuration: " << duration << "\nRating: " << rating << endl;
}
