#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILD_NODES		9

#define EMPTY		0
#define X_PLAYER	1
#define O_PLAYER	2

#define WIN	100
#define DRAW	0
#define LOSE	-100

#define MAX_TESTS	8


typedef struct {
  unsigned char test[3];
} test_t_l;

const test_t_l lin_tests[MAX_TESTS]={
  {{ 8, 7, 6 }}, 
  {{ 5, 4, 3 }},
  {{ 2, 1, 0 }}, 
  
  {{ 8, 5, 2 }},
  {{ 7, 4, 1 }},
  {{ 6, 3, 0 }},
  
  {{ 6, 4, 2 }}, 
  {{ 8, 4, 0 }} 
};

class linear
{
  public:
    int boards_checked;
    int computer_move;
    int moves;
    
    int this_player;
    int other_player;
    
    double w1;
    double w2;
    double w3;
    double w4;
    
    double cur_score;
    double pred_score;
    
    linear() ;
    linear(int player_char, int weight1, int weight2, int weight3, int weight4) ;
    void reset();

    int getCell( int cell, unsigned int board );
    void putCell( int player, int cell, unsigned int *board );
    char convert( int contents );
    int checkPlayerWin( int player, unsigned int cur_board );
    
    //     short scoreNextMove(unsigned int *board);
    double scoreNextMove(unsigned int *board, int player);
    int checkChanceofWin( int player, unsigned int cur_board );
    void adjustWeights( );
    
    short evaluateComputerMove( unsigned int board, int depth, int alpha, int beta );
//     short evaluateHumanMove( unsigned int board, int depth, int alpha, int beta );
    void getComputerMove( unsigned int *board );
};


linear::linear()
{
  moves = 0;
  this_player = 0;
  other_player = 0;
  
  w1 = 0;
  w2 = 0;
  w3 = 0;
  w4 = 0;
}

linear::linear(int player_char, int weight1, int weight2, int weight3, int weight4)
{
  moves = 0;
  this_player = player_char;
  other_player = (player_char % 2) + 1;
  
  w1 = weight1;
  w2 = weight2;
  w3 = weight3;
  w4 = weight4;
}

void linear::reset()
{
  moves = 0;
  boards_checked = 0;
  computer_move = 0;
  
  cur_score = 0;
  pred_score = 0;
}

int linear::checkPlayerWin( int player, unsigned int cur_board )
{
  int i;

  for (i = 0 ; i < MAX_TESTS ; i++)
  {
    if ((getCell(lin_tests[i].test[0], cur_board) == player) && (getCell(lin_tests[i].test[1], cur_board) == player) && (getCell(lin_tests[i].test[2], cur_board) == player))
      return 1;
  }

  return 0;
}


short linear::evaluateComputerMove( unsigned int board, int depth, int alpha, int beta )
{
  int i, value;
  unsigned int new_board;
  short max = LOSE-1;

  boards_checked++;

  /* The human (min) just made a move, so we evaluate that move here */
  //   if (checkPlayerWin(X_PLAYER, board))
  if (checkPlayerWin(other_player, board))
    return LOSE;

  for (i = 0 ; i < MAX_CHILD_NODES ; i++)
  {
    if (getCell(i, board) == EMPTY)
    {
      new_board = board;
      putCell( this_player, i, &new_board );
      value = scoreNextMove(&new_board,this_player);

      if (value > max) {
	max = value;
	computer_move = i;
      }
    }
  }

  /* No move is possible -- draw */
  if (max == LOSE-1) {
    return DRAW;
  }
  
  pred_score = max;
  return max;
}

double linear::scoreNextMove(unsigned int *board, int player)
{
  // params:
  //   x = # of possibilities of x to win
  //   o = # of possibilities of o to win
  //   y = # of blank spaces
  //   p = # of possibilities of o to immediately win
  int p,o,x,y;
  
  x = checkChanceofWin(this_player, *board)-checkPlayerWin(this_player, *board);
  o = checkChanceofWin(other_player, *board)-checkPlayerWin(other_player, *board);
  //   y = checkPlayerWin(this_player, *board)*50;
  y = ((9 - moves*2) >= 0) ? (9 - moves*2) : 0;
  p = checkPlayerWin(other_player, *board);
  
  double score = w1*x + w2*o + w3*y + w4*p;
//   printf("params\t%d\t%d\t%d\t%d\n",x,o,y,p);
  return ((score > 100) ? 100 : (score < -100) ? -100 : score);
}


int linear::checkChanceofWin( int player, unsigned int cur_board )
{
  int i;
  int count = 0;
  for (i = 0 ; i < MAX_TESTS ; i++)
  {
    if (
      ((getCell(lin_tests[i].test[0], cur_board) == player) || (getCell(lin_tests[i].test[0], cur_board) == EMPTY)) && 
      ((getCell(lin_tests[i].test[1], cur_board) == player) || (getCell(lin_tests[i].test[1], cur_board) == EMPTY)) && 
      ((getCell(lin_tests[i].test[2], cur_board) == player) || (getCell(lin_tests[i].test[2], cur_board) == EMPTY)))
      count = count+1;
  }

  return count;
}

void linear::getComputerMove(unsigned int *board )
{
  boards_checked = 0;

  evaluateComputerMove( *board, 0, LOSE-1, WIN+1 );
  cur_score = scoreNextMove(board, other_player);

  putCell( this_player, computer_move, board );
  moves++;

  adjustWeights();
  
  return;
}

void linear::adjustWeights()
{
  if (this_player %2 == 0)
  {
    if (1)
    {
      double c1 = 0.1;
      double c2 = 0.15;
      double c3 = 0.05;
      double c4 = 0.2;
      
      w1 = w1 + c1*(pred_score - cur_score);
      w2 = w2 + c2*(pred_score - cur_score);
      w3 = w3 + c3*(pred_score - cur_score);
      w4 = w4 + c4*(pred_score - cur_score);
    }
  }
  
  return;
}

int linear::getCell( int cell, unsigned int board )
{
  return ((board >> (cell*2)) & 0x3);
}

void linear::putCell( int player, int cell, unsigned int *board )
{
  cell = *board |= (player << (cell*2));
  return;
}


char linear::convert( int contents )
{
  if      (contents == X_PLAYER) return 'X';
  else if (contents == O_PLAYER) return 'O';

  return ' ';
}