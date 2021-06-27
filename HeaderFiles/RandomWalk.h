#include <cstdlib>
#include <iostream>
using namespace std;

class Particle {
  public:
    Particle(int xpos, int ypos);
    void getDirection();
    void moveDirection(int x, int y);
  
  private:
    int x;
    int y;
    int dir;
    bool stuck;
}

void getDirection(){
  int dir = 0;
  float rand = (rand()%101)/100;
  if (rand<=.2){
    dir = 0;
  }
  if (rand<=.4){
    dir = 1;
  }
  if (rand<=.6){
    dir = 2;
  }
  if (rand<=.8){
    dir = 3;
  }
  if (rand<=1){
    dir = 4;
  }
}

point moveDirection(){
  x = Particle.xpos;
  y = Particle.ypos;
  if (dir == 0){
    if(x == 0){
       x = 199;
    }
    else(){
      x-=1;
    }
  }
  if (dir == 1){
    x-=1;
    y+=1;
    if (x == -1){
      x = 199;
    }
  }
  if (dir == 2){
    y+=1;
  }
  if (dir == 3){
    x+=1;
    y+=1;
    if(x == 200){
      x = 0;
    }
  }
  if (dir == 4){
    if(x==199){
      x = 0;
    }
    else{
      x+=1;
    }
  }
}

struct Point{
  int xposition = x;
  int yposition = y;
}











