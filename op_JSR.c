#include "op.h"

INITOP("JSR",op_JSR,0)

_SUB int op_JSR(PCTX *ctx)
{

  BIGV stv;

  stv = ctx->pstatus;
  stv &= SB_MASK;

  ctx->pstatus &= ~(SB_AFI | SB_TRAP1 | SB_TRAP2 | SB_FPD);

  stv |= cPC + 1;

  WRITEMEM(jctx,ctx->E,stv);
  CHKERROR(jctx);

  cPC = cE + 1;
  setPCSET;

  return(OK_EXIT);

}
