// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
//
// #include "alphabeta.h"
// #include "minimax.h"
//
// #define MAX_CHILD_NODES		9
//
// #define EMPTY		0
// #define X_PLAYER	1
// #define O_PLAYER	2
//
// #define MAX_INFINITY	1
// #define DRAW		0
// #define MIN_INFINITY	-1

#include "alphabeta.h"
#include "minimax.h"
#include "linear.h"

using namespace std;

typedef struct {
  unsigned char test[3];
} test_t;

const test_t tests[MAX_TESTS]=
{
  {{ 8, 7, 6 }}, 
  {{ 5, 4, 3 }},
  {{ 2, 1, 0 }}, 
  
  {{ 8, 5, 2 }},
  {{ 7, 4, 1 }}, 
  {{ 6, 3, 0 }},
  
  {{ 6, 4, 2 }}, 
  {{ 8, 4, 0 }} 
};


int getCell( int cell, unsigned int board )
{
  return ((board >> (cell*2)) & 0x3);
}

void putCell( int player, int cell, unsigned int *board )
{
  cell = *board |= (player << (cell*2));
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

    if ((getCell(tests[i].test[0], cur_board) == player) && (getCell(tests[i].test[1], cur_board) == player) && (getCell(tests[i].test[2], cur_board) == player)) 
      return 1;

  }

  return 0;
}

int main()
{

//   alphabeta player1(1,20,8,56,35),player2(2,16,34,29,2);
//   minimax player1(1), player2(2);
linear player1(1,8,6,10,7),player2(2,1,1,1,1);
// alphabeta player1(1);
// minimax player1(1);
// linear player2(2,1,1,1,1);

int num_games = 1000;
  for (int i=0; i< num_games; i++)
  {
    unsigned int cur_board = 0;
    int won = false;

    while (!won)
    {
//       emitBoard(cur_board);

      player1.getComputerMove (&cur_board);

      won = checkPlayerWin(X_PLAYER, cur_board);
      player1.moves++;
//       player2.moves++;

      if ((!won) && ((player1.moves == MAX_CHILD_NODES) || (player2.moves == MAX_CHILD_NODES)))
      {
	printf("0\n");
	break;
      }

      if (!won) {

	/* Build the game tree */
	player2.getComputerMove( &cur_board );
	
// 	printf("player 1\t%3.2f\t%3.2f\t%3.2f\t%3.2f\n",player1.w1, player1.w2, player1.w3, player1.w4);
// 	printf("player 2\t%3.2f\t%3.2f\t%3.2f\t%3.2f\n",player2.w1, player2.w2, player2.w3, player2.w4);
	won = checkPlayerWin( O_PLAYER, cur_board );

	if (won)
	  printf("2\n");
      } 
      
      else printf("1\n");
    }
    
    player1.reset();
    player2.reset();
//     emitBoard(cur_board);
    
    
  }
  
  printf("%d",num_games);
  return 0;
}