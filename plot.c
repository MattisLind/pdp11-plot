

#define PENRIGHT 1<<0
#define PENLEFT 1<<1
#define DRUMUP 1<<2
#define DRUMDOWN 1<<3
#define PENUP 1<<4
#define PENDOWN 1<<5
#define PLOTTER_CS 0172554
#define PLOTTER_DB 0172556
int current_x, current_y;


int abs (int in)
{
  return in<0?-in:in;
}

void plotCommand(int command) 
{
  while ( * ((volatile int *) (PLOTTER_CS)) != 0x80) {
    //wait
  }
  *( (volatile int *) (PLOTTER_DB)) = command;
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


int main ()
{
  int t=0, lastt=0, sign=1,i;
  penDown();
  for (i=100;i>=0;i-=2) {
    t += sign?-sign:sign; 
    sign ^= sign;
    moveTo(t, lastt);
    lastt=t;
    moveTo(t, lastt);
  }
  penUp();
  return 0;
}
