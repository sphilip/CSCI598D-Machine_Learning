#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alphabeta.h"

#define MAX_CHILD_NODES		9

#define EMPTY		0
#define X_PLAYER	1
#define O_PLAYER	2

#define MAX_INFINITY	1
#define DRAW		0
#define MIN_INFINITY	-1

using namespace std;

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

int main()
{
  unsigned int cur_board = 0;
  int won = false;

  alphabeta player1(1),player2(2);

  while (!won)
  {
    emitBoard(cur_board);

    player1.getComputerMove (&cur_board);

    won = checkPlayerWin(X_PLAYER, cur_board);
    player1.moves++;
    player2.moves++;

    if ((!won) && ((player1.moves == MAX_CHILD_NODES) || (player2.moves == MAX_CHILD_NODES)))
    {
      printf("draw\n");
      break;
    }

    if (!won) {

      /* Build the game tree */
      player2.getComputerMove( &cur_board );

      won = checkPlayerWin( O_PLAYER, cur_board );

      if (won) {
	printf("\nYou lose!\n");
      }

    } else {

      printf("\nYou win!\n");

    }

  }

  emitBoard(cur_board);
  return 0;
}