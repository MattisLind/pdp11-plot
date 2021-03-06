#include <stdio.h>
#include <string.h>
#include <stdlib.h>     /* strtol */
#define STATE_ID 0
#define STATE_LEN 1
#define STATE_FONTDATA 2


struct fontchar { 
  int len;
  int fontnum;
};

typedef struct fontchar fc;

char buf[512];


char * escapeString (char * in) {
  int j=0, i;
  for (i=0; i<strlen(in); i++) {
    switch(in[i]) {
      case '\\':
        buf[j++] = '\\';
	buf[j++] = '\\';
      break;
      case '\"':
        buf[j++] = '\\';
	buf[j++] = '\"';
      break;
      default:
	buf[j++] = in[i];
      break;
    }
  }
  buf[j] = 0;
  return buf;
}

int find (int fontnum, fc * fontarray) {
  int i=0;
  while (i < 96) {
    if(fontarray[i].fontnum == fontnum) return i;
    i++;
  }
  return -1;
}


void update(int fontnum, int len, fc * fontarray) {
  int i=0;
  while (i < 96) {
    if(fontarray[i].fontnum == fontnum) fontarray[i].len = len;
    i++;
  }
}


int main (int argc, char * argv[])
{


  int d, last_d=0, i,j=0, maxy=0, miny=0;
  FILE * hmpFile, * fontFile;
  int ch, state=STATE_ID, cnt=0, len, id;
  char id_str[6], len_str[4], buffer[500];
  fc fontarray[96];
  int asciinum;


  if (argc != 3) {
    fprintf(stderr, "Wrong number of arguments.\n");
  }

  hmpFile = fopen (argv[1], "r");
  if (hmpFile == NULL) {
    fprintf (stderr, "Could not open file: %s. \n", argv[1]);
  }

  fontFile = fopen (argv[2], "r");
  if (fontFile == NULL) {
    fprintf (stderr, "Could not open file: %s. \n", argv[2]);
  }


  while((EOF!=fscanf (hmpFile, "%d", &d))) {
    if (d<0) {
      // range                                                                                                                                                                                   
      for (i=last_d + 1; i <= -d; i++) {
	//        printf("Read %d\n", i);
	fontarray[j].fontnum = i;
	j++;
      }
    }
    else {
      //      printf("Read %d\n", d);
      fontarray[j].fontnum = d;
      j++;
    }
    last_d = d;
  }
  i=0;

  while ((ch = fgetc(fontFile))!= EOF){
    if (ch=='\n') continue;
    switch (state) {
    case STATE_ID: 
      id_str[cnt]=ch;
      if (cnt==4) {
	id_str[5]=0;
	state=STATE_LEN;
	cnt=0;
	id = atoi(id_str);
	if (find(id, fontarray)>-1) {
	  printf("char fontchar_%d[]=\"", id);
	}
      }
      else {
	cnt++;
      }
      break;
    case STATE_LEN:
      len_str[cnt]=ch;
      if (cnt==2) {
	state = STATE_FONTDATA;
	len_str[3]=0;
	cnt = 0;
	len = atoi(len_str);
	update (id, len, fontarray);
      } else {
	cnt++;
      }
      break;
    case STATE_FONTDATA:
      buffer[cnt]=ch;
      if ((cnt>2) && (cnt&1) && (find(id, fontarray)>-1))  {
	int y = ch - 'R';
	if (y > maxy) {
	  maxy = y;
	}
	if (y < miny) {
	  miny = y;
	}
      }
      if (cnt < (len*2-1)) {
	cnt++;
      }
      else {
	buffer[len*2]=0;
	state=0;
	cnt=0;
	if (find(id, fontarray)>-1) {
	  printf("%s\";\n",escapeString(buffer));
	}
      }
      break;
    }
  }

  printf("typedef struct fc { int len; char * fontchar; } fontchar;\nfontchar font[] = {");
  for (i=0; i<12; i++) {
    fprintf(stdout, "{%d, fontchar_%d}", fontarray[i*8].len, fontarray[i*8].fontnum); 
    for (j=1; j<8; j++) {
      fprintf(stdout, ", {%d, fontchar_%d}", fontarray[i*8+j].len, fontarray[i*8+j].fontnum); 
    }
    if (i<11) {
      fprintf(stdout, ",\n                  ");
    }
  }
  printf("};\n");
  printf("#define MAXY %d\n#define MINY %d\n", maxy, miny);
  return 0;
}
