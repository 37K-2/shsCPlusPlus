#include "parent.h"
#ifndef VIDEO_GAME
#define VIDEO_GAME

class videoGame : public parent {
 public:
  videoGame();
  virtual ~videoGame();

  void setPublisher(char inputPub[101]);
  void setRating(float inputRating);
  void print();
 protected:
  char* publisher;
  float rating;
};

#endif
  
