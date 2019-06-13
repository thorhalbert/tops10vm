#include "op.h"

INITOP("IMUL",op_IMUL,0)

_SUB int op_IMUL(PCTX *ctx)
{

  BIGV a,b;
  
  a = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);
  NORMALIZE(a);

  b = READMEM(jctx, ctx->E);
  CHKERROR(jctx);
  NORMALIZE(b);

  WRITEMEM(jctx, ctx->AC, a * b);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("IMULI",op_IMULI,0)

_SUB int op_IMULI(PCTX *ctx)
{

  BIGV a,b;

  a = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);
  NORMALIZE(a);
  b = cE;

  WRITEMEM(jctx, ctx->AC, a * b);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("IMULM",op_IMULM,0)

_SUB int op_IMULM(PCTX *ctx)
{

  BIGV a,b;
  
  a = READMEM(jctx, ctx->E);
  CHKERROR(jctx);
  NORMALIZE(a);

  b = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);
  NORMALIZE(b);

  WRITEMEM(jctx, ctx->E, a * b);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("IMULB",op_IMULB,0)

_SUB int op_IMULB(PCTX *ctx)
{

  BIGV a,b,c;

  a = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);
  NORMALIZE(a);

  b = READMEM(jctx, ctx->E);
  CHKERROR(jctx);
  NORMALIZE(b);

  c = a * b;
  WRITEMEM(jctx, ctx->E, c);
  CHKERROR(jctx);
  WRITEMEM(jctx, ctx->AC, c);
  CHKERROR(jctx);

  return(OK_EXIT);

}

