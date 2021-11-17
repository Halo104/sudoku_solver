#include "sudoku.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>


using namespace std;

//long ATTEMPTS = 0;
//char MAXROWPOS = 'A';

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!" << '\n';
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+" << '\n';
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */
/*NEW FUNCTION - For checking if the board has been completely filled*/
/*Checks two conditions, it is NOT filled if the board contains a '.' or contains anything that's not between 1 and 9 */
bool is_complete(const char board[9][9]){
  for(int r = 0; r<9; r++){
    for(int c = 0; c<9; c++){
      if(board[r][c] == '.'){
	return false;
      }else if(!(board[r][c]>='1' && board[r][c]<='9')){
	return false;
      }
    }
  }
  return true;
}

//**Helper functions for make_move
bool isLengthTwo (const char* position){
  int lengthCount = 0;
  while(position[lengthCount]!= '\0'){
    lengthCount++;    
  }
  return lengthCount == 2;
}

bool boundCheck(const char inputChar, const char lowerValue, const char upperValue){
  if(inputChar > upperValue || inputChar < lowerValue){
    return false;
  }else{
    return true;
  }
}

bool existsInRow(const char digit, const char board[9][9], const int rowPos){
  for(int c = 0; c<9; c++){
    if(board[rowPos][c] == digit){
      return true;
    }
  }
  return false;
}

bool existsInColumn(const char digit, const char board[9][9], const int colPos){
  for(int r = 0; r<9; r++){
    if(board[r][colPos] == digit){
      return true;
    }
  }
  return false;
}

bool existsInBox(const int rowPos, const int colPos, const char digit, const char board[9][9]){
  int rowValue = 0;
  int colValue = 0;

  if(0<=rowPos && rowPos <=2){
    rowValue = 0;
  }else if(3<=rowPos && rowPos <=5){
    rowValue = 1;
  }else if(6<=rowPos && rowPos <=8){
    rowValue = 2;
  }else{
    cout << "Error: Not a valid row" << endl;
  }
  if(0<=colPos && colPos <=2){
    colValue = 0;
  }else if(3<=colPos && colPos <=5){
    colValue = 1;
  }else if(6<=colPos && colPos <=8){
    colValue = 2;
  }else{
    cout << "Error: Not a valid column" << endl;
  }
  
  for(int r = rowValue*3; r<(rowValue*3)+3; r++){
    for(int c = colValue*3; c<(colValue*3)+3; c++){
      if(board[r][c] == digit){
	return true;
      }
    }
  }
  return false;
}

/*NEW FUNCTION - For adding a new move to the board, while checking if the move is valid*/
bool make_move(const char* position, const char digit, char board[9][9]){
  //POSITION CHECKS
  if(position == nullptr){
    cerr << "\nError: Position input is a NULLPTR\n" << endl;
    return false;
  }
  
  /*Checking position contains only 2 values*/
  if(!isLengthTwo(position)){
    cerr << "\nError: Position input does not have 2 values\n" << endl;
    return false;
  }

  /*checking first character is between A and I*/
  if(!boundCheck(position[0], 'A', 'I')){
    cerr << "\nError: Input position character is not between A and I\n" << endl;
    return false;
  }
  /*checking second character is a digit beteen 1 to 9*/
  if(!boundCheck(position[1],'1','9')){
    cerr << "\nError: Input position value is not between 1 and 9, it is: " << position[1] <<  endl;
    return false;
  }

  /*Converting the input position values into integer values of row and column, can be used for the board indexs*/
  int rowPos = position[0] - 'A';
  int colPos = position[1] - '1';
  
  //DIGIT CHECKS
  /*check if there is already a digit, only display warning, but let it continue*/
  if(board[rowPos][colPos] < '9' && board[rowPos][colPos] > '0'){
    //cerr << "\n Warning: Input position already has a value\n" << endl;
  }

  //*checks that the digit entered is valid and between 1 to 9
  if(!boundCheck(digit,'1','9')){
    cerr << "\nError: Input digit is not between 1 and 9\n" << endl;
    return false;
  }
  
  /*check if the exact same digit is being added to what is already there, and if it is, not letting it continue*/
  if(board[rowPos][colPos] == digit){
    return false;
  }
  
  if(existsInRow(digit, board, rowPos)){
    //cerr << "\nError: Digit already exist in the row\n" << endl;
    return false;
  }

  if(existsInColumn(digit, board, colPos)){
    //cerr <<"\nError: Digit already exist in the column\n" << endl;
    return false;
  }

  if(existsInBox(rowPos, colPos, digit, board)){
    //cerr << "\nError: Digit already exist in the box\n" << endl;
    return false;
  }

  //WRITE VALUE
  board[rowPos][colPos] = digit;
  return true;
}

/*NEW FUNCTION - for saving the board to a new file*/
bool save_board(const char* filename, char board[9][9]){
  if(filename == nullptr){
    cerr << "\nError: filename pointer is NULLPTR\n" << endl;
    return false;                //As the filename is a null pointer and not a valid filename
  }
  ofstream file;
  file.open(filename);

  if(file.is_open()){
    for(int r = 0; r < 9; r++){
      for(int c = 0; c < 9; c++){
	assert(board[r][c] == '.' || isdigit(board[r][c])); //Same as the one made for loading the file, ensuring the values saved for the board is valid
	file << board[r][c];
      }
      file << "\n";
    }
  }else{
    return false;
  }
  file.close();

  //Only returning true if the values in the for loop are able to reach the end
  return true;
}

/*NEW FUNCTION - For solving the sudoku board*/
bool solve_board(char board[9][9]){
  char pos[] = "A1";                  //Provides starting position for solving the board
  bool returnValue = false;           //Using a returnValue instead of returning straight away, to allow the number of attempts taken and row reached to be printed
  //ATTEMPTS = 0; //Used for debugging
  //MAXROWPOS = 'A';  //Used for debugging
  
  returnValue = stepSolver(board, pos);
  //cout << "Attempts taken: " << ATTEMPTS << ", max Row Position: " << MAXROWPOS << endl;
  return returnValue;
}


bool stepSolver(char board[9][9], char* pos){
  if(pos == nullptr){
    cerr << "\nError: position in stepSolver is NULLPTR\n" << endl;
    return false;
  }
  char nextPos[] = "A1";

  //**Calculating the next position along and doesnt let it increment if it is at the end,
  //**and also check if the sudoku puzzel is completed
  if(is_complete(board) == true){
    return true;
  }else if(pos[1] == '9'){
    nextPos[0] = pos[0] + 1;
    nextPos[1] = '1';
  }else{
    nextPos[0] = pos[0];
    nextPos[1] = pos[1] + 1;
  }
  /*if(nextPos[0] > MAXROWPOS){
    MAXROWPOS = pos[0];
  }*/

  //**Checks that the next value isn't a default value, if it is a default value, then it moves onto the next value
  while(board[(nextPos[0]-65)][(nextPos[1]-49)] != '.'){
   if(nextPos[1] == '9'){
     nextPos[0] = nextPos[0] + 1;
     nextPos[1] = '1';
   }else{
     nextPos[0] = nextPos[0];
     nextPos[1] = nextPos[1] + 1;
   } 
  }
  
  //**Checks that the first value isn't a default value, if it is, it set the next location which is empty
  if(pos[0] == 'A' && pos[1] == '1' && board[(pos[0]-65)][(pos[1]-49)] != '.'){
    // cout << "First value default woohoo, original pos: " << pos << ", nextPos: " << nextPos << endl;
    strcpy(pos,nextPos);
    if(pos[1] == '9'){
      nextPos[0] = pos[0] + 1;
      nextPos[1] = '1';
    }else{
      nextPos[0] = pos[0];
      nextPos[1] = pos[1] + 1;
    }
  }
  
  //Attempting to write values starting from 0 to 9 to the current position
  for(int value = 0; value < 9; value++){
    char charValue = static_cast<char>(value+49);
    if(make_move(pos, charValue, board)){
      //**If the current position has an accepted value, then try to solve for next position, using recurssion, for calling stepSolver again
      //**The solver will attempt keep going forward with the earliest value that is valid
      bool completed = stepSolver(board, nextPos);
      if(completed)
	return true;
    }
  }
  //ATTEMPTS++;  //Used for debugging
  //cout << "no write, pos: " << pos << "no write attempts: " << attempts << endl;
  
  board[(pos[0]-65)][(pos[1]-49)] = '.';  //**Clearing the current position, so it doesnt affect the make_move conditions

  //**The function will return false, when all 9 values attempted to enter is invalid, and will cause the recursion function to unwind,
  //**until the point where a valid number can be entered and attempt to keep going along that path until it reaches another dead end.
  return false;
}
