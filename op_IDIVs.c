#include "op.h"

INITOP("IDIV",op_IDIV,1)

_SUB int op_IDIV(PCTX *ctx)
{

  BIGV a,b;
  
  a = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);

  NORMALIZE(a);
  b = READMEM(jctx, ctx->E);
  CHKERROR(jctx);

  NORMALIZE(b);

  WRITEMEM(jctx, ctx->AC, a / b);
  CHKERROR(jctx);
  if (ctx->AC<15) {  // What happens on the PDP?
    WRITEMEM(jctx, ctx->AC+1, a % b);
    CHKERROR(jctx);
  }

  return(OK_EXIT);

}

INITOP("IDIVI",op_IDIVI,0)

_SUB int op_IDIVI(PCTX *ctx)
{

  BIGV a,b;

  a = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);

  NORMALIZE(a);
  b = cE;

  WRITEMEM(jctx, ctx->AC, a / b);
  CHKERROR(jctx);
  if (ctx->AC<15) {  // What happens on the PDP?
    WRITEMEM(jctx, ctx->AC+1, a % b);
    CHKERROR(jctx);
  }

  return(OK_EXIT);

}

INITOP("IDIVM",op_IDIVM,0)

_SUB int op_IDIVM(PCTX *ctx)
{

  BIGV a,b;
  
  a = READMEM(jctx,ctx->E);
  CHKERROR(jctx);
  NORMALIZE(a);

  b = READMEM(jctx,ctx->AC);
  CHKERROR(jctx);
  NORMALIZE(b);

  WRITEMEM(jctx, ctx->E, a / b);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("IDIVB",op_IDIVB,0)

_SUB int op_IDIVB(PCTX *ctx)
{

  BIGV a,b,c;

  a = READMEM(jctx,ctx->AC);
  CHKERROR(jctx);
  NORMALIZE(a);

  b = READMEM(jctx,ctx->E);
  CHKERROR(jctx);
  NORMALIZE(b);

  c = a / b;
  WRITEMEM(jctx, ctx->E, c);
  CHKERROR(jctx);
  WRITEMEM(jctx, ctx->AC, c);
  CHKERROR(jctx);
  if (ctx->AC<15) {  // What happens on the PDP?
    WRITEMEM(jctx, ctx->AC+1, a % b);
    CHKERROR(jctx);
  }

  return(OK_EXIT);

}

