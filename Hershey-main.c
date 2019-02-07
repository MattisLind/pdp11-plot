//#include "printf.h"
//#define PLOTFILE_H "TekFastGraphicsFiles/TekBug.h"
#include PLOTFILE_H

void penUp();
void penDown();
void penLeft();
void penRight();
void drumDown();
void drumUp();
void drumUpPenLeft (); 
void drumDownPenLeft (); 
void drumUpPenRight (); 
void drumDownPenRight (); 
void moveTo(int, int);
void enablePlotterInterrupt();
void disablePlotterInterrupt();
void zero();
/*
int main() {
  int i;
  penDown();
  for (i=0;i<300;i++) {
    penRight();
  }
  for (i=0;i<300;i++) {
    drumDown();
  }
  for (i=0;i<300;i++) {
    penLeft();
  }
  for (i=0;i<300;i++) {
    drumUp();
  }
  penUp();
  for (i=0;i<100;i++) {
    penRight();
  }
  penDown();
  for (i=0;i<300;i++) {
    drumDownPenRight();
  }
  for (i=0;i<200;i++) {
    drumUpPenLeft();
    drumUp();
  }
  for (i=0;i<100;i++) {
    drumDownPenRight();
    drumDown();
    drumDown();
    drumDownPenRight();
    drumDown();
  }
  penUp();
  return 0;
}
*/


/*int main () 
{
  zero();
  penDown();
  moveTo(200,0);
  moveTo(200,200);
  moveTo(0,200);
  moveTo(0,0);
  penUp();
  moveTo(300,300);
  penDown();
  moveTo(600,150);
  moveTo(450,300);
  moveTo(700,350);
  moveTo(800,0);
  penUp();
  return 0;
}

*/

#ifndef UNIX
#define CONSOLE_TXCS 0177564
#define CONSOLE_TXDB 0177566

void putch (void * p, char c) {
  while ( * ((volatile int *) (CONSOLE_TXCS)) != 0200) {
    //wait
  }
  *( (volatile int *) (CONSOLE_TXDB)) = c;
}
#endif


int main () 
{
  int a,b,c,x,y,i=0,t,u,r,s;
  #ifndef UNIX
  //init_printf((void *) 0, putch);
  #endif
  zero();
  do {
    a = plotdata[i] & 0x7f;
    i++;
    b = plotdata[i] & 0x7f;
    i++;
    c = plotdata[i] & 0x7f;
    i++;
    t = 0x38 & a;
    u = 0x07 & a;
    r = t << 4;
    s = u << 7;
    x = r | b;
    y = s | c;
    //    printf("A=%02X B=%02X C=%02X T=%02X U=%02X r=%03X s=%03X X=%03X X=%d Y=%03X Y=%d",a,b,c,t,r,s,u,x,x,y,y);
    if (0x40 & a) {
      penUp();
      //printf (" UP\r\n");
    } else {
      penDown();
      //printf (" DOWN\r\n");
    }
    moveTo(x,y);
  } while(i<sizeof(plotdata));
  penUp();
  moveTo(0,0);
  return 0;
}

/*
int main ()
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

 /*
int main ()
{
  int i;
  penDown();
  zero();
  for (i=0;i<600;i+=8) {
    moveTo(i,200);
    moveTo(i+4,200);
    moveTo(0,0);
  }
  penUp();
  return 0;
}
 */
