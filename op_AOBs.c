#include "op.h"

INITOP("AOBJP",op_AOBJP,0)

_SUB int op_AOBJP(PCTX *ctx)
{

  BIGV a;
  
  a = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);
  NORMALIZE(a);

  /* This is the KA10 way of doing this - the other processors add 1
     separately to each half.  This will cause the right half to overflow
     into the left at 777777.  This is also the primary way that one
     determines in assembler what kind of CPU you are running under */
  
  a += 01000001;

  WRITEMEM(jctx, ctx->AC, a);
  CHKERROR(jctx);

  if (!(a & HIGHB)) {
    cPC = cE;
    setPCSET;
    return(OK_EXIT);
  }

  return(OK_EXIT);

}

INITOP("AOBJN",op_AOBJN,0)

_SUB int op_AOBJN(PCTX *ctx)
{

  BIGV a;
  
  a = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);

  NORMALIZE(a);

  /* This is the KA10 way of doing this - the other processors add 1
     separately to each half.  This will cause the right half to overflow
     into the left at 777777.  This is also the primary way that one
     determines in assembler what kind of CPU you are running under */
  
  a += 01000001;

  WRITEMEM(jctx, ctx->AC, a);
  CHKERROR(jctx);

  if ((a & HIGHB)) {
    cPC = cE;
    setPCSET;
    return(OK_EXIT);
  }

  return(OK_EXIT);

}
