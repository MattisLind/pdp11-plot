

void penUp();
void penDown();
void moveTo(int, int);


int main ()
{
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
