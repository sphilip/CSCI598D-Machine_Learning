#ifndef _CELL_H
#define _CELL_H

struct transition
{
  int val;
  int *next;
  int current_cell;
}

class cell
{
  public:
    transition* out;
    int num_transitions;
    
    cell();
    cell(int size);
    
    void create_link(int from, int to);
};


#endif