#include "op.h"

_SUB int t10_CALLI_RESET(PCTX *ctx)
{

  // RESET has nothing interesting to do yet.  Just return

  // Non-Error return

  ctx->PC ++;

  return(OK_EXIT);

}

_SUB int t10_CALLI_EXIT(PCTX *ctx)
{

  // We have no ability to CONTINUE, so we don't
  // really need to honor the exit function types yet
  // until we have a real command scanner

  return(OK_EXITJOB);  // Exit silently

}

_SUB int t10_CALLI_SLEEP(PCTX *ctx)
{

  int sl;

  sl = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);

  sleep(sl);

  return(OK_EXIT); 

}
