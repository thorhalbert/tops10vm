#include "op.h"

INITOP("SUB",op_SUB,0)

_SUB int op_SUB(PCTX *ctx)
{

  BIGV a,b;
  
  a = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);
  NORMALIZE(a);
  b = READMEM(jctx, ctx->E);
  CHKERROR(jctx);
  NORMALIZE(b);

  WRITEMEM(jctx, ctx->AC, a - b);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("SUBI",op_SUBI,0)

_SUB int op_SUBI(PCTX *ctx)
{

  BIGV a,b;

  a = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);

  NORMALIZE(a);
  b = cE;

  WRITEMEM(jctx, ctx->AC, a - b);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("SUBM",op_SUBM,0)

_SUB int op_SUBM(PCTX *ctx)
{

  BIGV a,b;
  
  a = READMEM(jctx, ctx->E);
  CHKERROR(jctx);

  NORMALIZE(a);

  b = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);
  
  NORMALIZE(b);

  WRITEMEM(jctx, ctx->E, b - a);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("SUBB",op_SUBB,0)

_SUB int op_SUBB(PCTX *ctx)
{

  BIGV a,b,c;

  a = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);
  NORMALIZE(a);
  b = READMEM(jctx, ctx->E);
  CHKERROR(jctx);
  NORMALIZE(b);

  c = a - b;

  WRITEMEM(jctx, ctx->E, c);
  CHKERROR(jctx);  
  WRITEMEM(jctx, ctx->AC, c);
  CHKERROR(jctx);

  return(OK_EXIT);

}

