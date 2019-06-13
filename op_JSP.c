#include "op.h"

INITOP("JSP",op_JSP,0)

_SUB int op_JSP(PCTX *ctx)
{
  BIGV t;

  t = ctx->pstatus;
  t &= SB_MASK;

  //  ctx->pstatus &= ~(SB_AFI | SB_TRAP1 | SB_TRAP2 | SB_FPD);

  t |= cPC + 1;
  WRITEMEM(jctx,ctx->AC,t);
  CHKERROR(jctx);

  cPC = cE;
  setPCSET;

  return(OK_EXIT);

}
