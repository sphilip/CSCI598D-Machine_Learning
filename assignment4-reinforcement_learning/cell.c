#include "cell.h"

cell::cell()
{
  outbound = new int[1];
  num_transitions = 1;
}

cell::cell(int num)
{
  outbound = new int[num];
  num_transitions = num;
  links_created = 0;
}

void cell::create_link(cell& to)
{
  if (links_created < num_transitions)
  {
    outbound[links_created]->next = to;
    outbound[links_created].val = 0;
    
    links_created++;
  }
  
  else printf("this cell is full\n");
  
}

int cell::get_transition_value_from(int id)
{
  for (int i=0; i<links_created; i++)
  {
    if (outbound[i]->next.cell_id == id)
    {
      return outbound[i].val;
    }
  }
  
  printf("couldn't find cell with id %d",id);
  return -1;
}