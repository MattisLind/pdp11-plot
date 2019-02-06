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


int main (int argc, char * argv[])
{
  int d, last_d=0, i,j=0;
  FILE * hmpFile, * fontFile;
  int ch, state=STATE_ID, cnt=0, len, id;
  char id_str[6], len_str[4], buffer[500];
  int map[3926];
  fc fontarray[96];

  memset(map,-1,sizeof (map));

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
	map[i] = j;
	fontarray[j].fontnum = i;
	j++;
      }
    }
    else {
      //      printf("Read %d\n", d);
      map[d] = j;
      fontarray[j].fontnum = d;
      j++;
    }
    last_d = d;
  }


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
	if (map[id]>-1) {
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
	if (map[id]>-1) {
	  fontarray[map[id]].len = len;
	}
      } else {
	cnt++;
      }
      break;
    case STATE_FONTDATA:
      buffer[cnt]=ch;
      if (cnt < (len*2-1)) {
	cnt++;
      }
      else {
	buffer[len*2]=0;
	state=0;
	cnt=0;
	if (map[id]>-1) {
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
  return 0;
}
