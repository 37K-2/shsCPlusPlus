/* Guessing Game code written by Aaron Guo
   C++ & Data Structures Period 6
   Finished 09/12/2022

   Basically, the code takes an input of a person who inputs a number. The program will tell if the number is higher or lower than the randomly generated number between 0-100. Once the number is guessed, the program will ask if you want to play again. If yes (y), then it repeats again with a different randomly generated number (hopefully), and if no (n) then it will end the program.

   Three Rules of C++:
   1. No global variables
   2. No strings (only cstrings/charachter arrys)
   3. Include <iostream> not stdio, which applied to programmers using C
   Note: Better to use a shell (like cygwin64) rather than a GUI (Visual Code Studio)
 */

#include <iostream> // cin, cout
#include <stdlib.h> // srand & rand
#include <time.h>   // time
using namespace std;

int main(){
  int guesses = 0; // guesses it takes for user to guess the number
  bool playing = true; // if person is playing
  srand(time(NULL)); // initializer for random (rand) function
  
  while(playing){ // while the person is playing
    int input = -1; // make the input default to -1 so that it does not conflict with the while loop
    int answer = rand()%101; // random number between 0-100
    while(input != answer){ // while number has not been guessed
      cout << "Enter guess: " << endl;
      cin >> input; // ask for input from user
      if (input > answer) // if input is bigger than the answer
	cout << "Too high!" << endl; // print too high
      else if (input < answer) // if input is smaller than the answer
	cout << "Too low!" << endl; // print too low
      else // otherwise if the input is the answer
	break; // then break and continue on to the next lines
      guesses++; // add 1 to guesses
    }
    cout << "Congrats! You guessed the number!" << endl; // give a congrats that you guessed the number i guess
    guesses++; // add 1 to guesses because did not add the last guess to the guess count due to break
    cout << "You took " << (guesses) << " guesses!" << endl; // print out how many guesses it took to guess the answer
    char playAgain = 'y'; // on default make the player play again :)))
    cout << "Do you want to play again? (y/n)" << endl; // ask if they want to play again
    cin >> playAgain; // input
    if (playAgain == 'n'){ // if play again is NO
      cout << "Thanks for playing!" << endl; // thanks for playing message
      playing = false; // break out of while loop by making it false
      break; // break everything to end the code
    }
    if (playAgain == 'y') // if play again is YES
      guesses = 0; // reset guess count to zero
  }
  return 0; // return lol
}
