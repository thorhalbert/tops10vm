#include "op.h"

INITOP("MOVS",op_MOVS,0)

_SUB int op_MOVS(PCTX *ctx)
{

  BIGV t;
  t = SWAPLR(READMEM(jctx, ctx->E));
  CHKERROR(jctx);
  WRITEMEM(jctx, ctx->AC, t);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("MOVSI",op_MOVSI,0)

_SUB int op_MOVSI(PCTX *ctx)
{

  WRITEMEM(jctx, ctx->AC, SWAPLR(cE));
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("MOVSM",op_MOVSM,0)

_SUB int op_MOVSM(PCTX *ctx)
{

  BIGV t;

  t = SWAPLR(READMEM(jctx, ctx->AC));
  CHKERROR(jctx);
  WRITEMEM(jctx, ctx->E, t);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("MOVSS",op_MOVSS,0)

_SUB int op_MOVSS(PCTX *ctx)
{

  BIGV t;

  t = SWAPLR(READMEM(jctx, ctx->E));
  CHKERROR(jctx);
  WRITEMEM(jctx, ctx->E, t);
  CHKERROR(jctx);

  if (cAC) {
    WRITEMEM(jctx, ctx->AC, t);
    CHKERROR(jctx);
  }

  return(OK_EXIT);

}

