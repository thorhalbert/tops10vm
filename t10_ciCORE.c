#include "op.h"

_SUB int t10_CALLI_CORE(PCTX *ctx)
{

  BIGV t;
  int hiseg,loseg;

  // Get the E to check the flags

  t = READMEM(jctx, ctx->E);
  CHKERROR(jctx);

  // Check to see if we got a flags -- assume that it is the UU.PHY
  // flag and give the exit return

  if (t)
    return(OK_EXIT); 

  // Read our args from the AC

  t = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);

  hiseg = (int) LH(t);
  loseg = (int) RH(t);

  // Call the pager to fix the core

  t = adjust_core(jctx,hiseg,loseg, ctx->PC);

  // Error return

  if (t < 0) {
    // Lets assume for now that the AC in unchanged on error
    //WRITEMEM(jctx, ctx->AC, 0);  // Zero the AC and return error 
    return(OK_EXIT);
  }

  // Check for simple check
  // Return core value and *error* return

  if (hiseg==0 && loseg==0) {
    WRITEMEM(jctx, ctx->AC, t);
    return(OK_EXIT);
  }

  // Put the answer, which is sizes in K back onto the AC and skip return

  WRITEMEM(jctx, ctx->AC, t);
  ctx->PC ++;   

  // Need a watch bit for this
  printcore(jctx,0);

  return(OK_EXIT);

}
