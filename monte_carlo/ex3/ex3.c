/* --------------------------------------------------------------------------  *
 * A Monte Carlo simulation of a stochastic activity network.                  *
 *                                                                             *
 * Name              : san.c                                                   *
 * Author            : Jeff Mallozzi, Kerry Connell, Larry Leemis, Matt Duggan *
 * Language          : ANSI C                                                  *
 * Latest Revision   : 6-16-04                                                 *
 * Compile with makefile                              *
------------------------------------------------------------------------------ */

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"
#include <ctime>

#define MAXEDGE  50
#define MAXNODE  50
#define MAXPATHS 50
#define N 10000L                           /* number of replications */

using namespace std;

struct loc
{
  double x;
  double y;
};

struct path_time
{
  int* path;
  double time;
};

// long   M[MAXNODE][MAXEDGE];
// // long   Paths[MAXPATHS][MAXNODE];
// double UpperLimit[MAXEDGE];
// double p[MAXEDGE];
// long   paths;
// long   nodes;
loc* loc_nodes;
int num_nodes;
long   edges;
bool euclid;
double* euclid_dist;
loc* rect_dist;
path_time* path_t;
int total_paths;
/* =========================== */
  double Uniform(double a, double b)          /* use a < b */
/* =========================== */
{
  return (a + (b - a) * Random());
}

double euclideanDistance(int a, int b)
{
  return sqrt(pow((loc_nodes[a].x-loc_nodes[b].x),2)+pow((loc_nodes[a].y-loc_nodes[b].y),2));
}

loc rectilinearDistance(int a, int b)
{
  loc result;
  result.x = loc_nodes[b].x - loc_nodes[a].x;
  result.y = loc_nodes[b].y - loc_nodes[a].y;

  return result;
}

int getInput()
{
  printf("How many cities (including hometown)? ");
  cin >> num_nodes;

  if (num_nodes > 0)
    loc_nodes = new loc[num_nodes];

  else
  {
    printf("Not enough cities to continue\n");
    return -1;
  }

  printf("How to calculate distance?\n0 for Euclidean\n1 for Rectilinear\nChoice: ");
  int choice;
  cin >> choice;

  if (choice == 0)
    euclid = true;

  printf("\n");
  return 0;
}

void getPathCount()
{
  int path_count=1;

  if (num_nodes == 1)
    path_count = 0;
  
  else
  {
    for (int temp_node=2; temp_node<num_nodes; temp_node++)
    {
      path_count *= temp_node;
    }
  }
  
  total_paths = path_count;
  printf("Total number of paths: %d\n\n",path_count);
}

void getEdgeCount()
{
  long temp_edge = 0;
  for (long temp_node = 2; temp_node <= num_nodes; temp_node++)
  {
    temp_edge += temp_node-1;
  }

  edges = temp_edge;
}

void placeCities()
{
  printf("Locations:\n");
  for (int i=0; i<num_nodes; i++)
  {
    loc_nodes[i].x = Uniform(0.0f,1.0f);
    loc_nodes[i].y = Uniform(0.0f,1.0f);
    printf("City #%d at (%3.2f, %3.2f)\n", i,loc_nodes[i].x ,loc_nodes[i].y);
  }


  if (euclid)
  {
    euclid_dist = new double[num_nodes];
    for (int i=0; i<num_nodes; i++)
      for (int j=0; j<num_nodes; j++)
	if (i != j)
	{
	  euclid_dist[i] = sqrt(pow((loc_nodes[i].x-loc_nodes[j].x),2)+pow((loc_nodes[i].y-loc_nodes[j].y),2));
	  euclid_dist[i] *= Uniform(0.0f,2.0f);
	}
  }

  else
  {
    rect_dist = new loc[num_nodes];
    for (int i=0; i<num_nodes; i++)
      for (int j=0; j<num_nodes; j++)
	if (i != j)
	{
	  rect_dist[i].x = (loc_nodes[i].x - loc_nodes[j].x)*Uniform(0.0f,2.0f);
	  rect_dist[i].y = (loc_nodes[i].y - loc_nodes[j].y)*Uniform(0.0f,2.0f);
	}
  }

  printf("\n");
}

bool alreadyTaken(int path_num, int c)
{
//   bool result=true;
  for (int i=0; i<num_nodes; i++)
  {
    if (path_t[path_num].path[i] == c)
      return true;
    
    else if (path_t[path_num].path[i] == -1)
      return false;
  }

//   for (int i=0; i<num_nodes; i++)
//   {
//     if (!result[i])
// //       return false;
//   }

  return false;
}

void printPaths(int total)
{
  for (int i=0; i<total; i++)
  {
    printf("Path %d : ", i);
    for (int j=0; j<num_nodes; j++)
      printf("%d ", path_t[i].path[j]);
    printf("\n");
  }
  printf("\n");
}

void printTables()
{
  printf("Distance matrix\n");
  for (int i=0; i<num_nodes; i++)
  {
    for (int j=0; j<num_nodes; j++)
    {
      printf("%3.4f\t",euclideanDistance(i,j));
    }
    printf("\n");
  }
}

void travel()
{
//   int current_path = 0;
  //   int total_paths = (int)Uniform(1.0f,edges);
  path_t = new path_time[total_paths];

  for (int current_path=0; current_path < total_paths; current_path++)
  {
    path_t[current_path].time = 0.0f;
    path_t[current_path].path = new int[num_nodes+1];
    
    for (int x=0 ; x<num_nodes+1; x++)
      path_t[current_path].path[x] = -1;

    path_t[current_path].path[0] = 0;

    for (int i=1; i<num_nodes; i++)
    {
      double choice;
      int j=0;

      do
      {
        // 	PutSeed(time(NULL));
        // 	choice = Uniform(1.0f,(double)num_nodes);

        choice = rand()%(num_nodes-1) + 1.0f;
        if (!alreadyTaken(current_path, choice))
          break;

        else j++;
      } while (j <= num_nodes);

     
      if (j < num_nodes)
	path_t[current_path].path[i] = choice;

//       else
//       {
// 	path_t[current_path].path[i] = 0;
// 	break;
//       }
    }

    int k=1;

    
    while(path_t[current_path].path[k] != -1 && k < num_nodes)
    {
      if (euclid)
	path_t[current_path].time += euclideanDistance(path_t[current_path].path[k-1],path_t[current_path].path[k]);

      k++;
    }
  }
  
  printPaths(total_paths);
  
  double min_time = 90.0f;
  int index;

  for (int k=0; k<total_paths; k++)
  {
    if (path_t[k].time < min_time)
    {
      min_time = path_t[k].time;
      index = k;
    }
  }

  printf("To travel %d cities:\n",num_nodes);
  printf("Time needed: %3.3f\n", min_time);
  printf("Optimal path:\t");

  for (int x=0; x<num_nodes+1; x++)
    if (path_t[index].path[x] != -1)
      printf("%d ", path_t[index].path[x]);

    printf("\n");
}


int main()
{
  srand(time(NULL));
  euclid = false;

  if(getInput() != 0)
    return -1;

  getPathCount();
  getEdgeCount();
  placeCities();
  travel();
  
  printTables();
  return 0;

  /*DefineNetwork();
  PrintPaths();
  PutSeed(0);
  EstimateCompletionTime();
  PutSeed(0);
  EstimatePathProb();
  return(0);*/
}
