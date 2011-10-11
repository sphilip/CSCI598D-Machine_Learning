#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cmath>

#include "stdio.h"
#include "stdlib.h"

using namespace std;


// global variables
int **alphabet;
int image_size;
int alphabet_count;
int *test_letter;


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
      if (pixel1 > 35)
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


double sigma_func(double y)
{
  return 1.0f/(1.0f+exp(-y));
}

double backpropagation(int input_size,int hidden_size, int output_size, double learning_rate, int letter)
{

  double **input_to_hidden_weight = new double*[input_size];
  double **hidden_to_output_weight = new double*[hidden_size];
  
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

  double *input_value = new double[input_size];
  double *hidden_value = new double[hidden_size];
  double *output_value = new double[output_size];
  
  double *hidden_error = new double[hidden_size];
  double *output_error = new double[output_size];
  
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
  
//   for (int letter=0; letter<alphabet_count; letter++)
//   {
//     double mse=0;
//     do {
      // initialize inputs
      for (int j=0; j<input_size; j++)
        input_value[j] = alphabet[letter][j];
      
      // train with alphabet
      for (int j=0; j<hidden_size; j++)
      {
        double net=0.0f;
        for (int i=0;i<input_size; i++)
        {
          net += input_to_hidden_weight[i][j] * input_value[i];
        }
        
        hidden_value[j] = net;
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
      double error=0.0f;
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
          input_to_hidden_weight[j][i] = input_to_hidden_weight[j][i] + learning_rate*hidden_error[j]*input_value[j]; 
      }
      
      for(int j=0; j<hidden_size; j++)
      {
        for (int i=0; i<output_size; i++)
          hidden_to_output_weight[j][i] = hidden_to_output_weight[j][i] + learning_rate*output_error[j]*hidden_value[j]; 
      }
      
      double mse;
      for (int j=0; j<output_size; j++)
        mse += (output_error[j]*output_error[j]);
      
      mse = mse/output_size;
  
  //  output results
//   for (int z=0;z<output_size; z++)
//     cout << (char)(z + 97) << "\t" << output_value[z] << endl;
  
  delete[] input_to_hidden_weight;
  delete[] hidden_to_output_weight;
  
  delete[] input_value;
  delete[] output_value;
  delete[] hidden_value;
  
  delete[] hidden_error;
  delete[] output_error;
  
  return mse;
}

void create_character(int letter, double noise)
{
  test_letter = new int[image_size];
  test_letter = alphabet[letter];
  
  cout << "original letter:\n";
  for (int i=0; i<image_size; i++)
  {
    if (i%14 == 0 && i != 0)
      cout << alphabet[letter][i] << endl;
    else cout << alphabet[letter][i] << " ";
  }
  
  cout << endl;
  
  for (int i=0; i<image_size; i++)
  {
    if (rand() < noise * RAND_MAX) {
      test_letter[i] = (test_letter[i]) ? 0 : 1;
     }
  }
  
  cout << "noisy letter:\n";
  cout << "supposed to resemble the letter " << (char) (letter +97) << endl;
  for (int i=0; i<image_size; i++)
  {
    if (i%14 == 0 && i != 0)
      cout << test_letter[i] << endl;
    else cout << test_letter[i] << " ";
  }
  
  cout << endl;
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
  double error=0;
  int test_letter_index;
  
  do
  {
    test_letter_index = (int) 25.0f*((double) rand()/(double) RAND_MAX);
    error = backpropagation(image_size,alphabet_count,alphabet_count,0.5, test_letter_index);
  } while (error > 0.01f);
  
  
  /* Start with 5% noise probability, end with 25% (per pixel) */
  double noise_prob = 0.05;
  test_letter_index = (int) (25*rand()/RAND_MAX);
  
  create_character(test_letter_index, noise_prob);
//   for (int i=0; i<5 ; i++) {
// 
//     set_network_inputs( test, noise_prob );
// 
//     feed_forward();
// 
//     for (j = 0 ; j < INPUT_NEURONS ; j++) {
//       if ((j % 5) == 0) printf("\n");
//       printf("%d ", (int)inputs[j]);
//     }
// 
//     printf( "\nclassified as %d\n\n", classifier() );
// 
//     noise_prob += 0.05;
// 
//   }
  
  clear_memory(alphabet_count);
  return 0;
}