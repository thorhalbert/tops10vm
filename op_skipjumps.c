#include "op.h"

INITBOP(0300,0377,op_skipjumps,0)

_SUB int op_skipjumps(PCTX *ctx)
{

  register short iop;
  register char t;

  BIGV imv;
  BIGV cmpt,cmpf;

#define op_CAI 0
#define op_CAM 1
#define op_JUMP 2
#define op_SKIP 3
#define op_AOJ 4
#define op_AOS 5
#define op_SOJ 6
#define op_SOS 7

#define cmp_none 0
#define cmp_L 1
#define cmp_E 2
#define cmp_LE 3
#define cmp_A 4
#define cmp_GE 5
#define cmp_N 6
#define cmp_G 7
  
  iop = ctx->OP;

#define DO_ins (iop&070)>>3
#define DO_cmp (iop&007)

  switch (DO_ins) {
  case op_AOJ:
    imv = READMEM(jctx,ctx->AC);
    CHKERROR(jctx);
    imv &= FM;
    if (imv==(HIGHB-1)) 
      ctx->pstatus |= SB_AROV | SB_CRY1 | SB_TRAP1;
    else
      if (imv==FM)
	ctx->pstatus |= SB_CRY0 | SB_CRY1;
    NORMALIZE(imv);
    imv ++;
    WRITEMEM(jctx,ctx->AC,imv);
    CHKERROR(jctx);
    break;
  case op_AOS:
    imv = READMEM(jctx,ctx->E);
    CHKERROR(jctx);
    imv &= FM;
    if (imv==(HIGHB-1)) 
      ctx->pstatus |= SB_AROV | SB_CRY1 | SB_TRAP1;
    else
      if (imv==FM)
	ctx->pstatus |= SB_CRY0 | SB_CRY1;
    NORMALIZE(imv);
    imv ++;
    WRITEMEM(jctx,ctx->E,imv);
    CHKERROR(jctx);
    if (cAC) {
      WRITEMEM(jctx,ctx->AC,imv);
      CHKERROR(jctx);
    }
    break;
  case op_SOJ:
    imv = READMEM(jctx,ctx->AC);
    CHKERROR(jctx);
    imv &= FM;
    if (imv==HIGHB) 
      ctx->pstatus |= SB_AROV | SB_CRY0 | SB_TRAP1;
    else
      if (imv!=0)
	ctx->pstatus |= SB_CRY0 | SB_CRY1;
    NORMALIZE(imv);
    imv --;
    WRITEMEM(jctx,ctx->AC,imv);
    CHKERROR(jctx);
    break;
  case op_SOS:
    imv = READMEM(jctx,ctx->E);
    CHKERROR(jctx);
    imv &= FM;
    if (imv==HIGHB) 
      ctx->pstatus |= SB_AROV | SB_CRY0 | SB_TRAP1;
    else
      if (imv!=0)
	ctx->pstatus |= SB_CRY0 | SB_CRY1;
    NORMALIZE(imv);
    imv --;
    imv &= FM;
    WRITEMEM(jctx,ctx->E,imv);
    CHKERROR(jctx);
    if (cAC) {
      WRITEMEM(jctx,ctx->AC,imv);
      CHKERROR(jctx);
    }
    break;
  }

  switch (DO_ins) {
  case op_JUMP:
  case op_AOJ:
  case op_SOJ:
    cmpf = READMEM(jctx,ctx->AC);
    CHKERROR(jctx);
    NORMALIZE(cmpf);
    cmpt = 0;
    break;

  case op_CAI:
    cmpf = READMEM(jctx,ctx->AC);
    CHKERROR(jctx);
    NORMALIZE(cmpf);
    cmpt = cE;
    break;
  case op_CAM:
    cmpf = READMEM(jctx,ctx->AC);
    CHKERROR(jctx);
    NORMALIZE(cmpf);
    cmpt = READMEM(jctx,ctx->E);
    CHKERROR(jctx);
    NORMALIZE(cmpt);
    break;

  case op_SKIP:
    cmpf = READMEM(jctx,ctx->E);
    CHKERROR(jctx);
    NORMALIZE(cmpf);
    cmpt = 0;
    if (cAC) {
      WRITEMEM(jctx,ctx->AC,cmpf);
      CHKERROR(jctx);
    }
    break;
  case op_AOS:
  case op_SOS:
    cmpf = READMEM(jctx,ctx->E);
    CHKERROR(jctx);
    NORMALIZE(cmpf);
    cmpt = 0;
    break;
  }

  t = 0;
  switch(DO_cmp) {
  case cmp_none:
    t = 0;
    break;
  case cmp_A:
    t = 1;
    break; 
 case cmp_L:
    if (cmpf < cmpt) t = 1;
    break;
  case cmp_E:
    if (cmpf == cmpt) t = 1;
    break;
  case cmp_LE:
    if (cmpf <= cmpt) t = 1;
    break;
  case cmp_GE:
    if (cmpf >= cmpt) t = 1;
    break;
  case cmp_N:
    if (cmpf != cmpt) t = 1;
    break;
  case cmp_G:
    if (cmpf > cmpt) t = 1;
    break;
  }

  if (t) {
    switch (DO_ins) {
    case op_JUMP:
    case op_AOJ:
    case op_SOJ:
      cPC = cE;
      setPCSET;
      break;
    case op_CAI:
    case op_CAM:
    case op_SKIP:
    case op_AOS:
    case op_SOS:
      cPC += 2;
      setPCSET;
      break;
    }
  }

  return(OK_EXIT);

}
