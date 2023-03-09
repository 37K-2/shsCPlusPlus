#ifndef PARENT_MEDIA
#define PARENT_MEDIA

class parent {
 public:
  parent();
  virtual ~parent();
  virtual void print();
  
  void setTitle(char inputTitle[101]);
  void setYear(int inputYear);
  int getYear();
  char* getTitle();
 protected:
  char* title;
  int year; 
  
};

#endif
