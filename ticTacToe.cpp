/* Tic Tac Toe (C++ Edition) By: Aaron Guo, Period 6
 *
 * The code starts of with Player X starting. There is a board where you input the slot. Then, goes to Player O. Continues to rotate until someone wins (or a tie). When someone wins, it tells who won and how many points total currently for each of the respective players. It asks to play again, if pressed "y" then clears board and plays again. Else if plays "n", then it stops.
 *
 */

#include <iostream>
#include <cstring>
using namespace std;

//for functions below
void clearBoard(char board[3][3]);
void printBoard(char board[3][3]);
bool checkWin(char player, char board[3][3]);
bool checkTie(char board[3][3]);

int main(){
  //initialize variables
  char playerTurn = 'x';
  char board[3][3];
  bool stillPlaying = true;

  //point counter
  int xPoints = 0;
  int oPoints = 0;
  
  while(stillPlaying == true){
    //clear and print board, player x starts
    clearBoard(board);
    printBoard(board);
    playerTurn = 'x';

    //make sure no win nor tie
    while(checkWin('x', board) == false && checkWin('o', board) == false && checkTie(board) == false){
      //get input for row and columns to put in the board
      char inputRowAlpha = '_';
      int inputColumnInt = 0;
      cout << "It is " << playerTurn << "\'s turn!" << endl;
      cout << "Input Row: " << endl;
      cin >> inputRowAlpha;
      //check if a, b, or c
      while(inputRowAlpha < 'a' || inputRowAlpha > 'c'){
	cout << "Enter either a, b, or c for row!" << endl;
	cout << "Input Row: " << endl;
	cin >> inputRowAlpha;
      }
      cout << "Input Column: " << endl;
      cin >> inputColumnInt;
      //check if 1, 2, or 3
      while(inputColumnInt < 1 || inputColumnInt > 3){
	cout << "Enter either 1, 2, or 3 for column!" << endl;
	cout << "Input Column: " << endl;
	cin >> inputColumnInt;
      }

      //put in board
      if(board[inputRowAlpha-97][inputColumnInt-1] == '_'){
	//if blank space then put in board
	board[inputRowAlpha-97][inputColumnInt-1] = playerTurn;
	//switch players
	if(playerTurn == 'x')
	  playerTurn = 'o';
	else
	  playerTurn = 'x';
      }
      else
	//space is taken
	cout << "There is a piece there. Try another space." << endl;
      printBoard(board);
    }

    //check if someone won
    if(checkWin('x', board) == true){
      xPoints++;
      cout << "X Wins!" << endl;
    }
    else if(checkWin('o', board) == true){
      oPoints++;
      cout << "O Wins!" << endl;
    }
    else
      cout << "Tie!" << endl;

    //print out results
    cout << "X Wins: " << xPoints << endl;
    cout << "O Wins: " << oPoints << endl;
    cout << "Play Again? (y/n)" << endl;

    char playAgainInput = 'y';
    cin >> playAgainInput;
    if(playAgainInput == 'n'){
      stillPlaying = false;
      break;
    }
  }
  return 0;
}

//clear the board with underscores
void clearBoard(char board[3][3]){
  for(int x = 0; x < 3; x++){
    for(int y = 0; y < 3; y++){
      board[x][y] = '_';
    }
  }
}

//print the board in the format
void printBoard(char board[3][3]){
  cout << "  1 2 3" << endl;
  for(int x = 0; x < 3; x++){
    cout << char('a'+x) << ' ';
    for(int y = 0; y < 3; y++){
      cout << board[x][y] << ' ';
    }
    cout << endl;
  }
}

//check all conditions of win
bool checkWin(char player, char board[3][3]){
  if((board[0][0] == player && board[0][1] == player && board[0][2]==player)) //vertical left
    return true;
  if (board[0][0] == player && board[1][1] == player && board[2][2]==player) //diagonal to the bottom right & top left
    return true;
  if (board[0][0] == player && board [1][0] == player && board [2][0] ==player)  //horizontal top
    return true;
  if (board[1][0] == player && board[1][1] == player && board [1][2] == player)  //horizontal middle
    return true;
  if (board[2][0] == player && board[2][1] == player && board [2][2] == player)  //horizontal bottom
    return true;
  if (board[0][1] == player && board[1][1] == player && board[2][1] == player) //vertical middle
    return true;
  if (board[0][2] == player && board[1][2] == player && board[2][2] == player) //vertical right
    return true;
  if (board[0][2] == player && board [1][1] == player && board [2][0] == player) //vertical top right and bottom left
    return true;
  return false;
}

//check if it is a tie
bool checkTie(char board[3][3]){
  for (int row = 0; row < 3; row++){
    for(int column = 0; column < 3; column++){
      if(board[row][column] == '_')
	return false;
    }
  }
  return true;
}
		
