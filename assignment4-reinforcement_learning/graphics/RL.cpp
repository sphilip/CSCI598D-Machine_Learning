#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <vector>
#include <stdio.h>

using namespace std;

const int width = 5;
const int height = 5;

struct twoInt {
    int x;
    int y;
};

void halt(){ while ( getchar() != '\n'); } //equivalent of system("Pause")

void initalizeTable(double table[][width]){
  for(int i=0; i<height; i++)
   for(int j=0; j<width; j++)
     table[i][j]=0;
}

void printTable(double table[][width]){
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++)
      printf("%1.2f  ",table[i][j]);
    cout<<endl;
  }
}

vector<twoInt> traverse(){
  vector<twoInt> path;// = new vector<twoInt>();
  int Xo = rand()%width;
  int Yo = rand()%height;
  int paths = 5;//rand()%30;
  int GoX,add;
  twoInt val;
  
  for(int i=0; i<paths; i++){
    GoX = rand()%2;
    add = rand()%2;
    if(GoX) {
      if((add && Xo < width-1) || (Xo<1)) Xo++;
      else Xo--;
    }
    else {
      if((add && Yo < height-1) || (Yo<1)) Yo++;
      else Yo--;
    }
    val.x = Xo;
    val.y = Yo;
    path.push_back(val);
  }
  return path;
}

double findMax(double q[][width],int x, int y){
  double max = q[x][y];
  if(x-1>=0) max = q[x-1][y] > max ? q[x-1][y] : max;
  if(x+1<width) max = q[x+1][y] > max ? q[x+1][y] : max;
  if(y-1>=0) max = q[x][y-1] > max ? q[x][y-1] : max;
  if(y+1<=height) max = q[x][y+1] > max ? q[x][y+1] : max;
  return max;
}

void update(vector<twoInt> path, double q[][width], double r[][width]){
  double n = 0.9; //learning rate
  
  int x,y;
  
  //cout<<"Path taken:"<<endl;
  for(int i=1; i<path.size(); i++){ //loop through vector, dont update last cell
    //cout << path[i].x << "," << path[i].y << endl;
    int x = path[i].x;
    int y = path[i].y;
    double max = findMax(q,x,y);
    
    double update = r[x][y] + n * max;
    update = update > 1 ? 1 : update;
    
    //cout << "prevVal: " << max << "\t update: " << update <<endl;
    
    if(update > q[x][y]) q[x][y] = update;
  }
}

void generateCompleteTable(double rewardsTable[][width], double copy[][width]){
  for(int i=0; i<1000; i++)
   update(traverse(), copy, rewardsTable);
}

double checkCompleteness(double final[][width], double q[][width]){
  double percent=0;
  for(int i=0; i<height; i++)
   for(int j=0; j<width; j++)
     percent+=q[i][j]/final[i][j];
   percent=percent/(width*height);
  //cout << "percent complete: " << percent <<endl;
   return percent;
}

int main(int argc, char *argv[]){
 double qTable[height][width];
 double rewardsTable[height][width];
 
 srand((unsigned)time(0)); 
 
 initalizeTable(qTable);
 initalizeTable(rewardsTable);
 
 for(int i=0; i<width; i++){
   rewardsTable[height/2][i]=1;
 }
 cout<<"Inital Q-Table:\n";
 printTable(qTable);
 
 cout<<"\n\n\n Rewards Table:\n"; 
 printTable(rewardsTable);
 
 //halt();
 
 int trials = atoi(argv[1]);
 
 double final[height][width];
 initalizeTable(final);
 generateCompleteTable(rewardsTable, final);
 cout<<"Final table: \n";
 printTable(final);
 //halt();
 
 double percent=0;
 int runs = 100000;
 for(int h=0; h<runs; h++){
   initalizeTable(qTable);
  for(int i=0; i<trials; i++){
    update(traverse(), qTable, rewardsTable);
    //cout<<"\n\nTrial: "<<i+1<<endl; printTable(qTable);
  }
  percent += checkCompleteness(final,qTable);
 }
 percent /= runs;
 cout << "average completness: " << percent<<endl;
 return 0;
}