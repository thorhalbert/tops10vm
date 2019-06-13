#include "op.h"

INITBOP(0500,0577,op_halfword,0)

_SUB int op_halfword(PCTX *ctx)
{

  register short iop;

#define from_L1 0
#define from_R1 1
#define from_R2 2
#define from_L2 3

#define to_L 0
#define to_R 1

#define mod_none 0
#define mod_Z 1
#define mod_O 2
#define mod_E 3

#define mem_mem 0
#define mem_I 1
#define mem_M 2
#define mem_S 3

  int lw,rw;
  char put_left,set_accum,set_effw;
  BIGV t,u;

  iop = ctx->OP;

#define DO_tfrom (iop&040)>>4 |(iop&004)>>2
#define DO_tto (iop&040)>>5
#define DO_tmod (iop&030)>>3
#define DO_tmem (iop&003)

  lw = rw = 0;
  put_left = 1;
  set_accum = 0;
  set_effw = 0;

  switch (DO_tfrom) {
  case from_R1:
  case from_R2:
    switch (DO_tmem) {
    case mem_mem:
      rw = RH(READMEM(jctx,ctx->E));
      CHKERROR(jctx);
      lw = 0;
      put_left = 0;
      break;
    case mem_I:
      rw = RH(cE);
      lw = 0;
      put_left = 1;
      break;
    case mem_M:
      rw = RH(READMEM(jctx,ctx->AC));
      CHKERROR(jctx);
      lw = 0;
      set_effw = 1;
      put_left = 1;
      break;
    case mem_S:
      rw = RH(READMEM(jctx,ctx->E));
      CHKERROR(jctx);
      lw = 0;
      set_effw = 1;
      set_accum = 1;
      put_left = 1;
      break;
    }
    break;
  case from_L1:
  case from_L2:
    switch (DO_tmem) {
    case mem_mem:
      rw = LH(READMEM(jctx, ctx->E));
      CHKERROR(jctx);
      lw = 0;
      put_left = 0;
      break;
    case mem_I:
      rw = 0;
      lw = 0;
      put_left = 1;
      break;
    case mem_M:
      rw = LH(READMEM(jctx,ctx->AC));
      CHKERROR(jctx);
      lw = 0;
      set_effw = 1;
      put_left = 1;
      break;
    case mem_S:
      rw = LH(READMEM(jctx, ctx->E));
      CHKERROR(jctx);
      lw = 0;
      set_accum = 1;
      set_effw = 1;
      put_left = 1;
      break;
    }
    break;
  }

  switch (DO_tmod) {
  case mod_none:
    put_left = 0;
    break;
  case mod_Z:
    put_left = 1;
    break;
  case mod_O:
    put_left = 1;
    lw = 0777777;
    break;
  case mod_E:
    put_left = 1;
    if (rw & 0400000) 
      lw = 0777777;
    break;
  }

  /*  printf("lw=%o rw=%o left=%d effw=%d accum=%d\n",lw,rw,put_left,set_effw,set_accum);*/

  switch (DO_tto) {
  case to_L:
    if (set_effw) {
      if (put_left) {
	t = rw;
	t <<= 18;
	t |= lw;
	WRITEMEM(jctx, ctx->E, t);
	CHKERROR(jctx);
      }
      else {
	t = READMEM(jctx, ctx->E) & RWM;
	CHKERROR(jctx);
	u = rw;
	u <<= 18;
	u |= t;
	WRITEMEM(jctx, ctx->E, u);
	CHKERROR(jctx);
      }
      if (set_accum && cAC) {
	t = READMEM(jctx, ctx->E);
	CHKERROR(jctx);
	WRITEMEM(jctx, ctx->AC, t);
	CHKERROR(jctx);
      }
    } else {
      if (put_left) {
	t = rw;
	t <<= 18;
	t |= lw;
	WRITEMEM(jctx, ctx->AC, t);
	CHKERROR(jctx);
      }
      else {
	t = READMEM(jctx,ctx->AC) & RWM;
	CHKERROR(jctx);
	u = rw;
	u <<= 18;
	u |= t;
	WRITEMEM(jctx, ctx->AC, u);
	CHKERROR(jctx);
      }
    }
    break;
  case to_R:
    if (set_effw) {
      if (put_left) {
	t = lw;
	t <<= 18;
	t |= rw;
	WRITEMEM(jctx, ctx->E, t);
	CHKERROR(jctx);
      }
      else {
	t = READMEM(jctx, ctx->E) & LWM;
	CHKERROR(jctx);
	u = t;
	u |= rw;
	WRITEMEM(jctx, ctx->E, u);
	CHKERROR(jctx);
      }
      if (set_accum && cAC) {
	t = READMEM(jctx, ctx->E);
	CHKERROR(jctx);
	WRITEMEM(jctx, ctx->AC, t);
	CHKERROR(jctx);
	
      }
    } else {
      if (put_left) {
	t = lw;
	t <<= 18;
	t |= rw;
	WRITEMEM(jctx, ctx->AC, t);
	CHKERROR(jctx);
      }
      else {
	t = READMEM(jctx,ctx->AC) & LWM;
	CHKERROR(jctx);
	u = rw;
	u |= t;
	WRITEMEM(jctx, ctx->AC, u);
	CHKERROR(jctx);
      }
    }
      
    break;
  }

  return(OK_EXIT);

}
