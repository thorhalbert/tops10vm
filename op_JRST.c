#include "op.h"

extern MEMLOC *main_core;

#define JRSTF_DEBUG

INITOP("JRST",op_JRST,0)

_SUB int op_JRST(PCTX *ctx)
{

  BIGV ssts;
  char *jrstn;

  int mode_user;
  int mode_iot;
  
  mode_user=ctx->pstatus & SB_USER;
  mode_iot=ctx->pstatus & SB_IOT;

  switch(cAC) {
  case 001: /* PORTAL */
    // For now, everything is in user mode -- Just treat as a JRST
    cPC = cE;
    setPCSET;
    return(OK_EXIT);
  case 000: /* JRST */
    cPC = cE;
    setPCSET;
    return(OK_EXIT);
  case 004: /* HALT */
    return(OK_HALTPROC);  // Just halt VM for now with ?HALT message
    if (!(mode_user && mode_iot)) 
      return(OK_MUUO);
    cPC = cE;
    setPCSET;
    cPSTAT = PSTAT_HALTED;
    dumpac(ctx);
    return(OK_PSTAT);
  case 002: /* JRSTF */
    if (ctx->debugthisop) {
      printf("Before JRSTF: ");
      dumppstat(ctx);
    }
    ssts = ctx->pstatus;
    if (ctx->IB || ctx->IN) {
      ssts = ctx->PreE & SB_MASK;
      CHKERROR(jctx);
      if (ctx->debugthisop) {
	printf("Set bits %06o\n",(int)LH(ssts));
	dumppsrvals(ssts);
	printf(" into PSR bits %06o",(int)LH(ctx->pstatus));
	dumppsrvals(ctx->pstatus); 
	printf("\n");
      }
    }
    switch (ctx->PMODE) {
    case CT_KA:
      ssts &= ~(SB_PUBL|SB_AFI|SB_TRAP1|SB_TRAP2);  /* KA doesn't have these */
      break;
    case CT_KS:
      ssts &= ~(SB_PUBL);  /* KS doesn't have public/concealed mode either */
      break;
    default:
      break;
    }
    if (mode_user) { /* Are we in user mode or exec */
      ssts |= SB_USER;  /* User can't clear USER mode */
      if (!(mode_iot)) /* User I/O set? */
	ssts &= ~SB_IOT;  /* User can't set IO mode, but can clear it */
    }
      
    ctx->pstatus = ssts;
    if (ctx->debugthisop) {
      printf("After JRSTF: ");
      dumppstat(ctx);
    }
    cPC = cE;  /* Might have a bug here -- when exec sets user mode on
		  a KA - this effective address might be in the user's 
		  space - we'll know when user/exec stuff starts happening */
    setPCSET;
    return(OK_EXIT);
  }

  switch (cAC) {
  case 001: jrstn="PORTAL"; break; /* PORTAL */
  case 005: jrstn="XJRSTF"; break; /* XJRSTF */ /* MUUO in USER mode */
  case 006: jrstn="XJEN"; break; /* XJEN */ /* MUUO in USER mode */
  case 007: jrstn="XPCW"; break; /* XPCW */ /* MUUO in USER mode */
  case 012: jrstn="JEN"; break; /* JEN */ /* MUUO in USER mode */
  case 017: jrstn="SFM"; break; /* SFM */
  default:
    jrstn="Unknown";
  }

  printf("?OP_JRST: Unimplemented JRST %o - %s at PC %06o\n",
	 cAC, jrstn, ctx->PC);
  cPSTAT = PSTAT_HALTED;
  dumpac(ctx);
  return(OK_PSTAT);

}
