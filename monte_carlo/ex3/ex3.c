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
// double* paths;
int* used_nodes;
path_time* path_t;


/* =========================== */
  double Uniform(double a, double b)          /* use a < b */
/* =========================== */
{
  return (a + (b - a) * Random());
}
/*
// ========================== //
  void GetActivityDurations()
// ========================== //
{
  long i;

  for (i = 1; i <= edges; i++)
    p[i] = Uniform(0.0, UpperLimit[i]);

  return;
}

// ================ //
  void PrintPaths()
// ================ //
{
  long i;
  long j;

  printf("\n");
  for (i = 1; i <= paths; i++) {
    printf("Path %ld: ", i);
    j = 1;
    while(Paths[i][j] != 0) {
      j++;
    }
    j--;
    while(j > 0) {
      printf("-%ld-", Paths[i][j]);
      j--;
    }
    printf("\n");
  }

  return;
}

// =============================== //
  double TimeToComplete(long node)
// =============================== //
{
  long   k;
  long   l = 0;
  double tmax   = 0.0;
  double t  = 0.0;

  k = 1;
  while (l < M[node][0]) {
    if (M[node][k] == -1) {
      t = TimeToComplete(M[0][k]) + p[k];
      if (t >= tmax)
	tmax = t;
      l++;
    }
    k++;
  }
  return(tmax);
}

// ============================================= //
  long GetPaths(long node, long step, long path)
// ============================================= //
{
  long i = 1;
  long j;
  long found    = 0;
  long numpaths = 0;
  long total    = 0;

  while(found < M[node][0]) {
    if(M[node][i] == -1) {
      numpaths = GetPaths(M[0][i], step + 1, path + total);
      for (j = 0; j < numpaths; j++) {
	Paths[path + j + total][step] = i;
      }
      total += numpaths;
      found++;
    }
    i++;
  }

  if(total == 0) {
    Paths[path][step] = 0;
    total = 1;
  }

  return(total);
}

// ============================================= //
  void EstimatePathProb()
// ============================================= //
{
  long   i;
  long   j;
  long   k;
  long   maxpath;
  long   PathProb[MAXPATHS] = {0};
  double pathtime           = 0.0;
  double maxtime            = 0.0;

  for (i = 0; i < N; i++) {
    GetActivityDurations();

    for (j = 1; j <= paths; j++) {
      k = 1;
      while(Paths[j][k] != 0) {
	pathtime += p[Paths[j][k]];
	k++;
      }
      if(pathtime > maxtime) {
	maxtime = pathtime;
	maxpath = j;
      }
      pathtime = 0.0;
    }
    PathProb[maxpath]++;

    maxpath = 0;
    maxtime = 0.0;
  }

  printf("\nCritical path probabilities:\n");
  for (i = 1; i <= paths; i++)
    printf(" -  %2ld  - ", i);
  printf("\n");
  for (i = 1; i <= paths; i++)
    printf(" %1.6f ", (double) PathProb[i]/N);
  printf("\n");

  return;
}

// =================== //
  void DefineNetwork()
// =================== //
{
  long j;
  long k;

//   edges = 5;
//   nodes = 4;

  for (j = 0; j <= nodes; j++) {
    for (k = 0; k <= edges; k++) {
      M[j][k] = 0;
    }
  }

  M[1][1] = 1;
  M[1][2] = 1;

  M[2][1] = -1;
  M[2][3] = 1;
  M[2][4] = 1;

  M[3][2] = -1;
  M[3][3] = -1;
  M[3][5] = 1;

  M[4][4] =-1;
  M[4][5] = -1;



  for (j = 1; j <= nodes; j++) {
    for (k = 1; k <= edges; k++) {
      if(M[j][k] == -1) {
	M[j][0]++;
      }
      else if(M[j][k] == 1) {
	M[0][k] = j;
      }
    }
  }

  UpperLimit[1] = 1.0;
  UpperLimit[2] = 1.0;
  UpperLimit[3] = 1.0;
  UpperLimit[4] = 1.0;
  UpperLimit[5] = 1.0;

  paths = GetPaths(nodes, 1, 1);

  printf("Network read in:\n");
  printf("%ld edges.\n", edges);
  printf("%ld nodes.\n", nodes);
  printf("%ld paths.\n", paths);

  return;
}

// ============================ //
  void EstimateCompletionTime()
// ============================ //
{
  long   node;
  long   i;
  double time;
  double sumtime = 0.0;

  node = nodes;

  for (i = 0; i < N; i++) {
    GetActivityDurations();
    time = TimeToComplete(node);
    sumtime += time;
  }

  printf("\nFor %ld replications,", N);
  printf("\nthe estimated average time to complete the network is:\n");
  printf("%11.5f\n", sumtime / (double) N);

  return;
}
*/

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

void getEdgeCount()
{
  long temp_edge = 0;
//   int i=0; // overcounting in for loop; i compensates for that

  for (long temp_node = 2; temp_node <= num_nodes; temp_node++)
  {
    temp_edge += temp_node-1;
//     i++;
  }

  edges = temp_edge;// - i;
}

void placeCities()
{
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

bool notAlreadyTaken(int path_num, int c)
{
  bool result=true;
  for (int i=0; i<num_nodes; i++)
  {
    if (path_t[path_num].path[i] == c)
      return true;
  }

//   for (int i=0; i<num_nodes; i++)
//   {
//     if (!result[i])
// //       return false;
//   }

  return false;
}

void travel()
{
  int current_path = 0;
  int total_paths = (int)Uniform(1.0f,edges);
  path_t = new path_time[total_paths];

  for (current_path; current_path < total_paths; current_path++)
  {
    path_t[current_path].path = new int[num_nodes+1];

    for (int i=0 ; i<num_nodes+1; i++)
      path_t[current_path].path[i] = -1;

    path_t[current_path].path[0] = 0;

    for (int i=1; i<num_nodes; i++)
    {
      int choice;
      int j=0;

      do
      {
	PutSeed(-1);
	choice = (int)Uniform(1.0f,num_nodes);
	j++;
      } while (notAlreadyTaken(current_path, choice) && (j <= num_nodes));

      if (j != num_nodes)
	path_t[current_path].path[i] = choice;

      else
      {
	path_t[current_path].path[i] = 0;
	break;
      }
    }

    int k=1;

    while(path_t[current_path].path[k] != -1 || k < num_nodes)
    {
      if (euclid)
	path_t[current_path].time += euclideanDistance(k-1,k);

      k++;
    }
  }

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

    print("\n");
}

int main()
{
  euclid = false;

  if(getInput() != 0)
    return -1;

  getEdgeCount();
  placeCities();
  travel();
  return 0;

  /*DefineNetwork();
  PrintPaths();
  PutSeed(0);
  EstimateCompletionTime();
  PutSeed(0);
  EstimatePathProb();
  return(0);*/
}
