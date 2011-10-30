#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cmath>

#include "stdio.h"
#include "stdlib.h"

using namespace std;

#define RANDOM_LETTER (int) (25.0f*(double)rand()/(double)RAND_MAX)
#define RANDOM_WEIGHT 0.10f*((double)rand())/((double)RAND_MAX) - 0.05f

// global variables
int **alphabet;
int image_size;
int alphabet_count;
// int *test_letter;

int *backpropagation_input;
int **target_output;

double **input_to_hidden_weight;
double **hidden_to_output_weight;

double *input_value;
double *hidden_value;
double *output_value;

double *hidden_error;
double *output_error;

int input_size;
int hidden_size;
int output_size;

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

  input_size = image_size;
  hidden_size = alphabet_count;
  output_size = alphabet_count;
}

void clear_memory()
{
  for (int i=0;i<alphabet_count;i++)
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

  delete[] backpropagation_input;

  for (int i=0; i<alphabet_count; i++)
    delete[] target_output[i];

  delete[] target_output;
}


double sigma_func(double y)
{
  return 1.0f/(1.0f+exp(-y));
}


void init_network()
{
  input_to_hidden_weight = new double*[input_size];
  hidden_to_output_weight = new double*[hidden_size];

  for (int i=0; i<input_size; i++)
  {
    input_to_hidden_weight[i] = new double[hidden_size];
    for (int j=0; j<hidden_size; j++)
    {
      input_to_hidden_weight[i][j] = RANDOM_WEIGHT;
    }
  }

  for (int i=0; i<hidden_size; i++)
  {
    hidden_to_output_weight[i] = new double[output_size];
    for (int j=0; j<output_size; j++)
      hidden_to_output_weight[i][j] = RANDOM_WEIGHT;
  }

  backpropagation_input = new int[input_size];
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

  // determine the target values per letter
  target_output = new int*[alphabet_count];
  for (int i=0; i<alphabet_count; i++)
    target_output[i] = new int[alphabet_count];

  for (int i=0; i<alphabet_count; i++)
  {
    for (int j=0; j<alphabet_count; j++)
    {
      if (i == j)
	target_output[i][j] = 1;
      else target_output[i][j] = 0;
    }
  }

//   test_letter = new int[image_size];
}

double calculate_mse(int letter)
{
  double mse=0.0f;
  for (int j=0; j<output_size; j++)
  {
    double error = (target_output[letter][j]-output_value[j])*(target_output[letter][j]-output_value[j]);
    mse += error;
  }

  mse = mse/output_size;
  cout << mse << endl;
  return mse;
}

void weight_update(double learning_rate)
{
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

}

void backpropagate_errors(int letter)
{
  // backpropagate errors @ output
  for (int j=0; j<output_size; j++)
    output_error[j] = output_value[j]*(1.0f-output_value[j])*(target_output[letter][j]-output_value[j]);

  // backpropagate error @ hidden
  for (int j=0; j<hidden_size; j++)
  {
    double sum=0.0f;
    for (int i=0; i<output_size; i++)
      sum += hidden_to_output_weight[j][i]*output_error[i];

    hidden_error[j] = hidden_value[j]*(1.0f-hidden_value[j])*sum;
  }
}


void apply_network()
{
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

/*   // backpropagate errors @ output
//   double target;
//   for (int j=0; j<output_size; j++)
//   {
//     if (j==letter)
//       target = 1.0f;
//     else target = -1.0f;
//
//     output_error[j] = output_value[j]*(1.0f-output_value[j])*(target-output_value[j]);
//   }
//
//   // backpropagate error @ hidden
//   for (int j=0; j<hidden_size; j++)
//   {
//     double sum=0.0f;
//     for (int i=0; i<output_size; i++)
//       sum += hidden_to_output_weight[i][j]*output_error[i];
//
//     hidden_error[j] = hidden_value[j]*(1.0f-hidden_value[j])*sum;
//   }
//
//   // update weights
//   for (int j=0;j<input_size; j++)
//   {
//     for (int i=0; i<hidden_size; i++)
//       input_to_hidden_weight[j][i] = input_to_hidden_weight[j][i] + learning_rate*hidden_error[i]*input_value[j];
//   }
//
//   for(int j=0; j<hidden_size; j++)
//   {
//     for (int i=0; i<output_size; i++)
//       hidden_to_output_weight[j][i] = hidden_to_output_weight[j][i] + learning_rate*output_error[i]*hidden_value[j];
//   }
//
//   double mse;
//   for (int j=0; j<output_size; j++)
//     mse += (output_error[j]*output_error[j]);
//
//   mse = mse/output_size;
//
//   //  output results
//   //   for (int z=0;z<output_size; z++)
//   //     cout << (char)(z + 97) << "\t" << output_value[z] << endl;
//
//   return mse;
*/
}

void create_character(int letter, double noise)
{
  for (int i=0; i<image_size; i++)
    backpropagation_input[i] = alphabet[letter][i];
  // test_letter = alphabet[letter];

  //   backpropagation_input = alphabet[letter];

  for (int i=0; i<image_size; i++)
  {
    if (rand() < noise * RAND_MAX)
    {
      if (backpropagation_input[i])
	backpropagation_input[i] = 0;

      else backpropagation_input[i] =  1;
    }
  }
}

void print_output()
{
  for (int i=0; i<output_size; i++)
    cout << (char) (i+97) << "\t" << output_value[i] << endl;
}
void classify_input(int size, int index, double noise)
{
  double max = -999.0f;
  int max_id = -1;

  print_output();

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

  double error=0;


  init_network();

  do
  {
    int chosen_letter = RANDOM_LETTER;

    // initialize inputs
    for (int j=0; j<image_size; j++)
      backpropagation_input[j] = alphabet[chosen_letter][j];

    apply_network();

    backpropagate_errors(chosen_letter);
    weight_update(chosen_letter);

    error = calculate_mse(chosen_letter);

  } while (error > 0.001);


  /* Start with 5% noise probability, end with 25% (per pixel) */
  double noise_prob = 0.05f;

  int rand_letter = RANDOM_LETTER;
  cout << "Original letter is " <<  (char) (rand_letter+97) << endl;

  for (int i=0; i<5 ; i++)
  {
    create_character(rand_letter, noise_prob);

//     //initialize inputs
//     for (int j=0; j<image_size; j++)
//       backpropagation_input[j] = alphabet[rand_letter][j];

    apply_network();
    classify_input(alphabet_count, rand_letter, noise_prob);

    noise_prob += 0.05;

  }

  clear_memory();
  return 0;
}