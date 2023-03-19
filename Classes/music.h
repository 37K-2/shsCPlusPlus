#include "parent.h"
#ifndef MUSIC_MUSIC
#define MUSIC_MUSIC

class music : public parent {
 public:
  music();
  virtual ~music();

  void setArtist(char inputArtist[101]);
  void setDuration(float inputDuration);
  void setPublisher(char inputPublisher[101]);
  void print();
 protected:
  char* artist;
  float duration;
  char* publisher;
};

#endif
