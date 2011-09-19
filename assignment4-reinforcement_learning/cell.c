#include "stdio.h"
#include "cell.h"

cell::cell()
{
  cell_id = -1;
  links_created = -1;
  max_transition_value = -1;

  outbound = new transition[1];
  num_transitions = 0;
}

cell::cell(int id, int num)
{
  cell_id = id;

  outbound = new transition[num];
  num_transitions = num;

  links_created = 0;
  max_transition_value = 0;
}

void cell::create_link(cell& to)
{
  if (links_created < num_transitions)
  {
    outbound[links_created].next = &to;
    outbound[links_created].val = 0;

    links_created++;
  }

  else printf("this cell is full\n");

}

int cell::get_transition_value_from(int id)
{
  for (int i=0; i<links_created; i++)
  {
    if (outbound[i].next->cell_id == id)
    {
      return outbound[i].val;
    }
  }

  printf("couldn't find cell with id %d",id);
  return -1;
}

void cell::get_max_transition()
{
  if (num_transitions > 0)
  {
    int max = -9999;

    for (int i=0; i<num_transitions; i++)
    {
      if (outbound[i].val > max)
	max = outbound[i].val;
    }

    max_transition_value = max;
  }

  else printf("there aren't any transitions...\n");
}