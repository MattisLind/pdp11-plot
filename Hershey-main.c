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


#ifdef UNIX
#include <stdio.h>

int puts (const char * str) {
  printf("%s", str);
  return 0;
}

void getlin (char * buf, int maxlen) {
  fgets(buf, maxlen, stdin);
}

int readSWR () {
  return 0;
}




#else

#include "printf.h"

#define CONSOLE_RXCS 0177560
#define CONSOLE_RXDB 0177562
#define CONSOLE_TXCS 0177564
#define CONSOLE_TXDB 0177566

#define SWR 0177570

void putch (char c) {
  while ( * ((volatile int *) (CONSOLE_TXCS)) != 0200) {
    //wait
  }
  *( (volatile int *) (CONSOLE_TXDB)) = c;
}

int getch () {
  while ( * ((volatile int *) (CONSOLE_RXCS)) != 0200) {
    //wait
  }
  return *( (volatile int *) (CONSOLE_RXDB));
}

int puts (const char * str) {
  char ch;
  while ((ch=*str++)) {
    putch(ch);
  }
}

void getlin (char * buf, int maxlen) {
  int ch, i=0;
  do {
    ch = getch();
    if (ch == '\n') break;
    if (ch == '\r') break;
    buf[i]=ch;
    i++;
    putch(ch);
    if (i==maxlen) break;
  } while (1);
  buf[i]=0;
  puts("\r\n");
}

int readSWR () {
  return *( (volatile int *) (SWR));
}

void print_putch (void * dummy, char ch) {
  putch(ch);
}

#define printf tfp_printf

#endif

int plotHersheyChar(char ch, int x, int y, int scale) {
  if ((ch<32) || (ch>127)) return x;
  int len = font[ch-0x20].len<<1;
  char * fontchar = font[ch-0x20].fontchar;
  int left = (fontchar[0]-'R') << scale;
  int right = (fontchar[1]-'R') << scale;
  x = x - left; // left is negative
  penUp();
  for (int i=2; i<len; i+=2) {
    int xrel = (((int) (fontchar[i] - 'R')) << scale);
    int yrel = (((int) (fontchar[i+1] - 'R')) << scale);
    //printf("xrel=%d, yrel=%d\n", xrel, yrel);
    if (fontchar[i]==' ' && fontchar[i+1]=='R') {
      penUp();
    } else {
      moveTo(x+xrel, y-yrel);
      penDown();
    }
  }
  return x+right;
}

void plotHersheyLine(char * buf, int x, int y, int scale) {
  int i, last_x=x;
  char ch;
  while((ch=buf[i++]) != 0) {
    //printf("Now plotting %c, last_x=%d, y=%d, scale=%d\n",ch, last_x, y, scale); 
    last_x = plotHersheyChar(ch, last_x, y, scale);
    //printf("last_x=%d\n", last_x);
    last_x += (1 << scale);
  }
  penUp();
}

#define MAXLEN 60
#define LINE_HEIGHT ((MAXY)-(MINY))

int main () 
{
  char buf[MAXLEN+1];
  int y=0, scale;
  #ifndef UNIX
  //init_printf((void *) 0, print_putch);
  #endif
  zero();
  do {
    puts("HERSHEY-PRINTER> ");
    getlin(buf,MAXLEN);
    scale = readSWR()&0x7;
    plotHersheyLine(buf,0, y, scale);
    y-=(LINE_HEIGHT<<scale);
  } while (1);
  return 0;
}

