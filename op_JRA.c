#include "op.h"

INITOP("JRA",op_JRA,0)

_SUB int op_JRA(PCTX *ctx)
{

  BIGV stv;

  int tev;
  int tpc;

  stv = READMEM(jctx,ctx->AC);
  CHKERROR(jctx);
  stv >>= 18;
  stv &= RWM;

  tev = stv;

  stv = READMEM(jctx,ctx->AC);
  stv &= RWM;

  tpc = stv;

  stv = READMEM(jctx,tev);
  CHKERROR(jctx);

  WRITEMEM(jctx,ctx->AC,stv);
  CHKERROR(jctx);

  cPC = cE;

  setPCSET;

  return(OK_EXIT);

}
