#include <iostream>
#include "cell.h"

using namespace std;

int main()
{
  /*
  1 -- 2 -- 3
  |    |    |
  |    |    |
  4 -- 5 -- 6
  */
  cell uno(1,2);
  cell two(2,3);
  cell three(3,2);
  cell four(4,2);
  cell five(5,3);
  cell six(6,2);

  uno.create_link(four);
  uno.create_link(two);

  cout << uno.cell_id << endl;
  cout << uno.num_transitions << "\t" << uno.links_created << endl;

  for (int i=0; i<uno.num_transitions; i++)
    cout << uno.outbound[i].next->cell_id << endl;

  return 0;
}