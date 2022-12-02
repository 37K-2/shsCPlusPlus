#include "parent.h"
#ifndef MOVIE_MOVIE
#define MOVIE_MOVIE
class movie : public parent{
 public:
  movie();
  virtual ~movie();

  void setDirector(char inputDirector[101]);
  void setDuration(int inputDuration);
  void setRating(float inputRating);
  void print();
 protected:
  char* director;
  int duration;
  float rating;
};
#endif
