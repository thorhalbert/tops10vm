#include "op.h"

INITOP("EXCH",op_EXCH,0)

_SUB int op_EXCH(PCTX *ctx)
{

  BIGV stv,ste;

  stv = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);

  ste = READMEM(jctx, ctx->E);
  CHKERROR(jctx);

  WRITEMEM(jctx, ctx->AC, ste);
  CHKERROR(jctx);
  WRITEMEM(jctx, ctx->E, stv);
  CHKERROR(jctx);

  return(OK_EXIT);

}

