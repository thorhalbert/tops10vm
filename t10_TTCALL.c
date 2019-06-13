#include "op.h"

// Output a single ascii character 

_SUB int t10_TTCALL_OUTCHR(PCTX *ctx)
{

  BIGV CN;
  int op;

  CN = READMEM(jctx, ctx->E);
  CHKERROR(jctx);

  op = CN;
  op &= 0177;  // 7 bits only

  putchar(op);

  return(OK_EXIT);
}

// Output an asciz string

_SUB int t10_TTCALL_OUTSTR(PCTX *ctx)
{

  BIGV CN;
  char ob[5];
  int addr,ex;

  for (addr=cE; ; addr++) {
    int j;

    CN = READMEM(jctx, addr);
    CHKERROR(jctx);

    CN >>= 1;  // Move off that spare bit

    for (j=0; j<5; j++) {
      ob[4-j] = CN & 0177;
      CN >>= 7;
    }

    ex = 0;
    for (j=0; j<5; j++) {
      if (ob[j]==0) {
	ex = 1;
	break;
      }
      //printf("%c - %d\n",ob[j],ob[j]);
      putchar(ob[j]);
    }
    if (ex) break;
  }      
  
  return(OK_EXIT);
}

_SUB int t10_TTCALL(PCTX *ctx)
{

  char *ttfun;

  switch(ctx->AC) {
  case 00: ttfun="INCHRW"; break;
  case 01: return(t10_TTCALL_OUTCHR(ctx));
  case 02: ttfun="INCHRS"; break;
  case 03: return(t10_TTCALL_OUTSTR(ctx));
  case 04: ttfun="INCHWL"; break;
  case 05: ttfun="INCHSL"; break;
  case 06: ttfun="GETLCH"; break;
  case 07: ttfun="SETLCH"; break;
  case 010: ttfun="RESCAN"; break;
  case 011: ttfun="CLRBFI"; break;
  case 012: ttfun="CLRBFO"; break;
  case 013: ttfun="SKPINC"; break;
  case 014: ttfun="SKPINL"; break;
  case 015: ttfun="IONEOU"; break;
  }

  printf("?T10_TTCALL - Terminal Op %s called at PC %06o\n",ttfun,ctx->PC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);

}
