#include <stdio.h>

int main () {
  int ch, i=0;
  fprintf (stdout, "char plotdata[] = {");
  ch = getchar();
  if (!feof(stdin)) {
    fprintf(stdout, "0x%02X",ch);
  }
  else {
    return 0;
  }
  do {
    ch=getchar();
    if (ch != EOF) {
      fprintf (stdout, ",");
    } else {
      break;
    }
    if (i==15) { 
      fprintf(stdout, "\n                   ");
      i=0;
    } else {
      i++;
    }
    if (ch != EOF) {
      fprintf (stdout, "0x%02X",ch);
    }
  } while (1);
  fprintf (stdout, "};\n");
  return 0;
}
