#include "op.h"

INITBOP(0600,0677,op_bittest,0)

_SUB int op_bittest(PCTX *ctx)
{

  register short iop;

#define what_R 0
#define what_L 1
#define what_D 2
#define what_S 3

#define mod_N 0
#define mod_Z 1
#define mod_C 2
#define mod_O 3

#define skip_nev 0
#define skip_E 1
#define skip_A 2
#define skip_N 3

  BIGV imask,tvl;

  iop = ctx->OP;

#define DO_tskip (iop&007)>>1
#define DO_tmod (iop&070)>>4
#define DO_twhat (iop&010)>>2 | (iop&001)

  switch (DO_twhat) {
  case what_R:
    imask = cE;
    break;
  case what_L:
    imask = cE;
    imask <<= 18;
    break;
  case what_D:
    imask = READMEM(jctx,ctx->E);
    CHKERROR(jctx);
    break;
  case what_S:
    imask = READMEM(jctx,ctx->E);
    CHKERROR(jctx);
    imask &= RWM;
    imask <<= 18;
    tvl = READMEM(jctx,ctx->E);
    CHKERROR(jctx);
    tvl >>= 18;
    tvl &= RWM;
    imask |= tvl;
    break;
  }

  switch(DO_tskip) {
  case skip_nev:
    break;
  case skip_N:
    if (READMEM(jctx,ctx->AC) & imask) {
    CHKERROR(jctx);
      cPC += 2;
      setPCSET;
    }
    break;
  case skip_E:
    if ((READMEM(jctx,ctx->AC) & imask)==0) {
    CHKERROR(jctx);
      cPC += 2;
      setPCSET;
    }
    break;
  case skip_A:
    cPC += 2;
    setPCSET;
    break;
  }

  switch(DO_tmod) {
  case mod_N:
    break;
  case mod_Z:
    tvl = READMEM(jctx, ctx->AC);
    CHKERROR(jctx);
    tvl &= (~imask);
    WRITEMEM(jctx, ctx->AC, tvl);
    CHKERROR(jctx);
    break;
  case mod_O:
    tvl = READMEM(jctx, ctx->AC);
    CHKERROR(jctx);
    tvl |= imask;
    WRITEMEM(jctx, ctx->AC, tvl);
    CHKERROR(jctx);
    break;
  case mod_C:
    tvl = READMEM(jctx, ctx->AC);
    CHKERROR(jctx);
    tvl ^= imask;
    WRITEMEM(jctx, ctx->AC, tvl);
    CHKERROR(jctx);
    break;
  }

  return(OK_EXIT);

}
