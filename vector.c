#ifdef UNIX
#include <stdio.h>
#else 
#include "printf.h"
#endif


#define AR11_DP_CS    0170410
#define AR11_DP_DX    0170412
#define AR11_DP_DY    0170414

// Use the Erase signal to control the Z-axis.

#define AR11_DP_CS_ERASE       1 << 12


void vectorZero () {
  (*((volatile int *) (AR11_DP_DX))) = 0;
  (*((volatile int *) (AR11_DP_DY))) = 0;
}

void vectorUp ()
{
  *((volatile int *) (AR11_DP_CS)) = AR11_DP_CS_ERASE;
}

void vectorDown ()
{
  *((volatile int *) (AR11_DP_CS)) = 0;
}

void vectorX(int x)
{
  (*((volatile int *) (AR11_DP_DY))) = x;
} 

void vectorY(int y)
{
  (*((volatile int *) (AR11_DP_DY))) = y;
} 

