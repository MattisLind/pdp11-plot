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


#ifndef UNIX
#define CONSOLE_RXCS 0177560
#define CONSOLE_RXDB 0177562
#define CONSOLE_TXCS 0177564
#define CONSOLE_TXDB 0177566

#define SWR 0177570

void putch (void * p, char c) {
  while ( * ((volatile int *) (CONSOLE_TXCS)) != 0200) {
    //wait
  }
  *( (volatile int *) (CONSOLE_TXDB)) = c;
}

int getch () {
  while ( * ((volatile int *) (CONSOLE_RXCS)) != 0200) {
    //wait
  }
  return *( (volatile int *) (CONSOLE_TXDB));
}

void getline (char * buf, int maxlen) {
  int ch, i=0;
  do {
    ch = getch();
    if (ch == '\n') break;
    if (ch == '\r') break;
    buf[i]=ch;
    i++;
    putch(NULL, ch);
    if (i==maxlen) break;
  } while (1);
  buf[i]=0;
  printf("\r\n");
}

int readSWR () {
  return *( (volatile int *) (SWR));
}

#endif

int plotHersheyChar(char ch, int x, int y, int scale) {


}

plotHersheyLine(char * nuf, int x, int y, int scale) {
  int i, last_x=x;
  char ch;
  while((ch=buf[i]) != 0) {
    last_x = plotHersheyChar(ch, last_x, y, scale);
  }
}

#define MAXLEN 60
#define LINE_HEIGHT 16;

int main () 
{
  char buf[MAXLEN+1];
  int y;
  #ifndef UNIX
  init_printf((void *) 0, putch);
  #endif
  zero();
  do {
    scale = readSWR();
    printf("HERSHEY-PRINTER> ")
    getline(buf,MAXLEN);
    plotHersheyLine(buf,0, y, scale);
    y+=(LINHEIGHT<<scale);
  } while ();
  return 0;
}

