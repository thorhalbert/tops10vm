#include "op.h"

INITBOP(0400,0477,op_bitops,0)

_SUB int op_bitops(PCTX *ctx)
{

  register short iop;
  BIGV inv;

  iop = ctx->OP;

#define DO_majop (iop&0774)
#define DO_memop (iop&0003)

#define op_SETZ 0400
#define op_SETO 0474
#define op_SETCA 0450
#define op_SETCM 0460
#define op_SETM 0414
#define op_SETA 0424

#define op_AND 0404
#define op_ANDCA 0410
#define op_ANDCM 0420
#define op_ANDCB 0440

#define op_OR 0434
#define op_ORCA 0454
#define op_ORCM 0464
#define op_ORCB 0470

#define op_EQV 0444
#define op_XOR 0430

#define mem_basic 0
#define mem_imm 1
#define mem_mem 2
#define mem_both 3

  switch(DO_memop) {
  case mem_imm:
    inv = cE;
    break;
  case mem_basic:
  case mem_mem:
  case mem_both:
    inv = READMEM(jctx, ctx->E);
    CHKERROR(jctx);
    break;
  }

  switch(DO_majop) {
  case op_SETZ:
    inv = 0;
    break;
  case op_SETO:
    inv = ~0;
    break;
  case op_SETCA:
    inv = ~READMEM(jctx,ctx->AC);
    CHKERROR(jctx);
    break;
  case op_SETCM:
    inv = ~inv;
    break;
  case op_SETM:
    break;
  case op_SETA:
    inv = READMEM(jctx,ctx->AC);
    CHKERROR(jctx);
    break;
  case op_AND:
    inv &= READMEM(jctx,ctx->AC);
    CHKERROR(jctx);
    break;
  case op_ANDCA:
    inv = inv & (~READMEM(jctx,ctx->AC));
    CHKERROR(jctx);
    break;
  case op_ANDCM:
    inv = READMEM(jctx,ctx->AC) & (~inv);
    CHKERROR(jctx);
    break;
  case op_ANDCB:
    inv = (~READMEM(jctx,ctx->AC)) & (~inv);
    CHKERROR(jctx);
    break;
  case op_OR:
    inv |= READMEM(jctx,ctx->AC);
    CHKERROR(jctx);
    break;
  case op_ORCA:
    inv = inv | (~READMEM(jctx,ctx->AC));
    CHKERROR(jctx);
    break;
  case op_ORCM:
    inv = READMEM(jctx,ctx->AC) | (~inv);
    CHKERROR(jctx);
    break;
  case op_ORCB:
    inv = (~inv) | (~READMEM(jctx,ctx->AC));
    CHKERROR(jctx);
    break;
  case op_EQV:
    inv = ~ (inv ^ READMEM(jctx,ctx->AC));
    CHKERROR(jctx);
    break;
  case op_XOR:
    inv ^= READMEM(jctx,ctx->AC);
    CHKERROR(jctx);
    break;
  }

  switch(DO_memop) {
  case mem_basic:
  case mem_imm:
    WRITEMEM(jctx,ctx->AC,inv);
    CHKERROR(jctx);
    break;
  case mem_mem:
    WRITEMEM(jctx,ctx->E,inv);
    CHKERROR(jctx);
    break;
  case mem_both:
    WRITEMEM(jctx,ctx->AC,inv);
    CHKERROR(jctx);
    WRITEMEM(jctx,ctx->E,inv);
    CHKERROR(jctx);
    break;
  }

  return(OK_EXIT);

}
