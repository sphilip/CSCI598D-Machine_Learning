#include "cell.h"

cell::cell()
{
  out = new int[1];
  num_transitions = 1;
}

cell::cell(int num)
{
  out = new int[num];
  num_transitions = num;
}

void cell::create_link(int from, int to)
{
  if (from > num_transitions)
    std::cout << "Can't make link from cells " << from << "to " << to << std::endl;
  else if (to > num_transitions)
    std::cout << "Can't make link from cells " << from << "to " << to << std::endl;
  else if (from == out.current_cell)
    
}