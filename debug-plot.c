#include <stdio.h>
#define DRUMDOWN 1<<0
#define DRUMUP   1<<1
#define PENLEFT  1<<2
#define PENRIGHT 1<<3
#define PENUP    1<<5
#define PENDOWN  1<<4

void enablePlotterInterrupt() {
}

void disablePlotterInterrupt() {
} 

void plotCommand(int command) {
  if (command & DRUMDOWN) {
    fprintf(stdout, "DRUMDOWN ");
  } 
  if (command & DRUMUP) {
    fprintf(stdout, "DRUMUP ");
  } 
  if (command & PENLEFT) {
    fprintf(stdout, "PENLEFT ");
  } 
  if (command & PENRIGHT) {
    fprintf(stdout, "PENRIGHT");
  } 
  if (command & PENUP) {
    fprintf(stdout, "PENUP ");
  } 
  if (command & PENDOWN) {
    fprintf(stdout, "PENDOWN");
  } 
  fprintf(stdout, "\n");
}
