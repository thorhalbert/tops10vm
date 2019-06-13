#include "op.h"

INITOP("MOVN",op_MOVN,0)

_SUB int op_MOVN(PCTX *ctx)
{

  BIGV tv;
  
  tv = READMEM(jctx,ctx->E);
  tv &= FM;
  if (tv==HIGHB) 
    ctx->pstatus |= SB_AROV | SB_CRY1;

  NORMALIZE(tv);

  if (tv==0) 
    ctx->pstatus |= SB_CRY0 | SB_CRY1;

  WRITEMEM(jctx,ctx->AC,- tv);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("MOVNI",op_MOVNI,0)

_SUB int op_MOVNI(PCTX *ctx)
{

  BIGV tv;

  tv = cE;
  tv &= FM;
  if (tv==HIGHB) 
    ctx->pstatus |= SB_AROV | SB_CRY1;

  if (tv==0) 
    ctx->pstatus |= SB_CRY0 | SB_CRY1;

  WRITEMEM(jctx,ctx->AC, -tv);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("MOVNM",op_MOVNM,0)

_SUB int op_MOVNM(PCTX *ctx)
{

  BIGV tv;

  tv = READMEM(jctx,ctx->AC);
  CHKERROR(jctx);

  tv &= FM;
  if (tv==HIGHB) 
    ctx->pstatus |= SB_AROV | SB_CRY1;

  if (tv==0) 
    ctx->pstatus |= SB_CRY0 | SB_CRY1;

  WRITEMEM(jctx,ctx->E,-tv);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("MOVNS",op_MOVNS,0)

_SUB int op_MOVNS(PCTX *ctx)
{

  BIGV tv,t;

  tv = READMEM(jctx,ctx->E);
  CHKERROR(jctx);

  tv &= FM;
  if (tv==HIGHB) 
    ctx->pstatus |= SB_AROV | SB_CRY1;

  NORMALIZE(tv);

  if (tv==0) 
    ctx->pstatus |= SB_CRY0 | SB_CRY1;

  t = -tv;
  
  WRITEMEM(jctx,ctx->E,t);
  CHKERROR(jctx);

  if (cAC) {
    WRITEMEM(jctx,ctx->AC,t);
    CHKERROR(jctx);
  }

  return(OK_EXIT);

}

