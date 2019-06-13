#include "op.h"

BIGV adder(PCTX *ctx,BIGV a, BIGV b)
{

  BIGV t;

  t = a + b;

  if (a<0 && b<0) 
    ctx->pstatus |= SB_CRY0 | SB_CRY1;

  if ((a<0 && b>0) ||
      (a>0 && b<0)) {
    int at,bt;

    if (a<0) 
      at = -a;
    else
      at = a;
    if (b<0) 
      bt = -b;
    else
      bt = b;

    if (bt==at) 
      ctx->pstatus |= SB_CRY0 | SB_CRY1;

    if (a>0) {
      if (at>bt)
	ctx->pstatus |= SB_CRY0 | SB_CRY1;
    } else {
      if (bt>at)
	ctx->pstatus |= SB_CRY0 | SB_CRY1;
    }
  }
  
  if (t>0) {
    if (t&BITOVER) { /* We overflowed */
      ctx->pstatus |= (SB_AROV | SB_CRY1 | SB_TRAP1);
      //printf("ADDER OVERFLOW\n");
    }
    return(t);
  }

  if (t<0) {
    if (!(t&BITOVER)) { /* We underflowed */
      ctx->pstatus |= (SB_AROV | SB_CRY0 | SB_TRAP1);
      //printf("ADDER UNDERFLOW\n");
    }
    return(t);
  }

  return(t);

}

INITOP("ADD",op_ADD,0)

_SUB int op_ADD(PCTX *ctx)
{

  BIGV a,b;
  
  a = READMEM(jctx,ctx->AC);
  CHKERROR(jctx);

  NORMALIZE(a);

  b = READMEM(jctx,ctx->E);
  NORMALIZE(b);

  WRITEMEM(jctx,ctx->AC,adder(ctx,a,b));
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("ADDI",op_ADDI,0)

_SUB int op_ADDI(PCTX *ctx)
{

  BIGV a,b;

  a = READMEM(jctx,ctx->AC);
  CHKERROR(jctx);

  NORMALIZE(a);
  b = cE;

  WRITEMEM(jctx,ctx->AC,adder(ctx,a,b));

  return(OK_EXIT);

}

INITOP("ADDM",op_ADDM,0)

_SUB int op_ADDM(PCTX *ctx)
{

  BIGV a,b;
  
  a = READMEM(jctx,ctx->E);
  CHKERROR(jctx);
  NORMALIZE(a);

  b = READMEM(jctx,ctx->AC);
  CHKERROR(jctx);
  NORMALIZE(b);

  WRITEMEM(jctx,ctx->E,adder(ctx,a,b));
  CHKERROR(jctx);

  return(OK_EXIT);

}

#if 0
_SUB int op_ADDS(PCTX *ctx)
{

  BIGV a,b,c;

  a = READMEM(jctx,ctx->AC);
  CHKERROR(jctx);
  NORMALIZE(a);

  b = READMEM(jctx,ctx->E);
  CHKERROR(jctx);
  NORMALIZE(b);

  c = adder(ctx,a,b);
  WRITEMEM(jctx,ctx->E,c);
  CHKERROR(jctx);
  WRITEMEM(jctx,ctx->AC,c);
  CHKERROR(jctx);

  return(OK_EXIT);

}
#endif

INITOP("ADDB",op_ADDB,0)

_SUB int op_ADDB(PCTX *ctx)
{

  BIGV a,b,c;
  
  a = READMEM(jctx,ctx->E);
  CHKERROR(jctx);
  NORMALIZE(a);

  b = READMEM(jctx,ctx->AC);
  CHKERROR(jctx);
  NORMALIZE(b);

  c = adder(ctx,a,b);
  WRITEMEM(jctx,ctx->E,c);
  CHKERROR(jctx);
  WRITEMEM(jctx,ctx->AC,c);
  CHKERROR(jctx);

  return(OK_EXIT);

}
