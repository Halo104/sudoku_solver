#include "sudoku.h"

#include <iostream>
#include <cstdio>

using namespace std;

int main(){
  
  char board[9][9];
  
  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============" << "\n\n";

  cout << "Calling load_board():" << '\n';
  load_board("easy.dat", board);

  cout << '\n' << "Displaying Sudoku board with display_board():" << '\n';
  display_board(board);
  cout << "Done!" << "\n\n";

  cout << "=================== Question 1 ===================" << "\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete." << "\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete." << "\n\n";

  load_board("invalidBoard1.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete." << "\n\n";

  
  cout << "=================== Question 2 ===================" << "\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Should NOT be OK, as K is not within bounds
  cout << "Putting '9' into K8 is ";
  if (!make_move("K8", '9', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Should NOT be OK, as 0 is not within position bounds
  cout << "Putting '3' into C0 is ";
  if (!make_move("C0", '3', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Should NOT be OK, as 99 is not within position bounds
  cout << "Putting '3' into C99 is ";
  if (!make_move("C99", '3', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Should NOT be OK, as just D is not within position bounds
  cout << "Putting '3' into D is ";
  if (!make_move("D", '3', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);
  
  // Should NOT be OK, as 0 value is not within bounds
  cout << "Putting '0' into B2 is ";
  if (!make_move("B2", '0', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Should NOT be OK, as @ is a valid value
  cout << "Putting '@' into D3 is ";
  if (!make_move("D3", '@', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  
  cout << "=================== Question 3 ===================" << "\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful." << '\n';
  } else {
    cout << "Save board failed." << '\n';
  }
  cout << '\n';
  
  cout << "=================== Question 4 ===================" << "\n\n";

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';
  
  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';
  
  // write more tests
  
  cout << "=================== Question 5 ===================" << "\n\n";

  load_board("mystery1.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  //Attempting to save the board after it has been solved
  if (save_board("mystery1-solved.dat", board)) {
    cout << "Save board to 'mystery1-solved.dat' successful." << '\n';
  } else {
    cout << "Save board failed." << '\n';
  }
  
  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  //Attempting to save the board after it has been solved
  if (save_board("mystery2-solved.dat", board)) {
    cout << "Save board to 'mystery2-solved.dat' successful." << '\n';
  } else {
    cout << "Save board failed." << '\n';
  }
  
  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';
  
  // write more tests
  load_board("own_veryDifficult.dat", board);
  if (solve_board(board)) {
    cout << "The 'own_veryDifficult' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  load_board("own_Hard.dat", board);
  if (solve_board(board)) {
    cout << "The 'own_Hard' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  load_board("own_startTest.dat", board);
  if (solve_board(board)) {
    cout << "The 'own_startTest' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';

  load_board("own_startTest1.dat", board);
  if (solve_board(board)) {
    cout << "The 'own_startTest1' board has a solution:" << '\n';
    display_board(board);
  } else {
    cout << "A solution cannot be found." << '\n';
  }
  cout << '\n';
  
  return 0;
}
