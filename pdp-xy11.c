#define PLOTTER_CS 0172554
#define PLOTTER_DB 0172556

void plotCommand(int command) 
{
  while ( * ((volatile int *) (PLOTTER_CS)) != 0x80) {
    //wait
  }
  *( (volatile int *) (PLOTTER_DB)) = command;
}
