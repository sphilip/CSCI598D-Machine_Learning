#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILD_NODES		9

#define EMPTY		0
#define X_PLAYER	1
#define O_PLAYER	2

#define MAX_INFINITY	1
#define DRAW		0
#define MIN_INFINITY	-1

#define MAX_TESTS	8

typedef struct {
  unsigned char test[3];
} test_t_m;

 const test_t_m mini_tests[MAX_TESTS]={
  {{ 8, 7, 6 }}, {{ 5, 4, 3 }},
  {{ 2, 1, 0 }}, {{ 8, 5, 2 }},
  {{ 7, 4, 1 }}, {{ 6, 3, 0 }},
  {{ 6, 4, 2 }}, {{ 8, 4, 0 }} };

class minimax
{
  public:
    int boards_checked;
    int computer_move;
    int moves;
    int this_player;
    int other_player;

    minimax();
    minimax(int player_char);
    void reset();

    int getCell( int cell, unsigned int board );
    void putCell( int player, int cell, unsigned int *board );
    char convert( int contents );
    int checkPlayerWin( int player, unsigned int cur_board );

    short evaluateHumanMove( unsigned int board, int depth );
    short evaluateComputerMove( unsigned int board, int depth );
    void getComputerMove( unsigned int *board );
};


minimax::minimax()
{
  moves = 0;
  this_player = 0;
  other_player = 0;
}

minimax::minimax(int player_char)
{
  moves = 0;
  this_player = player_char;
  other_player = (player_char % 2) + 1;
}

void minimax::reset()
{
  moves = 0;
  boards_checked = 0;
  computer_move = 0;
}

int minimax::checkPlayerWin( int player, unsigned int cur_board )
{
  int i;

  for (i = 0 ; i < MAX_TESTS ; i++)
  {
    if ((getCell(mini_tests[i].test[0], cur_board) == player) && (getCell(mini_tests[i].test[1], cur_board) == player) && (getCell(mini_tests[i].test[2], cur_board) == player))
      return 1;
  }

  return 0;
}

short minimax::evaluateHumanMove( unsigned int board, int depth )
{
  int i, value;
  unsigned int new_board;
  short min = MAX_INFINITY+1;

//   short evaluateComputerMove( unsigned int, int );

  boards_checked++;

  /* The computer (max) just made a move, so we evaluate that move here */
  if (checkPlayerWin(O_PLAYER, board))
    return MAX_INFINITY;

  for (i = 0 ; i < MAX_CHILD_NODES ; i++) {

    if (getCell(i, board) == EMPTY) {

      new_board = board;
      //       putCell( X_PLAYER, i, &new_board );
      putCell( other_player, i, &new_board );

      value = evaluateComputerMove( new_board, depth+1 );

      if (value < min) {
	min = value;
      }

    }

  }

  /* No move is possible -- draw */
  if (min == MAX_INFINITY+1) {
    return DRAW;
  }

  return min;
}

short minimax::evaluateComputerMove( unsigned int board, int depth )
{
  int i, value;
  unsigned int new_board;
  short max = MIN_INFINITY-1;

  boards_checked++;

  /* The human (min) just made a move, so we evaluate that move here */
  //   if (checkPlayerWin(X_PLAYER, board)) return MIN_INFINITY;
  if (checkPlayerWin(other_player, board))
    return MIN_INFINITY;

  for (i = 0 ; i < MAX_CHILD_NODES ; i++) {

    if (getCell(i, board) == EMPTY) {

      new_board = board;
      //       putCell( O_PLAYER, i, &new_board );
      putCell( this_player, i, &new_board );
      value = evaluateHumanMove( new_board, depth+1 );

      if (value > max) {
	max = value;
	if (depth == 0) computer_move = i;
      }

    }

  }

  /* No move is possible -- draw */
  if (max == MIN_INFINITY-1) {
    return DRAW;
  }

  return max;
}


void minimax::getComputerMove( unsigned int *board )
{

  boards_checked = 0;

  evaluateComputerMove( *board, 0 );

//   printf("move is %d (%d boards checked)\n", computer_move, boards_checked);

  //   putCell( O_PLAYER, computer_move, board );
  putCell( this_player, computer_move, board );
  moves++;

  return;
}

int minimax::getCell( int cell, unsigned int board )
{
  return ((board >> (cell*2)) & 0x3);
}

void minimax::putCell( int player, int cell, unsigned int *board )
{
  cell = *board |= (player << (cell*2));
  return;
}


char minimax::convert( int contents )
{
  if      (contents == X_PLAYER) return 'X';
  else if (contents == O_PLAYER) return 'O';

  return ' ';
}
