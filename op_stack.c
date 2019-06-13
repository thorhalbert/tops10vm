#include "op.h"

INITOP("PUSHJ",op_PUSHJ,0)

     /*

     PUSHJ
     Increment left and right half
     if left half becomes zero, set PDL overflow and trap
     Put the PSR flags in LH and PC in RH of @RH-AC
     Jump to E

     */

     _SUB int op_PUSHJ(PCTX *ctx)
{

  BIGV t;
  BIGV pdlcount,pdladdr;
  BIGV stv;

  stv = ctx->pstatus;
  stv &= SB_MASK;

  //  ctx->pstatus &= ~(SB_AFI | SB_TRAP1 | SB_TRAP2 | SB_FPD);

  stv |= cPC + 1;

  t = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);

  pdlcount = LH(t);
  NORMALIZE_RH(pdlcount);    // Typically negative - do sign extension
  pdladdr =  RH(t);
  //  NORMALIZE_RH(pdladdr); // This an address - normally positive and unsigned

  if (ctx->debugthisop)
    printf("PUSHJ AC=%o,,%o\n",(int) pdlcount,(int) pdladdr);

  // Increment
  // Note that KA does an add of 1,,1 instead of each half
  // Need to accurately emulate values

  pdladdr ++;
  pdlcount ++;
  pdlcount += (int) (pdladdr>>18); // Need carry bit 
  pdladdr &= 0777777;
  pdlcount &= 0777777;  // 020402 - Forgot to mask this

  if (ctx->debugthisop)
    printf("PUSHJ AC=%o,,%o\n",(int) pdlcount,(int) pdladdr);

  t = pdlcount & 0777777;
  t <<= 18;
  t |= pdladdr & 0777777;

  WRITEMEM(jctx,ctx->AC,t);
  CHKERROR(jctx);
  
  // Look for stack overflow - Set Pushdown Overflow on KA
  // Set trap2 on KI

  // Undocumented - PUSHJ always unsets the BIS flag (KA only?)

  ctx->pstatus &= ~SB_BIS;

  if (pdlcount >= 0) {
    ctx->pstatus |= SB_TRAP2;
    if (ctx->debugthisop)
      printf("PUSHJ - set trap\n");
  }

  WRITEMEM(jctx,pdladdr,stv);
  CHKERROR(jctx);

  // Jump to effective address

  cPC = cE;
  setPCSET;
  return(OK_EXIT);

}

INITOP("PUSH",op_PUSH,0)

     /*

     PUSH
     Increment left and right half
     if left half becomes zero, set PDL overflow and trap
     Put the contents of E into @RH-AC

     */

     _SUB int op_PUSH(PCTX *ctx)
{

  BIGV t;
  int pdlcount,pdladdr;

  t = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);

  pdlcount = (int) LH(t);
  NORMALIZE_RH(pdlcount);    // Typically negative - do sign extension
  pdladdr = (int) RH(t);
  //  NORMALIZE_RH(pdladdr); // This an address - normally positive and unsigned

  if (ctx->debugthisop)
    printf("PUSH AC=%o,,%o\n",pdlcount,pdladdr);

  // Increment
  // Note that KA does an add of 1,,1 instead of each half
  // Need to accurately emulate values

  pdladdr ++;
  pdlcount ++;
  pdlcount += (int) (pdladdr>>18); // Need carry bit 
  pdladdr &= 0777777;
  pdlcount &= 0777777;  // 020402 - Forgot to mask this

  if (ctx->debugthisop)
    printf("PUSH AC=count=%o,,addr=%o\n",pdlcount,pdladdr);

  t = pdlcount & 0777777;
  t <<= 18;
  t |= pdladdr & 0777777;

  WRITEMEM(jctx,ctx->AC,t);
  CHKERROR(jctx);
  
  // Look for stack overflow - Set Pushdown Overflow on KA
  // Set trap2 on KI

  if (pdlcount == 0) {  // Appearently no trap if > 0
    ctx->pstatus |= SB_TRAP2;   // KI/KL response -- need proper KA resp
    if (ctx->debugthisop)
      printf("PUSH - set trap\n");
    return(OK_PSTAT);
  }

  t = READMEM(jctx, ctx->E);
  CHKERROR(jctx);

  WRITEMEM(jctx,pdladdr,t);
  CHKERROR(jctx);

  return(OK_EXIT);

}

INITOP("POP",op_POP,0)

     /*

     POP
     Increment left and right half
     if left half becomes zero, set PDL overflow and trap
     Put the contents of E into @RH-AC

     */

     _SUB int op_POP(PCTX *ctx)
{

  BIGV t,u;
  int pdlcount,pdladdr;

  // cnAC --> E

  t = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);

  u = READMEM(jctx, RH(t));
  CHKERROR(jctx);

  WRITEMEM(jctx, ctx->E, u);
  CHKERROR(jctx);

  pdlcount = (int) LH(t);
  NORMALIZE_RH(pdlcount);    // Typically negative - do sign extension
  pdladdr = (int) RH(t);
  NORMALIZE_RH(pdladdr); // This an address - normally positive and unsigned

  if (ctx->debugthisop)
    printf("POP AC=%o,,%o\n",pdlcount,pdladdr);

  // Decrement
  // Note that KA does an add of 1,,1 instead of each half
  // Need to accurately emulate values

  pdlcount --;
  pdladdr --;

  NORMALIZE_RH(pdlcount); 
  NORMALIZE_RH(pdladdr); 
  
  if (pdladdr== -1)   // Carry
    pdlcount --;

  if (ctx->debugthisop)
    printf("POP AC=%o,,%o\n",pdlcount,pdladdr);

  t = pdlcount & 0777777;
  t <<= 18;
  t |= pdladdr & 0777777;

  WRITEMEM(jctx,ctx->AC,t);
  CHKERROR(jctx);
  
  // Look for stack overflow - Set Pushdown Overflow on KA
  // Set trap2 on KI

  if (pdlcount == -1) {  // Appearently no trap if > 0
    ctx->pstatus |= SB_TRAP2;   // KI/KL response -- need proper KA resp
    if (ctx->debugthisop)
      printf("POP - set trap\n");
    return(OK_PSTAT);
  }

  return(OK_EXIT);

}

INITOP("POPJ",op_POPJ,0)

     /*

     POPJ
     Increment left and right half
     if left half becomes zero, set PDL overflow and trap
     Put the PSR flags in LH and PC in RH of @RH-AC
     Jump to E

     */

     _SUB int op_POPJ(PCTX *ctx)
{

  BIGV t;
  BIGV pdlcount,pdladdr,stackp;
  BIGV stv;

  t = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);

  pdlcount = LH(t);
  NORMALIZE_RH(pdlcount);    // Typically negative - do sign extension
  stackp = pdladdr = RH(t);
  NORMALIZE_RH(pdladdr); // This an address - normally positive and unsigned

  if (ctx->debugthisop)
    printf("POPJ AC=%o,,%o\n",(int) pdlcount,(int) pdladdr);

  // Increment
  // Note that KA does an add of 1,,1 instead of each half
  // Need to accurately emulate values

  pdlcount --;
  pdladdr --;

  NORMALIZE_RH(pdlcount); 
  NORMALIZE_RH(pdladdr); 
  
  if (pdladdr== -1)   // Carry
    pdlcount --;

  if (ctx->debugthisop)
    printf("POPJ AC=%o,,%o\n",(int) pdlcount,(int) pdladdr);

  t = pdlcount & 0777777;
  t <<= 18;
  t |= pdladdr & 0777777;

  WRITEMEM(jctx,ctx->AC,t);
  CHKERROR(jctx);
  
  // Look for stack overflow - Set Pushdown Overflow on KA
  // Set trap2 on KI

  if (pdlcount == -1) {
    ctx->pstatus |= SB_TRAP2;
    if (ctx->debugthisop)
      printf("POPJ - Set trap\n");
    return(OK_PSTAT);
  }

  // Jump to address on stack

  t = READMEM(jctx, (int) stackp);
  CHKERROR(jctx);
  cPC = t & 0777777;

  if (ctx->debugthisop)
    printf("New PC from %o is %o\n",(int) t,(int) stackp);

  setPCSET;        // Don't increment
  return(OK_EXIT);

}

