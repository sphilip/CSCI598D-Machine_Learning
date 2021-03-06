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

int boards_checked;


int getCell( int cell, unsigned int board )
{
  return ((board >> (cell*2)) & 0x3);
}

void putCell( int player, int cell, unsigned int *board )
{
  cell = 
  *board |= (player << (cell*2));
  return;
}
  

char convert( int contents )
{
  if      (contents == X_PLAYER) return 'X';
  else if (contents == O_PLAYER) return 'O';

  return ' ';
}


void emitBoard( unsigned int board )
{
  /* Emit the current board */
  printf("\n");
  printf(" %c | %c | %c \n",
          convert(getCell(8,board)),
          convert(getCell(7,board)),
          convert(getCell(6,board)) );
  printf("------------\n");
  printf(" %c | %c | %c \n",
          convert(getCell(5,board)),
          convert(getCell(4,board)),
          convert(getCell(3,board)) );
  printf("------------\n");
  printf(" %c | %c | %c \n\n",
          convert(getCell(2,board)),
          convert(getCell(1,board)),
          convert(getCell(0,board)) );

  return;
}


void getHumanMove( unsigned int *board )
{
  int selection;

  /* Get human move */
  while (1) {
    printf("Select a move (8=upper-left, 0=lower-right): ");
    scanf("%d", &selection);
    printf("\n");
    if (selection < MAX_CHILD_NODES) {
      if (getCell(selection, *board) == EMPTY) break;
      printf("cell taken -- choose again.\n");
    }
  }

  putCell( X_PLAYER, selection, board );

  return;
}


#define MAX_TESTS	8

typedef struct {
  unsigned char test[3];
} test_t;

const test_t tests[MAX_TESTS]={
          {{ 8, 7, 6 }}, {{ 5, 4, 3 }},
          {{ 2, 1, 0 }}, {{ 8, 5, 2 }},
          {{ 7, 4, 1 }}, {{ 6, 3, 0 }},
          {{ 6, 4, 2 }}, {{ 8, 4, 0 }} };


int checkPlayerWin( int player, unsigned int cur_board )
{
  int i;

  for (i = 0 ; i < MAX_TESTS ; i++) {

    if ((getCell(tests[i].test[0], cur_board) == player) && 
        (getCell(tests[i].test[1], cur_board) == player) &&
        (getCell(tests[i].test[2], cur_board) == player)) return 1;

  }

  return 0;
}


short evaluateHumanMove( unsigned int board, int depth,
                          int alpha, int beta )
{
  int i, value;
  unsigned int new_board;
  short min = MAX_INFINITY+1;

  short evaluateComputerMove( unsigned int, int, int, int );

  boards_checked++;

  /* The computer (max) just made a move, so we evaluate that move here */
  if (checkPlayerWin(O_PLAYER, board)) return MAX_INFINITY;

  for (i = 0 ; i < MAX_CHILD_NODES ; i++) {

    if (getCell(i, board) == EMPTY) {

      new_board = board;
      putCell( X_PLAYER, i, &new_board );

      value = evaluateComputerMove( new_board, depth+1, alpha, beta );

      if (value < min) {
        min = value;
      }

      if (value < beta) beta = value;

      /* Prune this subtree by not checking any further successors */
      if (alpha >= beta) return beta;

    }

  }

  /* No move is possible -- draw */
  if (min == MAX_INFINITY+1) {
    return DRAW;
  }

  return min;
}


int computer_move;
int moves = 0;

short evaluateComputerMove( unsigned int board, int depth,
                             int alpha, int beta )
{
  int i, value;
  unsigned int new_board;
  short max = MIN_INFINITY-1;

  boards_checked++;

  /* The human (min) just made a move, so we evaluate that move here */
  if (checkPlayerWin(X_PLAYER, board)) return MIN_INFINITY;

  for (i = 0 ; i < MAX_CHILD_NODES ; i++) {

    if (getCell(i, board) == EMPTY) {

      new_board = board;
      putCell( O_PLAYER, i, &new_board );

      value = evaluateHumanMove( new_board, depth+1, alpha, beta );

      if (value > max) {
        max = value;
        if (depth == 0) computer_move = i;
      }

      if (value > alpha) alpha = value;

      /* Prune this subtree by not checking any further successors */
      if (alpha >= beta) return alpha;

    }

  }

  /* No move is possible -- draw */
  if (max == MIN_INFINITY-1) {
    return DRAW;
  }

  return max;
}


void getComputerMove( unsigned int *board )
{
  boards_checked = 0;

  evaluateComputerMove( *board, 0, MIN_INFINITY-1, MAX_INFINITY+1 );

  printf("move is %d (boards checked %d)\n", computer_move, boards_checked);

  putCell( O_PLAYER, computer_move, board );
  moves++;

  return;
}


int main()
{
  unsigned int cur_board = 0;
  int won = 0;

  while (!won) {

    emitBoard( cur_board );

    getHumanMove( &cur_board );

    won = checkPlayerWin( X_PLAYER, cur_board );
    moves++;

    if ((!won) && (moves == MAX_CHILD_NODES)) {
      printf("draw\n");
      break;
    }

    if (!won) {

      /* Build the game tree */
      getComputerMove( &cur_board );

      won = checkPlayerWin( O_PLAYER, cur_board );

      if (won) {
        printf("\nYou lose!\n");
      }

    } else {

      printf("\nYou win!\n");

    }

  }

  emitBoard( cur_board );

  return 0;
}


