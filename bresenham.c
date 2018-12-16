#ifdef UNIX
#include <stdio.h>
#endif

#define PENRIGHT 1<<0
#define PENLEFT 1<<1
#define DRUMUP 1<<2
#define DRUMDOWN 1<<3
#define PENUP 1<<5
#define PENDOWN 1<<4
int current_x, current_y;

void plotCommand(int); 

int abs (int in)
{
  return in<0?-in:in;
}


void penDown ()
{
  plotCommand(PENDOWN);
}

void penUp ()
{
  plotCommand(PENUP);
}

void moveTo(int x,int y)
{
  int dx = abs (x-current_x), sx = (current_x < x)?1:-1;
  int dy = abs (y-current_y), sy = (current_y < y)?1:-1;
  int err = (dx > dy ? dx : - dy)>>1, e2;
  int command;
  #ifdef UNIX
  fprintf(stderr, "move to %d, %d\n", x,y);
  #endif 
  while(1) {
    if (current_x == x && current_y == y) {
      break;
    } 
    e2 = err;
    command = 0;
    if (e2>-dx) {
      err -=dy;
      current_x += sx;
      command |= (sx==1)?PENRIGHT:PENLEFT;
    }
    if (e2<dy) {
      err += dx;
      current_y += sy;
      command |= (sy==1)?DRUMUP:DRUMDOWN;
    }
    plotCommand(command);
  }
} 

