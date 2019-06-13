#include <stdio.h>
#include <string.h>

#include "psr.h"
#include "t10vm.h"

int read36unix(FILE *iniov, int fmt, int count, BIGV *retarr)
{

  int lh;
  int rh;
  BIGV blv;

  int ret,i,j;

  if (feof(iniov)) return(0);
  if (ferror(iniov)) return(0);

  switch (fmt) {
  case INT_FILEFMT_ASC:
    ret = 0;

    for (i=0; i<count; i++) {

      j = fscanf(iniov,"%o,,%o",&lh,&rh);
      if (j!=2) 
	return(ret);

      blv = lh & RWM;
      blv <<= 18;
      blv |= rh & RWM;

      retarr[ret++] = blv;
    }

    return(ret);

    break;
    //  case INT_FILEFMT_B36:
    //    break;
    //  case INT_FILEFMT_UNIX:
    //    break;
  default:
    printf("?T10_IO - UNIX 36 Format %d Unknown or Unimplimented\n",fmt);
    exit(100);
  }
}
