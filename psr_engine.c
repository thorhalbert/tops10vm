#include <stdio.h>

#include "psr.h"

#include "opcodelist.h"

int inst=0;

BIGV ret_pc_status(PCTX *ctx)
{

  BIGV t;

  t = ctx->pstatus;
  t &= SB_MASK;

  t |= ctx->PC;

  return(t);

}

void dumppsrvals(BIGV ins)
{

  if (ins & SB_AROV) printf(" AROV");
  if (ins & SB_CRY0) printf(" CRY0");
  if (ins & SB_CRY1) printf(" CRY1");
  if (ins & SB_FOV) printf(" FOV");
  if (ins & SB_FPD) printf(" FPD");
  if (ins & SB_USER) printf(" USER");
  if (ins & SB_IOT) printf(" IOT");
  if (ins & SB_PUBL) printf(" PUBL");
  if (ins & SB_AFI) printf(" AFI");
  if (ins & SB_TRAP2) printf(" TRAP2");
  if (ins & SB_TRAP1) printf(" TRAP1");
  if (ins & SB_FXU) printf(" FXU");
  if (ins & SB_DCK) printf(" DCK");
}

void dumppstat(PCTX *ctx)
{
  printf("PC=%o Flags=",ctx->PC);
  dumppsrvals(ctx->pstatus);
  printf("\n");
}

void dumpac(PCTX *ctx)
{

  int i;

  printf("\n");
  dumppstat(ctx);

  printf("\n");

  for (i=0; i<16; i++) {
    BIGV tc;    
    tc = READMEM(jctx, i);
    if (tc)
      printf("%o/ %o,,%o\n", 
	     i,
	     (int) LH(tc),
	     (int) RH(tc));
  }
}

#define BSIZE 100
char exebuf[BSIZE][200];
int cbuf=0,ctot=0;
int exebufon=1;

void postmortemdump(PCTX *ctx)
{



}

int exec_word(PCTX *ctx,int inE)
{

  BIGV t,nxv,PreE;
  int ib,in,ma,ad,E;
  int rsts;
  char buf1[120],buf2[120];

  // Normal increment

  ctx->PCSET=0;

  ctx->xct_depth ++;
  if (ctx->xct_depth > MAXXCT) {
    printf("\n\n%o/ XCT depth exceeds recursion max (%d)\n",
	   ctx->PC,
	   MAXXCT);
    ctx->PSTAT = PSTAT_HALTED;
    return(10);
  }

  ma = inE;

  nxv = READMEM(jctx, ma);
  CHKERROR(jctx);

  ctx->exins = nxv;

  t = nxv;
  t &= OPM;
  t >>= OPS;
  ctx->OP = t;
  t = nxv;
  t &= ACM;
  t >>= ACS;
  ctx->AC = t;

  // Turn on the debug flag if this op is being debugged - pass to op handler

  if (ctx->debugop) 
    ctx->debugthisop = ((master_xbar[ctx->OP].pflag & DEBUGOP)!=0);
  if (ctx->debugthisop)
    dumppstat(ctx);
    
  if (master_xbar[ctx->OP].pflag & NOOPE) {  // No-Op - no effective address
    if (exebufon) {
      sprintf(buf2,"%06o/ %03o %02o %01o %02o %06o ",
	      ctx->PC,
	      ctx->OP,
	      ctx->AC,
	      ib,in,ad);
      sprintf(buf1," %-6s %2o,   [NOOPE]",
	      master_xbar[ctx->OP].onam,ctx->AC);
      strcat(buf2,buf1);
      strcpy(exebuf[cbuf],buf2);
      if (ctx->TRACE>TRACE_NONE)
	printf("%s\n",buf2);
      cbuf = (cbuf + 1) % BSIZE;
      ctot++;
    }

    if (ctx->PCSET==0)
      ctx->PC ++;
    ctx->xct_depth --;
    return(0);
  }

  t = nxv;
  t &= RWM;
  ad = t;
  t = nxv;
  t &= IBM;
  t >>= IBS;
  ctx->IB = ib = t;
  t = nxv;
  t &= INM;
  t >>= INS;
  ctx->IN = in = t;

  if (exebufon)
    sprintf(buf2,"%06o/ %03o %02o %01o %02o %06o ",
	 ctx->PC,
	 ctx->OP,
	 ctx->AC,
	 ib,in,ad);

  // Compute effective address 
  // Will need segmented Effective address calculator

  while (1) {

    t = nxv;
    t &= RWM;
    ad = t;
    t = nxv;
    t &= IBM;
    t >>= IBS;
    ib = t;
    t = nxv;
    t &= INM;
    t >>= INS;
    in = t;

    PreE = ad;

    // Perform indexing 

    if (in) {
      PreE += READMEM(jctx,in);
      CHKERROR(jctx);
    }

    // Segment truncation - E will always be & RWM

    E = (int) RH(PreE);

    // Rest of loop does indirect bit

    if (ib==0) break;

    ma = E;

    nxv = READMEM(jctx,ma);
    CHKERROR(jctx);
  }

  ctx->PreE = PreE;
  ctx->E = E;

  // Dump AC

  if (exebufon && ctx->TRACE==TRACE_WIDE) {
    BIGV rv;
    rv = READMEM(jctx,ctx->AC);
    if (jctx->memerror == MEM_NONERROR)
      sprintf(buf1," (ac=%02o/ %6o,,%-6o) ", 
	      ctx->AC,
	      (int) LH(rv),
	      (int) RH(rv));
    else
      sprintf(buf1,"                         "); 
    CLRERROR(jctx);

    strcat(buf2,buf1);
  }

  // Dump E if in range

  if (exebufon) {
    BIGV rv;
    rv = READMEM(jctx,E);
    if (jctx->memerror == MEM_NONERROR)
      sprintf(buf1," (e=%06o/ %6o,,%-6o) ", 
	      E,
	      (int) LH(rv),
	      (int) RH(rv));
    else
      sprintf(buf1," (e=%06o                ) ", E);
    CLRERROR(jctx);

    strcat(buf2,buf1);
  }

  if (master_xbar[ctx->OP].pflag & NOOP) {  // No-Op
    if (exebufon) {
      sprintf(buf2,"%06o/ %03o %02o %01o %02o %06o ",
	      ctx->PC,
	      ctx->OP,
	      ctx->AC,
	      ib,in,ad);
      sprintf(buf1," %-6s %2o,   [NOOP]",
	      master_xbar[ctx->OP].onam,ctx->AC);
      strcat(buf2,buf1);
      strcpy(exebuf[cbuf],buf2);
      if (ctx->TRACE>TRACE_NONE)
	printf("%s\n",buf2);
      cbuf = (cbuf + 1) % BSIZE;
      ctot++;
    }
    if (ctx->PCSET==0)
      ctx->PC ++;
    ctx->xct_depth --;
    return(0);
  }

  if (master_xbar[ctx->OP].pfun) {
    ctx->PCSET = 0;
    if (exebufon) {
      sprintf(buf1," %-6s %2o,",
	      master_xbar[ctx->OP].onam,ctx->AC);
      strcat(buf2,buf1);
      strcpy(exebuf[cbuf],buf2);
      if (ctx->TRACE>TRACE_NONE)
	printf("%s\n",buf2);
      cbuf = (cbuf + 1) % BSIZE;
      ctot++;
    }

    // Clear any existing memory errors 

    CLRERROR(jctx);

    // Execute the instruction 

    rsts = master_xbar[ctx->OP].pfun(ctx);

    if (ctx->debugthisop)
      dumppstat(ctx);

    // See if memory fault after operating

    if (jctx->memerror!=MEM_NONERROR) {
      printf("\n\n?TV10EM - Memory Error %d - ",jctx->memerror);
      switch(jctx->memerror) {
      case MEM_WRITE_NONPAGE:
	printf("Write attempt to non-existant page");
	break;
      case MEM_READ_NONPAGE:
	printf("Read attempt to non-existant page");
	break;
      case MEM_WRITE_WLPAGE:
	printf("Write attempt against write-locked page");
	break;
      case MEM_READ_CONCEAL:
	printf("Read against a concealed page");
	break;
      case MEM_PAGE_EXISTS:
	printf("Attempt to create already existing page");
	break;
      case MEM_PAGE_NONEXIST:
	printf("Access to non-existant page");
	break;
      }

      printf(" at PC %06o\n",ctx->PC);
      dumpac(ctx);
      ctx->PSTAT = PSTAT_HALTED;

      ctx->xct_depth --;
      return(0);
    }

    switch(rsts) {
    case OK_EXITJOB:
      // Silenly return
      ctx->PSTAT = PSTAT_HALTED;
      return(0);
    case OK_HALTPROC:
      printf("\n?TV10EM - HALT at user PC %06o\n",ctx->PC);
      ctx->PSTAT = PSTAT_HALTED;
      return(0);
    case OK_EXIT:  
    case OK_PSTAT:
    case OK_PFLAG:
      master_xbar[ctx->OP].hits ++;
      inst++;
      break;
    case OK_MUUO:  /* Must implement USER mode *UUO traps for these */
    case OK_LUUO:
    case OK_UUO:
    default:
      printf("\n?TV10EM - Illegal opcode %o",
	     ctx->OP);
      if (master_xbar[ctx->OP].onam) 
	printf(" - (%s)",master_xbar[ctx->OP].onam); 
      printf(" at PC %06o\n",ctx->PC);
      dumpac(ctx);
      ctx->PSTAT = PSTAT_HALTED;

      ctx->xct_depth --;
      return(0);
    }

    if (ctx->PCSET==0)
      ctx->PC ++;
    ctx->xct_depth --;
    return(0);
  }

  printf("\n?TV10EM - Unimplemented opcode %o", ctx->OP);
  if (master_xbar[ctx->OP].onam) 
    printf(" - (%s)",master_xbar[ctx->OP].onam);
  printf(" at PC %06o\n",ctx->PC);
  dumpac(ctx);
  ctx->PSTAT = PSTAT_HALTED;

  ctx->xct_depth --;

  return(0);

}

int start_processor(PCTX *inctx,int transferaddr)
{

  int err;

  inctx->PC = transferaddr;     // Where to start
  inctx->PSTAT = PSTAT_RUNNING; // Fire up the processor

  while(inctx->PSTAT==PSTAT_RUNNING) {
    err = exec_word(inctx,inctx->PC);
    if (err) return(err);
  }
 
  return(0);
}
