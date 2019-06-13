#include "op.h"

INITOP("MOVE",op_MOVE,0)

_SUB int op_MOVE(PCTX *ctx)
{
  BIGV t;

  t = READMEM(jctx, ctx->E);
  CHKERROR(jctx);
  WRITEMEM(jctx, ctx->AC, t);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("MOVEI",op_MOVEI,0)

_SUB int op_MOVEI(PCTX *ctx)
{

  WRITEMEM(jctx, ctx->AC, cE);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("MOVEM",op_MOVEM,0)

_SUB int op_MOVEM(PCTX *ctx)
{
  BIGV t;

  t = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);
  WRITEMEM(jctx, ctx->E, t);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("MOVES",op_MOVES,0)

_SUB int op_MOVES(PCTX *ctx)
{
  BIGV t;

  if (cAC) {
    t = READMEM(jctx, ctx->E);
    CHKERROR(jctx);
    WRITEMEM(jctx, ctx->AC, t);
    CHKERROR(jctx);
  }

  return(OK_EXIT);

}

