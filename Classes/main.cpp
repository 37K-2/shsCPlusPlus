// Classes By: Aaron Guo, C++ Period 6
// Basically, it adds, searches, and deletes media (video games, music, movie) with its respective pieces of information

#include <iostream> //required packages
#include <vector>
#include <cstring>
#include <ctype.h>
#include <iomanip>

#include "parent.h" //classes
#include "videoGames.h"
#include "music.h"
#include "movie.h"

using namespace std;

//cmds
const char addCMD[] = "ADD";
const char searchCMD[] = "SEARCH";
const char deleteCMD[] = "DELETE";
const char quitCMD[] = "QUIT";

//media types
const char typeVideoGame[] = "VIDEOGAME";
const char typeMusic[] = "MUSIC";
const char typeMovie[] = "MOVIE";

//filters
const char searchTitle[] = "TITLE";
const char searchYear[] = "YEAR";

//other
const char yesDelete[] = "YES";
const char noDelete[] = "NO";

//method prototypes
void addMedia(vector<parent *> *mediaList);
void searchMedia(vector<parent *> *mediaList);
void deleteMedia(vector<parent *> *mediaList);

int main(){
  //vector with media pointers
  vector<parent *> mediaList;

  //round to nearest tenth for ratings
  cout << fixed << setprecision(1);

  //current cmd, longest command is 6 char long + null char
  char cmd[7];

  while(true){ //recieve commands until user wants to exit
    cout << "-> ";
    cin >> cmd;

    //the commands
    if(strcmp(cmd, addCMD) == 0)
      addMedia(&mediaList);
    if(strcmp(cmd, searchCMD) == 0)
      searchMedia(&mediaList);
    if(strcmp(cmd, deleteCMD) == 0)
      deleteMedia(&mediaList);
    if(strcmp(cmd, quitCMD) == 0){
      break;
    }
  }

  return 0;
}

//asks media objects and media type 


void addMedia(vector<parent *> *mediaList){
  char typIn[10];
  int type = -1; // 0 -> video game, 1 -> music, 2 -> movie

  do{ //checks if video game, music, or movie
    cout <<"What type of media do you want to add? Enter in \"VIDEOGAME\", \"MUSIC\", or \"MOVIE\": ";
    cin >> typIn;
    cin.ignore();
    
    if(strcmp(typIn, typeVideoGame) == 0) {
      type = 0; 
      break;
    } else if (strcmp(typIn, typeMusic) == 0) {
      type = 1;
      break;
    } else if (strcmp(typIn, typeMovie) == 0) {
      type = 2;
      break;
    }
  } while(true);

  if(type == 0) {
    videoGame* game = new videoGame();

    char title[101];
    cout << "Enter the game's title: ";
    cin.getline(title, 100, '\n');
    game->setTitle(title); // set video game title

    int year;
    cout << "Enter the game's year: ";
    cin >> year;
    cin.ignore();
    game->setYear(year); // set video game year

    char publisher[101];
    cout << "Enter the game's publisher: ";
    cin.getline(publisher, 100, '\n');
    game->setPublisher(publisher); // set video game publisher

    float rating;
    cout << "Enter the game's rating: ";
    cin >> rating;
    cin.ignore();
    game->setRating(rating); // set video game rating

    cout << endl;

    game->print(); //prints out the game

    mediaList->push_back(game); //puts in vector

    cout << endl << "Game added, there are " << mediaList->size() << " entries in the media list" << endl;
  } else if (type == 1) {
    music* ms = new music();

    char title[101];
    cout << "Enter the song's title: ";
    cin.getline(title, 1009, '\n');
    ms->setTitle(title); // set music title

    int year;
    cout << "Enter the song's year: ";
    cin >> year;
    cin.ignore(); // set music year
    ms->setYear(year);
    
    char artist[101];
    cout << "Enter the song's artist: ";
    cin.getline(artist, 100, '\n');
    ms->setArtist(artist); //set artist for music
    
    float duration;
    cout << "Enter the song's duration in minutes: ";
    cin >> duration;
    cin.ignore();
    ms->setDuration(duration); //set music duration

    char publisher[101];
    cout << "Enter the song's publisher: ";
    cin.getline(publisher, 100, '\n');
    ms->setPublisher(publisher); // set publisher for music

    cout << endl;

    ms->print(); //print out music

    mediaList->push_back(ms); //push into vector

    cout << endl << "Song added, there are " << mediaList->size() << " entries in the media list" << endl;
  } else if (type == 2) {
    movie* mv = new movie();

    char title[101];
    cout << "Enter the movie's title: ";
    cin.getline(title, 100, '\n');
    mv->setTitle(title); // set movie title

    int year;
    cout << "Enter the movie's year: ";
    cin >> year;
    cin.ignore();
    mv->setYear(year); //set movie year

    char director[101];
    cout << "Enter the movie's director: ";
    cin.getline(director, 100, '\n');
    mv->setDirector(director); // set movie director

    float duration;
    cout << "Enter the movie's duration in minutes: ";
    cin >> duration;
    cin.ignore();
    mv->setDuration(duration); //set movie duration

    float rating;
    cout << "Enter the movie's rating: ";
    cin >> rating;
    cin.ignore();
    mv->setRating(rating); //set movie rating

    cout << endl;

    mv->print(); //print

    mediaList->push_back(mv); // put into vector

    cout << endl << "Movie added, there are " << mediaList->size() << " entries in the media list" << endl;
  } else {
    cout << "An unknown error occurred." << endl;
  }
  
}

void searchMedia(vector<parent *> *mediaList) {
  char typeIn[10];
  int type = -1;

  do {
    cout << "Please tell how you'd like to search, either type \"TITLE\" or \"YEAR\": ";
    cin >> typeIn;
    cin.ignore(); // search, input title or year

    if(strcmp(typeIn, searchTitle) == 0) {
      type = 0;
      break;
    } else if(strcmp(typeIn, searchYear) == 0) {
      type = 1;
      break;
    }
  } while (true);

  if(type == 0) {
    cout << "What title are you searching for?: ";
    char ttlsearch[101]; //search via title
    cin.getline(ttlsearch, 100, '\n');
    cout << endl;

    int found = 0;

    for(vector<parent*>::iterator it = mediaList->begin(); it < mediaList->end(); it++) {
      if(strcmp((*it)->getTitle(), ttlsearch) == 0) {
	(*it)->print();
	found++; //go through until it find the one needed
      }
    }
    cout << endl << found << " entries are in the database with that title." << endl;
  } else if (type == 1) {
    cout << "What year are you searching for? ";
    int yrsearch; //search via year
    cin >> yrsearch;
    cin.ignore();
    cout << endl;

    int found = 0;

    for(vector<parent*>::iterator it = mediaList->begin(); it < mediaList->end(); it++) {
      if((*it)->getYear() == yrsearch) {
	(*it)->print();
	found++; // go through until find the one needed
      }
    }
    cout << endl << found << " entries are in the database with that year." << endl;
  } else {
    cout << "An unknown error occurred." << endl;
  }
}

void deleteMedia(vector<parent *> *mediaList) {
  char typeIn[10];
  int type = -1;

  do {
    cout << "Please tell how you'd like to search, either type \"TITLE\" or \"YEAR\": ";
    cin >> typeIn;
    cin.ignore(); //delete stuff, sets by looking for title or year

    if(strcmp(typeIn, searchTitle) == 0) {
      type = 0;
      break;
    } else if (strcmp(typeIn, searchYear) == 0) {
      type = 1;
      break;
    }
  } while (true);

  if(type == 0) {
    cout << "What title are you searching for?: ";
    char searchTitle[101]; //search for title
    cin.getline(searchTitle, 100, '\n');
    int index = 0;

    vector<parent *>::iterator it;
    for(it = mediaList->begin(); it < mediaList->end(); it++){
      if(strcmp((*it)->getTitle(), searchTitle)==0){
	cout << endl;
	(*it)->print(); //prints out title
	cout << "Do you want to delete this? Enter \"YES\" or \"NO\": ";
	char confirm[4];
	cin >> confirm;
	if(strcmp(confirm, yesDelete) == 0){ //confirms user to delete title
	  cout << "Confirmed Delete. Deleting..." << endl;
	  delete *it; //delete the index
	  mediaList->erase(mediaList->begin() + index);
	  cout << "Confirmed Fully Deleted." << endl;
	  break;
	}
      }
      index++;
    }
  } else if(type == 1) {
    cout << "What year are you searching for?: ";
    int searchYear; //search for year
    cin >> searchYear;
    cin.ignore();
    int index = 0;

    vector<parent *>::iterator it;
    for(it = mediaList->begin(); it < mediaList->end(); it++){
      if((*it)->getYear() == searchYear){
        cout << endl;
        (*it)->print(); //prints out year
        cout << "Do you want to delete this? Enter \"YES\" or \"NO\": ";
        char confirm[4];
        cin >> confirm;
        if(strcmp(confirm, yesDelete) == 0){
          cout << "Confirmed Delete. Deleting..." << endl;
          delete *it; //delete the index
          mediaList->erase(mediaList->begin() + index);
          cout << "Confirmed Fully Deleted." << endl;
          break;
        }
      }
      index++;
    }
  } else {
    cout << "An unknown error occurred." << endl;
  }
}
