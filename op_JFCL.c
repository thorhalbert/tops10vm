#include "op.h"

INITOP("JFCL",op_JFCL,0)

_SUB int op_JFCL(PCTX *ctx)
{

  char any=0;

  if (ctx->AC==0) return(OK_EXIT);  // Canonical NO-OP

  if (ctx->debugthisop) {
    printf("Before JFCL: ");
    dumppstat(ctx);
  }
    
  if (cAC&010)
    if (ctx->pstatus & SB_AROV) {
      any = 1;
      ctx->pstatus &= ~SB_AROV;
    }
  if (cAC&004)
    if (ctx->pstatus & SB_CRY0) {
      any = 1;
      ctx->pstatus &= ~SB_CRY0;
    }
  if (cAC&002)
    if (ctx->pstatus & SB_CRY1) {
      any = 1;
      ctx->pstatus &= ~SB_CRY1;
    }
  if (cAC&001)
    if (ctx->pstatus & SB_FOV) {
      any = 1;
      ctx->pstatus &= ~SB_FOV;
    }

  ctx->pstatus &= SB_MASK;

  if (ctx->debugthisop) {
    printf("After JFCL: ");
    dumppstat(ctx);
  }

  if (any) {
    cPC = cE;
    setPCSET;
  }

  return(OK_EXIT);

}
