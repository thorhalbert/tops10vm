#include "op.h"

void exec_word(PCTX *ctx,int inE);

INITBOP(0000,0037,op_luuos,0)

#define dJBUUO 040  // Store instruction
#define dJB41 041   // Execute instruction

// Completely different operation in non-segment-zero

_SUB int op_luuos(PCTX *ctx)
{

  BIGV t,e;

  t = READMEM(jctx, dJB41);
  CHKERROR(jctx);

  if (t==0) {
    printf("?OP_LUUO: Untrapped LUUO at PC %06o\n", ctx->PC);
    cPSTAT = PSTAT_HALTED;
    return(OK_PSTAT);
  }

  t = READMEM(jctx, ctx->PC);
  CHKERROR(jctx);

  t &= 0777740000000ULL;  // Strip the addressing off
  e = cE;
  e &= 0000000777777ULL;  // Strip off 

  t |= e;

  WRITEMEM(jctx, dJBUUO, t);
  CHKERROR(jctx);

  exec_word(ctx, dJB41);

  setPCSET;  /* Fake into not incrementing the PC - XCT is probably a jump */

  return(OK_EXIT);

}
