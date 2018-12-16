#include <stdio.h>

void enablePlotterInterrupt() {
}

void disablePlotterInterrupt() {
} 

void plotCommand(int command) {
  fprintf(stdout, "Command: %d \n", command);
}
