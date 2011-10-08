#include <iostream>
#include <fstream>
#include "stdio.h"
#include "stdlib.h"
#include <cstring>
// #include "perceptron.h"

using namespace std;

// global variables
int **alphabet;
int *letters;
int image_size;

struct perceptron
{
  double weight;
  double value;
};


void read_input(const char* name, int index) // name of file & index in alphabet
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
  int pixel1,pixel2,pixel3;

  infile >> code >> width >> height;
  image_size = width*height;

  alphabet[index] = new int[width*height];

  int i(0);
  while (!infile.eof())
  {
    pixel1 = -1;
    pixel2 = -1;
    pixel3 = -1;
    infile >> pixel1 >> pixel2 >> pixel3;
    
    // scale pixel values b/w 0,1
    if (pixel1 == 255)
      pixel1 = 0;  // if white
    
    else pixel1 = 1; // if black
      
    alphabet[index][i] = pixel1;
    i++;
  }
  
  infile.close();
}


bool valid_file(const char* name)
{
  ifstream infile(name);

  if (infile) return true;
  else return false;
}


void test_alphabet()
{
  for (int i=0; i<26; i++)
  {
    for (int j=0; j<image_size; j++)
    {
      if (j%14 == 0)
        cout << endl << alphabet[i][j] << " ";
      else
        cout << alphabet[i][j] << " ";
    }
    
    cout << "\n\n";
  }
}


void clear_memory(int count)
{
  for (int i=0;i<count;i++)
    delete[] alphabet[i];
  
  delete[] alphabet;
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

    read_input(filename.c_str(),(i-97));
  }
  
  //   test_alphabet();
  
  
  
  
  
  
  
  clear_memory(valid_count);
  return 0;
}