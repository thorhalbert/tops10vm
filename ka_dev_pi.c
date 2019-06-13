#include "ioop.h"

_SUB int ka_dev_pi(PCTX *ctx, int dev, int op)
{

  BIGV inv;

  switch(op) {
  case IO_DATAO:
    inv = READMEM(jctx,ctx->E);
    CHKERROR(jctx);
    printf("LIGHTS=(%6o,,%-6o)\n", 
	   (int) LH(inv),
	   (int) RH(inv));
    return(OK_EXIT);
  }

  printf("ka_dev_pi(%o %o)\n",dev,op);

  return(OK_EXIT);

}
