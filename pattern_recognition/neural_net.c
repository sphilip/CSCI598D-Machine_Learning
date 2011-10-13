#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cmath>

#include "stdio.h"
#include "stdlib.h"

using namespace std;

#define RANDOM_LETTER (int) (25.0f*(double)rand()/(double)RAND_MAX)

// global variables
int **alphabet;
int image_size;
int alphabet_count;
int *test_letter;

double **input_to_hidden_weight;
double **hidden_to_output_weight;

double *input_value;
double *hidden_value;
double *output_value;

double *hidden_error;
double *output_error;


// name of file & index in alphabet
void read_input(const char* name, int index)
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
      if (pixel1 > 113)
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


void test_alphabet()
{
  for (int i=0; i<alphabet_count; i++)
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

void count_files()
{
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

}

void clear_memory(int count, int input_size, int hidden_size, int output_size)
{
  for (int i=0;i<count;i++)
    delete[] alphabet[i];

  delete[] alphabet;

  for (int i=0; i<input_size; i++)
    delete[] input_to_hidden_weight[i];

  delete[] input_to_hidden_weight;

  for (int i=0; i<hidden_size; i++)
    delete[] hidden_to_output_weight[i];

  delete[] hidden_to_output_weight;

//   delete[] test_letter;
  delete[] input_value;
  delete[] output_value;
  delete[] hidden_value;

  delete[] hidden_error;
  delete[] output_error;
}


double sigma_func(double y)
{
  return 1.0f/(1.0f+exp(-y));
}


void init_network(int input_size,int hidden_size, int output_size)
{
  input_to_hidden_weight = new double*[input_size];
  hidden_to_output_weight = new double*[hidden_size];

  for (int i=0; i<input_size; i++)
  {
    input_to_hidden_weight[i] = new double[hidden_size];
    for (int j=0; j<hidden_size; j++)
    {
      input_to_hidden_weight[i][j] = ((double)rand())/((double)RAND_MAX) - 0.5f;
    }
  }

  for (int i=0; i<hidden_size; i++)
  {
    hidden_to_output_weight[i] = new double[output_size];
    for (int j=0; j<output_size; j++)
      hidden_to_output_weight[i][j] = ((double)rand())/((double)RAND_MAX) - 0.5f;
  }

  input_value = new double[input_size];
  hidden_value = new double[hidden_size];
  output_value = new double[output_size];

  hidden_error = new double[hidden_size];
  output_error = new double[output_size];

  // initialize weights b/w -0.05 to +0.05
  for (int i=0; i<input_size; i++)
  {
    input_value[i] = 0.0f;

    if (i<hidden_size)
    {
      hidden_error[i] = 0.0f;
      hidden_value[i] = 0.0f;
    }

    if (i<output_size)
    {
      output_value[i] = 0.0f;
      output_error[i] = 0.0f;
    }
  }


}


double backpropagation(int input_size,int hidden_size, int output_size, double learning_rate, int letter)
{
  // initialize inputs
  for (int j=0; j<input_size; j++)
    input_value[j] = alphabet[letter][j];

  // train with alphabet
  for (int j=0; j<hidden_size; j++)
  {
    //     double net=0.0f;
    for (int i=0;i<input_size; i++)
    {
      //       net += input_to_hidden_weight[i][j] * input_value[i];
      hidden_value[j] += input_to_hidden_weight[i][j] * input_value[i];
    }

    //     hidden_value[j] = net;
  }

  // calculate output
  for (int j=0; j<output_size; j++)
  {
    double net=0.0f;
    for (int i=0; i<hidden_size; i++)
    {
      net += hidden_to_output_weight[i][j] * hidden_value[i];
    }

    output_value[j] = sigma_func(net);
  }

  // backpropagate errors @ output
  double target;
  for (int j=0; j<output_size; j++)
  {
    if (j==letter)
      target = 1.0f;
    else target = -1.0f;

    output_error[j] = output_value[j]*(1.0f-output_value[j])*(target-output_value[j]);
  }

  // backpropagate error @ hidden
  for (int j=0; j<hidden_size; j++)
  {
    double sum=0.0f;
    for (int i=0; i<output_size; i++)
      sum += hidden_to_output_weight[i][j]*output_error[i];

    hidden_error[j] = hidden_value[j]*(1.0f-hidden_value[j])*sum;
  }

  // update weights
  for (int j=0;j<input_size; j++)
  {
    for (int i=0; i<hidden_size; i++)
      input_to_hidden_weight[j][i] = input_to_hidden_weight[j][i] + learning_rate*hidden_error[i]*input_value[j];
  }

  for(int j=0; j<hidden_size; j++)
  {
    for (int i=0; i<output_size; i++)
      hidden_to_output_weight[j][i] = hidden_to_output_weight[j][i] + learning_rate*output_error[i]*hidden_value[j];
  }

  double mse;
  for (int j=0; j<output_size; j++)
    mse += (output_error[j]*output_error[j]);

  mse = mse/output_size;

  //  output results
  //   for (int z=0;z<output_size; z++)
  //     cout << (char)(z + 97) << "\t" << output_value[z] << endl;

  return mse;
}

void create_character(int letter, double noise)
{
  test_letter = new int[image_size];
  test_letter = alphabet[letter];

  for (int i=0; i<image_size; i++)
  {
    if (rand() < noise * RAND_MAX)
      test_letter[i] = (test_letter[i]) ? 0 : 1;
  }
}

void classify_input(int size, int index, double noise)
{
  double max = -999.0f;
  int max_id = -1;

  for (int i=0; i<size; i++)
  {
    if (output_value[i] > max)
    {
      max = output_value[i];
      max_id = i;
    }
  }

  cout << "Classified as " << (char) (max_id+97) << " with " << noise*100 << "% noise\n";
}

int main()
{
  srand(time(NULL));

  count_files();

  //     test_alphabet(alphabet_count);
  double error=0;

  init_network(image_size,alphabet_count,alphabet_count);
  do
  {
    error = backpropagation(image_size,alphabet_count,alphabet_count,0.5, RANDOM_LETTER);
  } while (error > 0.001);


  /* Start with 5% noise probability, end with 25% (per pixel) */
  double noise_prob = 0.05;

  int rand_letter = RANDOM_LETTER;
  cout << "Original letter is " <<  (char) (rand_letter+97) << endl;

  for (int i=0; i<5 ; i++)
  {
    create_character(rand_letter, noise_prob);
//     backpropagation(image_size,alphabet_count,alphabet_count,0.5, rand_letter);
    classify_input(alphabet_count, rand_letter, noise_prob);

    noise_prob += 0.05;
  }

  clear_memory(alphabet_count,image_size,alphabet_count,alphabet_count);
  return 0;
}