
#include "TekFastGraphicsFiles/File03.h"

void penUp();
void penDown();
void moveTo(int, int);
void enablePlotterInterrupt();
void disablePlotterInterrupt();

int main () 
{
  int a,b,c,x,y,i=0;
  do {
    a = plotdata[i];
    b = plotdata[i+1];
    c = plotdata[i+2];
    x = (0x38 & a) << 4 | 0x7f & b;
    y = (0x07 & b) << 7 | 0x7f & c;
    if (0x40 & a) {
      penUp();
    } else {
      penDown();
    }
    moveTo(x,y);
    if (i==(sizeof(plotdata)-1)) {
      break;
    }
  } while(1);
  return 0;
}

/*
int test1 ()
{
  disablePlotterInterrupt();
  int t=0, lastt=0, sign=0,i;
  penDown();
  for (i=100;i>=0;i-=2) {
    t += sign?-i:i; 
    sign = ~sign;
    moveTo(t, lastt);
    lastt=t;
    moveTo(t, lastt);
  }
  penUp();
  return 0;
}
*/
