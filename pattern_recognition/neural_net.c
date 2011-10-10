#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cmath>

#include "stdio.h"
#include "stdlib.h"
// #include "perceptron.h"

using namespace std;

// global variables
int **alphabet;
int image_size;
int alphabet_count;

struct perceptron_layer
{
  double weight;
  double value;
  double error;
};


void read_input(const char* name, int index) // name of file & index in alphabet
{
  ifstream infile(name, ifstream::in);
  if (!infile)
  {
    cout << "Can't read from " << name << endl;
    return;
  }

  if (infile.is_open())
  {
    char code[3];
    int height;
    int width;
    int pixel1,pixel2,pixel3;

    infile >> code;
    infile >> width >> height;
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
}


bool valid_file(const char* name)
{
  ifstream infile(name);

  if (infile) return true;
  else return false;
}


void test_alphabet(int alphabet_count)
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


double delta_func(double y)
{
  return 1.0f/(1.0f+exp(-y));
}

void backpropagation(int input_size,int hidden_size, int output_size, double learning_rate)
{
  perceptron_layer* input = new perceptron_layer[input_size];
  perceptron_layer* hidden = new perceptron_layer[hidden_size];
  perceptron_layer* output = new perceptron_layer[output_size];

  double *hidden_weights = new double[input_size];
  double *output_weights = new double[hidden_size];

  // initialize weights b/w -0.05 to +0.05
  for (int i=0; i<input_size; i++)
  {
    input[i].value = 0.0;
    input[i].weight = 0.10f*((double)rand())/((double)RAND_MAX) - 0.05f;
    input[i].error = 0.0;

    hidden_weights[i] = 0.10f*((double)rand())/((double)RAND_MAX) - 0.05f;
    if (i<hidden_size)
    {
      hidden[i].value = 0.0;
      hidden[i].weight = 0.10f*((double)rand())/((double)RAND_MAX) - 0.05f;
      hidden[i].error = 0.0;

      output_weights[i] = 0.10f*((double)rand())/((double)RAND_MAX) - 0.05f;
    }

    if (i<output_size)
    {
      output[i].value = 0.0;
      output[i].weight = 0.10f*((double)rand())/((double)RAND_MAX) - 0.05f;
      output[i].error = 0.0;
    }
  }

  cout << "hidden weights\n";
  for (int k=0; k<input_size; k++)
    cout << hidden_weights[k] << endl;

  cout << "output weights\n";
  for (int k=0; k<hidden_size; k++)
    cout << output_weights[k] << endl;

  for (int k=0; k<alphabet_count; k++)
  {
    // initialize inputs
    for (int j=0; j<input_size; j++)
      input[j].value = alphabet[k][j];

    // train with alphabet
    for (int j=0; j<hidden_size; j++)
    {
      for (int i=0;i<input_size; i++)
      {
	hidden[j].value = delta_func(hidden[j].value + (hidden_weights[i] * input[i].value));
      }
    }

    // calculate output and backpropagate errors
    for (int j=0; j<output_size; j++)
    {
      for (int i=0;i<hidden_size; i++)
      {
	output[j].value = delta_func( output[j].value + (output_weights[i] * hidden[i].value));
      }
    }
  }

  for (int z=0;z<output_size; z++)
  {
    cout << (char)(z + 97) << "\t" << output[z].value << endl;
  }

  delete[] input;
  delete[] hidden;
  delete[] output;
}

int main()
{
  srand(time(NULL));

  string filename;
  int a = 97;
  int z = 122;
  char letter;
  alphabet_count = 0;

  // how many valid files exist?
  for (int i=a; i<=z; i++)
  {
    sprintf(&letter,"%c",i);
    filename = "./letters/" + string (1,letter) + ".ppm";

    if ( valid_file(filename.c_str()) )
      alphabet_count++;
  }

  alphabet = new int*[alphabet_count];

  // save pixel values for each valid file
  for (int i=a; i<=z; i++)
  {
    sprintf(&letter,"%c",i);
    filename = "./letters/" + string (1,letter) + ".ppm";

    read_input(filename.c_str(),(i-97));
  }

//     test_alphabet(alphabet_count);

  backpropagation(image_size,alphabet_count,alphabet_count,0.5);





  clear_memory(alphabet_count);
  return 0;
}