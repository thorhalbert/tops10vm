// Extremely Crude Assembler (ECA) for the PDP-10

#include <stdio.h>

#define PCTX int

#define DEFOPS

#include "../include/opcodelist.h"


main()
{

  int i;

  for (i=0; op_tab[i].op!=0; i++) {
    printf("\tOPDEF %s=%o,%o,%o\n",
	   op_tab[i].onam,
	   op_tab[i].op,
	   op_tab[i].ac,0);
  }

  exit(0);
}
