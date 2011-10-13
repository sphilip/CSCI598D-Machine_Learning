#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
//#include "rand.h"

#define INPUT_NEURONS	322
#define HIDDEN_NEURONS	26
#define OUTPUT_NEURONS	26

using namespace std;

double inputs[INPUT_NEURONS+1];
double hidden[HIDDEN_NEURONS+1];
double outputs[OUTPUT_NEURONS];

#define RHO	(double)0.1

double w_h_i[HIDDEN_NEURONS][INPUT_NEURONS+1];

double w_o_h[OUTPUT_NEURONS][HIDDEN_NEURONS+1];

#define RAND_WEIGHT	(((double)rand() / (double)RAND_MAX) - 0.5)

#define IMAGE_SIZE	322

#define MAX_TESTS	26

// global variables
int **alphabet;
int image_size;
int alphabet_count;

typedef struct test_images_s {

  int image[IMAGE_SIZE];
  int output[OUTPUT_NEURONS];

} test_image_t;

test_image_t tests[MAX_TESTS];

void halt() { while( getchar() != '\n'); }

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
      if (pixel1 > 113) pixel1 = 0; // if white
      else pixel1 = 1; // if black

      alphabet[index][i] = pixel1;
      tests[index].image[i] = pixel1;
      i++;
    }
      
    for(int j=0; j<MAX_TESTS; j++)
      if(j==index) tests[index].output[j]=1;
      else tests[index].output[j]=0;

    infile.close();
  }
}

void process_file(const char* name, int index) // name of file & index in alphabet
{
  //cout << "filename is " << name<<endl;
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
      if (pixel1 > 113) pixel1 = 0; // if white
      else pixel1 = 1; // if black

      alphabet[index][i] = pixel1;
      tests[index].image[i] = pixel1;
      i++;
    }

    infile.close();
  }
}

void generate_output(char letter,int output[OUTPUT_NEURONS]){
  int index=0;
  if(letter == 'a') index=0;
  else if(letter =='b') index=1;
  else if(letter =='c') index=2;
  else if(letter =='d') index=3;
  else if(letter =='e') index=4;
  else if(letter =='f') index=5;
  else if(letter =='g') index=6;
  else if(letter =='h') index=7;
  else if(letter =='i') index=8;
  else if(letter =='j') index=9;
  else if(letter =='k') index=10;
  else if(letter =='l') index=11;
  else if(letter =='m') index=12;
  else if(letter =='n') index=13;
  else if(letter =='o') index=14;
  else if(letter =='p') index=15;
  else if(letter =='q') index=16;
  else if(letter =='r') index=17;
  else if(letter =='s') index=18;
  else if(letter =='t') index=19;
  else if(letter =='u') index=20;
  else if(letter =='v') index=21;
  else if(letter =='w') index=22;
  else if(letter =='x') index=23;
  else if(letter =='y') index=24;
  else if(letter =='z') index=25;
  
  //cout<<"input letter is "<<letter<<", index is "<<index<<endl;
  for(int j=0; j<MAX_TESTS; j++)
      if(j==index) output[j]=1;
      else output[j]=0;
}

void process_input_list(string dir, string name){
  name = dir + name;
  ifstream infile(name.c_str(), ifstream::in);
  if (!infile)
  {
    cout << "Can't read from " << name << endl;
    return;
  }
  
  string datas[100];
  int i(0);
  //find all validation data
  if (infile.is_open())
  {    
    
    while (!infile.eof())
    {
      string file;
      infile >> file;
      //cout<<file<<endl;
      //file = dir+file;
      datas[i] = file;
      i++;
    }
  }
  infile.close();
  
  //cout<<"Selecting subset of validation data"<<endl;
  
  //choose a subset of 26 values of the validation data
  //generate two random numbers and swap their values in the datas array
  int r1,r2;
  //cout<<i<<endl;
  string tmp;
  for(int x=0; x<MAX_TESTS; x++){
    r1= rand()%(i-1); r2 = rand()%(i-1);
    //cout<<r1<<","<<r2<<endl;
    tmp = datas[r1];
    datas[r1] = datas[r2];
    datas[r2] = tmp;
  }
  
  //cout<<"Processing subset"<<endl;
  
  //read in the 26 selected sets of validation data
  for(int x=0; x<MAX_TESTS; x++){
    //cout<<datas[x][0]<<endl;
    generate_output(datas[x][0],tests[x].output);
    string f = dir + datas[x];
    process_file(f.c_str(),x);
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
    halt();
  }
}

void test_image_matrix(int alphabet_count)
{
  for (int i=0; i<MAX_TESTS; i++)
  {
    for (int j=0; j<OUTPUT_NEURONS; j++)
      cout<<tests[i].output[j];

    cout << "\n\n";
    halt();
  }
}

double sigmoid(double x) {
	return 1.0/(1+exp(-x));
}
double sigmoid_d(double x) {
	double g = sigmoid(x);
	return g*(1-g);
}
void init_network( void )
{
  int i, j;

  /* Set the input bias */
  inputs[INPUT_NEURONS] = 1.0;

  /* Set the hidden bias */
  hidden[HIDDEN_NEURONS] = 1.0;

  /* Initialize the input->hidden weights */
  for (j = 0 ; j  < HIDDEN_NEURONS ; j++) {
    for (i = 0 ; i < INPUT_NEURONS+1 ; i++) {
      w_h_i[j][i] = RAND_WEIGHT;
    }
  }

  for (j = 0 ; j < OUTPUT_NEURONS ; j++) {
    for (i = 0 ; i < HIDDEN_NEURONS+1 ; i++) {
      w_o_h[j][i] = RAND_WEIGHT;
    }
  }

  return;
}

void feed_forward( void )
{
  int i, j;

  /* Calculate outputs of the hidden layer */
  for (i = 0 ; i < HIDDEN_NEURONS ; i++) {

    hidden[i] = 0.0;

    for (j = 0 ; j < INPUT_NEURONS+1 ; j++) {
      hidden[i] += (w_h_i[i][j] * inputs[j]);
    }

    hidden[i] = sigmoid( hidden[i] );

  }

  /* Calculate outputs for the output layer */
  for (i = 0 ; i < OUTPUT_NEURONS ; i++) {

    outputs[i] = 0.0;

    for (j = 0 ; j < HIDDEN_NEURONS+1 ; j++) {
      outputs[i] += (w_o_h[i][j] * hidden[j] );
    }

    outputs[i] = sigmoid( outputs[i] );

  }

}

void backpropagate_error( int test )
{
  int out, hid, inp;
  double err_out[OUTPUT_NEURONS];
  double err_hid[HIDDEN_NEURONS];

  /* Compute the error for the output nodes */
  for (out = 0 ; out < OUTPUT_NEURONS ; out++) {

    err_out[out] = ((double)tests[test].output[out] - outputs[out]) * sigmoid_d(outputs[out]);

  }

  /* Compute the error for the hidden nodes */
  for (hid = 0 ; hid < HIDDEN_NEURONS ; hid++) {

    err_hid[hid] = 0.0;

    /* Include error contribution for all output nodes */
    for (out = 0 ; out < OUTPUT_NEURONS ; out++) {
      err_hid[hid] += err_out[out] * w_o_h[out][hid];
    }

    err_hid[hid] *= sigmoid_d( hidden[hid] );

  }

  /* Adjust the weights from the hidden to output layer  */
  for (out = 0 ; out < OUTPUT_NEURONS ; out++) {

    for (hid = 0 ; hid < HIDDEN_NEURONS ; hid++) {
      w_o_h[out][hid] += RHO * err_out[out] * hidden[hid];
    }

  }

  /* Adjust the weights from the input to hidden layer  */
  for (hid = 0 ; hid < HIDDEN_NEURONS ; hid++) {

    for (inp = 0 ; inp < INPUT_NEURONS+1 ; inp++) {
      w_h_i[hid][inp] += RHO * err_hid[hid] * inputs[inp];
    }

  }

  return;
}

double calculate_mse( int test )
{
  double mse = 0.0;
  int i;

  for (i = 0 ; i < OUTPUT_NEURONS ; i++) {
    double t = tests[test].output[i] - outputs[i];
    mse += t*t;
  }

  return ( mse / (double)i );
}

void set_network_inputs( int test, double noise_prob )
{
  int i;

  /* Fill the network inputs vector from the test */
  for (i = 0 ; i < INPUT_NEURONS ; i++) {

    inputs[i] = tests[test].image[i];

    /* In the given noise probability, negate the cell */
    if (rand() < noise_prob * RAND_MAX) {
      inputs[i] = (inputs[i]) ? 0 : 1;
    }

  }

  return;
}

int classifier( void )
{
  int i, best;
  double max;

  best = 0;
  max = outputs[0];


  for (i = 1 ; i < OUTPUT_NEURONS ; i++) {

    if (outputs[i] > max) {
      max = outputs[i];
      best = i;
    }

  }

  return best;
}

int rand_test() {
	int r = rand();
	int RR=RAND_MAX/MAX_TESTS;
	int rr = r/(RR);
	return rr;
}

int find_ans(int index){
  int i=0;
  for(i=0;i<MAX_TESTS; i++)
    if(tests[index].output[i]==1) break;
    
  return i;
}

int main( void )
{
  double mse, noise_prob;
  int test, i;
  
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
  
  //test_alphabet(26); //verify that each letter is read in and converted to binary correctly
  //test_image_matrix(26);
  
  //cout<<"You made it this for, sweet!\n";
  //halt();


  init_network();
  
//   cout<<"Network initalized!\n";

  //training
  do {

    /* Pick a test at random */
    test = rand_test();

    /* Grab input image (with no noise) */
    set_network_inputs( test, 0.0 );

    /* Feed this data set forward */
    feed_forward();

    /* Backpropagate the error */
    backpropagate_error( test );

    /* Calculate the current MSE */
    mse = calculate_mse( test );
//     cout<<test<<","<<mse<<endl;
  } while (mse > 0.001);
  
    //cross validation 
  
//  cout<<"processing validation data"<<endl;
  process_input_list("./validation/","validation.txt");
//  cout<<"validation processed, verifying"<<endl;
//  test_image_matrix(26);
//  cout<<"training neural network with cross validation data"<<endl;
  //*
    do {

    // Pick a test at random 
    test = rand_test();

    // Grab input image (with no noise) 
    set_network_inputs( test, 0.0 );

    // Feed this data set forward
    feed_forward();

    // Backpropagate the error 
    backpropagate_error( test );

    // Calculate the current MSE
    mse = calculate_mse( test );
//     cout<<test<<","<<mse<<endl;
  } while (mse > 0.001);
  //*/
  
//  cout<<"cross validation training complete!!"<<endl;
  //test_alphabet(26);

  /* Now, let's test the network with increasing amounts of noise */
  //test = rand_test();
  
/*  
  set_network_inputs( test, 0 );
  
  feed_forward();
  
  for (int j = 0 ; j < INPUT_NEURONS ; j++) {
      if ((j % 14) == 0) printf("\n");
      printf("%d ", (int)inputs[j]);
    }
  printf( "\nOriginal letter is %c\n\n", classifier()+97 );//*/

  //process_input_list("./production/","production.txt");
  
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
  
  noise_prob = 0.5;
  int guess, ans;
  int correct = 0;
  for (int j=0; j<1000; j++){
    
    //for (i = 0 ; i < 5 ; i++) {
      test = rand_test();
      set_network_inputs( test, noise_prob );

      feed_forward();

  /*    
    for (int j = 0 ; j < INPUT_NEURONS ; j++) {
	if ((j % 14) == 0) printf("\n");
	printf("%d ", (int)inputs[j]);
      } //*/

      guess = classifier()+97;
      ans = find_ans(test)+97;
      if(guess == ans) correct++;
      //printf( "\nclassified as %c, supposed to be %c\n\n", guess,ans);

      //noise_prob += 0.05;

    //}
  }
  
  cout<<correct<<endl;

  return 0;
}

