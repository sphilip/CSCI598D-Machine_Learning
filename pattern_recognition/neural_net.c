#include <iostream>
#include <fstream>
#include "stdio.h"
#include "stdlib.h"
#include <cstring>
// #include "perceptron.h"

using namespace std;

int **alphabet;
int *letters;

void read_input(const char* name)
{
  ifstream infile(name);
  if (!infile)
  {
    cout << "Can't read from " << name << endl;
    return;
  }

  char code[2];
  int height;
  int width;
  int pixel;

  infile >> code;
  infile >> width;
  infile >> height;
  cout << width << endl << height;
  infile.close();
}

bool valid_file(const char* name)
{
  ifstream infile(name);

  if (infile) return true;
  else return false;
}

int main()
{
  string filename;
  int a = 97;
  int z = 122;
  char letter;
  int valid_count = 0;

  // how many valid files exist?
  for (int i=a; i<=z; i++)
  {
    sprintf(&letter,"%c",i);
    filename = "./letters/" + string (1,letter) + ".ppm";

    if (valid_file) valid_count++;
  }

  alphabet = new int*[valid_count];

  // save pixel values for each valid file
  for (int i=a; i<=z; i++)
  {
    sprintf(&letter,"%c",i);
    filename = "./letters/" + string (1,letter) + ".ppm";

    read_input(filename.c_str());
  }
  return 0;
}