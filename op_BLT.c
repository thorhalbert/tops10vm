#include "op.h"

INITOP("BLT",op_BLT,0)

// Note from the KHL simulator that there are lots of gotcha's with
// BLT -- we're likely to need lots of iterations to get this right
// First off, we'll just implement as we see it.

_SUB int op_BLT(PCTX *ctx)
{

  BIGV t;
  int srcaddr,dstaddr,finaldest;
  int loopaddr,loopcount;

  t = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);

  srcaddr = (int) LH(t);
  dstaddr = (int) RH(t);

  finaldest = ctx->E;

  loopcount = finaldest - dstaddr;

  for (loopaddr = 0; loopaddr <= loopcount; loopaddr++) { // inclusive
    t = READMEM(jctx, srcaddr + loopaddr);
    CHKERROR(jctx);
    WRITEMEM(jctx, dstaddr + loopaddr, t);
    CHKERROR(jctx);
  }

  return(OK_EXIT);

}
