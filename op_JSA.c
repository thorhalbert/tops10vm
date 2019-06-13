#include "op.h"

INITOP("JSA",op_JSA,0)

_SUB int op_JSA(PCTX *ctx)
{

  BIGV stv;

  stv = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);
  WRITEMEM(jctx, ctx->E, stv);
  CHKERROR(jctx);

  stv = cE;
  stv <<= 18;
  stv |= (cPC + 1) & RWM;
  stv &= FM;

  WRITEMEM(jctx, ctx->AC, stv);
  CHKERROR(jctx);

  cPC = cE + 1;
  setPCSET;

  return(OK_EXIT);

}
