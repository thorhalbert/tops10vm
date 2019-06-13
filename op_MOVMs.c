#include "op.h"

INITOP("MOVM",op_MOVM,0)

_SUB int op_MOVM(PCTX *ctx)
{

  BIGV tv;
  
  tv = READMEM(jctx,ctx->E);
  CHKERROR(jctx);

  tv &= FM;
  if (tv==HIGHB) 
    ctx->pstatus |= SB_AROV | SB_CRY1;

  NORMALIZE(tv);

  if (tv<0) {
    WRITEMEM(jctx,ctx->AC, - tv);
    CHKERROR(jctx);
  }
  else {
    WRITEMEM(jctx,ctx->AC, tv);
    CHKERROR(jctx);
  }

  return(OK_EXIT);

}

INITOP("MOVMI",op_MOVMI,0)

_SUB int op_MOVMI(PCTX *ctx)
{

  WRITEMEM(jctx,ctx->AC, cE);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("MOVMM",op_MOVMM,0)

_SUB int op_MOVMM(PCTX *ctx)
{

  BIGV tv;

  tv = READMEM(jctx,ctx->AC);
  CHKERROR(jctx);

  tv &= FM;
  if (tv==HIGHB) 
    ctx->pstatus |= SB_AROV | SB_CRY1;

  NORMALIZE(tv);

  if (tv<0) {
    WRITEMEM(jctx,ctx->E, - tv);
    CHKERROR(jctx);
  }
  else {
    WRITEMEM(jctx,ctx->E, tv);
    CHKERROR(jctx);
  }

  return(OK_EXIT);

}

INITOP("MOVMS",op_MOVMS,0)

_SUB int op_MOVMS(PCTX *ctx)
{

  BIGV tv;

  tv = READMEM(jctx,ctx->E);
  CHKERROR(jctx);

  tv &= FM;
  if (tv==HIGHB) 
    ctx->pstatus |= SB_AROV | SB_CRY1;

  NORMALIZE(tv);

  if (tv<0) {
    WRITEMEM(jctx,ctx->E, - tv);
    CHKERROR(jctx);
  }
  else {
    WRITEMEM(jctx,ctx->E, tv);
    CHKERROR(jctx);
  }

  if (cAC) {
    BIGV t;
    t = READMEM(jctx,ctx->E);
    CHKERROR(jctx);
    WRITEMEM(jctx,ctx->AC,t);
    CHKERROR(jctx);
  }

  return(OK_EXIT);

}

