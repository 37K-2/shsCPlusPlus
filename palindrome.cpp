/* Palindrome (C++ Version) by: Aaron Guo, Period 6
 *
 * Basically what this program does is that you input some charachters, and it tells if it is a palindrome or not. Max input is 80 charachters.
 *
 */
#include <iostream>
#include <cstring>
using namespace std;

int main(){
  cout << "Enter word: ";
  char palin[81]; // receives charachters
  char sortedPalin[81]; // put in after charachters are sorted
  bool palindrome = true; // assume charachters are a palindrome

  cin.getline(palin, 81); // input charachters into the array

  int counter = 0; // counter since no append function
  for(int x = 0; x < strlen(palin); x++){ // for len of palin
    if(isalpha(palin[x]) || isdigit(palin[x])){ // if is alphanumeric
       sortedPalin[counter] = tolower(palin[x]); // enter it into the new sorted array and make it lowercase
       counter++; // add to counter to move on to the next part of the array
    }
  }
  sortedPalin[counter] = palin[-1]; // add null charachter
      
  for(int x = 0; x < strlen(sortedPalin); x++){ // for everything in sortedpalin
    if (sortedPalin[x] != sortedPalin[strlen(sortedPalin)-1-x]){ // if character is not the one at the corresponding location when read from the back
      palindrome = false; // automatically not a palindrome since different characters
      break; // kill loop because no point since its not a palindrome
    }
  }

  //cout << palindrome;
  if(palindrome == true)
    cout << "Palindrome!"; // palindrome bool is true and therefore is a palindrome
  else
    cout << "Not a palindrome!"; // palindrome bool is false and therefore not a palindrome
  
  return 0;
}
