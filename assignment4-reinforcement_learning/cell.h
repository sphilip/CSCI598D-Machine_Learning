#ifndef _CELL_H
#define _CELL_H

// #include "defs.h"
class cell;

struct transition
{
    int val;
    cell *next;
};

class cell
{
  public:
    transition* outbound;
    int num_transitions;
    int cell_id;
    int links_created;
    
    cell();
    cell(int size);
    
    void create_link(cell*);
    int get_transition_value_from(int id);
};

#endif