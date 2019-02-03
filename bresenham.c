#ifdef UNIX
#include <stdio.h>
#else 
#include "printf.h"
#endif

#define DRUMDOWN 1<<0
#define DRUMUP   1<<1
#define PENLEFT  1<<2
#define PENRIGHT 1<<3
#define PENUP    1<<5
#define PENDOWN  1<<4
int current_x, current_y;

void zero () {
  current_x = 0;
  current_y = 0;
}
 
void plotCommand(int); 

int abs (int in)
{
  return in<0?-in:in;
}

void penLeft() 
{
  plotCommand(PENLEFT);
}

void penRight() 
{
  plotCommand(PENRIGHT);
}
void drumDown() 
{
  plotCommand(DRUMDOWN);
}
void drumUp() 
{
  plotCommand(DRUMUP);
}

void penDown ()
{
  plotCommand(PENDOWN);
}

void penUp ()
{
  plotCommand(PENUP);
}

void drumUpPenLeft () 
{ 
  plotCommand(PENLEFT | DRUMUP);
} 

void drumDownPenLeft () 
{ 
  plotCommand(PENLEFT | DRUMDOWN);
} 

void drumUpPenRight () 
{ 
  plotCommand(PENRIGHT | DRUMUP);
} 

void drumDownPenRight () 
{ 
  plotCommand(PENRIGHT | DRUMDOWN);
} 

void moveTo(int x,int y)
{
  int dx = abs (x-current_x), sx = (current_x < x)?1:-1;
  int dy = abs (y-current_y), sy = (current_y < y)?1:-1;
  int err = (dx > dy ? dx : - dy)>>1, e2;
  int command;
  #ifdef UNIX
  fprintf(stdout, "move to %d, %d current_x: %d current_y %d dx: %d dy %d sx: %d sy: %d err: %d e2: %d\n", x,y, current_x, current_y, dx, dy, sx, sy, err, e2);
  #else
  //printf("Move to (%d,%d)\r\n",x,y);
  #endif
  while(1) {
  #ifdef UNIX
    fprintf(stdout, "while current_x: %d current_y %d dx: %d dy %d sx: %d sy: %d err: %d e2: %d\n",current_x, current_y, dx, dy, sx, sy, err, e2);
  #endif

    if (current_x == x && current_y == y) {
      break;
    } 
    e2 = err;
    command = 0;
    if (e2>=-dx) {
      err -=dy;
      current_x += sx;
      command |= (sx==1)?PENRIGHT:PENLEFT;
    }
    if (e2<dy) {
      err += dx;
      current_y += sy;
      command |= (sy==1)?DRUMDOWN:DRUMUP;
    }
    plotCommand(command);
  }
} 

