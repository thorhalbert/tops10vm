#include "op.h"

INITOP("ASH",op_ASH,0)

_SUB int op_ASH(PCTX *ctx)
{

  BIGV t;
  int shif;

  shif = cE;

  if (shif>0) {
    char b36;
    if (shif>=35) 
      return(OK_EXIT);
    b36 = (READMEM(jctx,ctx->AC) & HIGHB) != 0;
    CHKERROR(jctx);
    t = (READMEM(jctx,ctx->AC) & ALLBHIGHB) << shif;
    CHKERROR(jctx);
    WRITEMEM(jctx,ctx->AC,t);
    CHKERROR(jctx);
    if (b36) {
      t = READMEM(jctx, ctx->AC);
      CHKERROR(jctx);
      t |= HIGHB;
      WRITEMEM(jctx, ctx->AC, t);
      CHKERROR(jctx);
    }
  } else {
    char b36;
    shif = -shif;
    if (shif>=35) 
      return(OK_EXIT);
    b36 = (READMEM(jctx,ctx->AC) & HIGHB) != 0;
    CHKERROR(jctx);
    t = (READMEM(jctx,ctx->AC) & ALLBHIGHB) >> shif;
    CHKERROR(jctx);
    WRITEMEM(jctx, ctx->AC, t);
    CHKERROR(jctx);
    if (b36) {
      t = READMEM(jctx, ctx->AC);
      CHKERROR(jctx);
      t |= HIGHB;
      WRITEMEM(jctx, ctx->AC, t);
      CHKERROR(jctx);
    }
  }

  return(OK_EXIT);

}

// Need ASHC 

int bitrot(PCTX *ctx, unsigned char *bitarr, int bits, int wrap)
{

#define DLEFT 0
#define DRIGHT 1

  int i,num,dire,carrybit,ncarry;
  unsigned char bitlist[80];
  BIGV t;

  for (i=0; i<80; i++) bitlist[i] = 0;

  t = ctx->E;
  NORMALIZE_RH(t);
  num = t;

  // The real processor only uses the last few bits of this -- we
  // can modulus around any number of bits -- probably wrong

  if (ctx->debugthisop)
    printf("Rotate by %d\n",num);

  // Get rid of modulus (if it gets entirely wrapped around)

  num %= bits;  

  for (i=0; i<bits; i++) {
    int j;

    j = i + num;

    if (wrap) {
      j += (bits *2);  // Normalize a negative value 
      j %= bits;       // Wrap
    }

    if (j<0 || j>=bits) continue;

    bitlist[j] = bitarr[i];
  }

  for (i=0; i<bits; i++)
    bitarr[i] = bitlist[i];

  return(0);

}

INITOP("LSH",op_LSH,0)
_SUB int op_LSH(PCTX *ctx)
{
  unsigned char rots[36];

  if (peelbits(ctx,ctx->AC,rots,36,0)) return(1);

  bitrot(ctx,rots,36,0);

  if (packbits(ctx,ctx->AC,rots,36,0,1)) return(1);

  return(OK_EXIT);
}

INITOP("LSHC",op_LSHC,0)
_SUB int op_LSHC(PCTX *ctx)
{

  unsigned char rots[72];

  if (peelbits(ctx,ctx->AC,rots,36,0)) return(1);
  if (peelbits(ctx,ctx->AC+1,&rots[36],36,0)) return(1);

  bitrot(ctx,rots,72,0);

  if (packbits(ctx,ctx->AC,rots,36,0,1)) return(1);
  if (packbits(ctx,ctx->AC+1,&rots[36],36,0,1)) return(1);

  return(OK_EXIT);
}

INITOP("ROT",op_ROT,0)
_SUB int op_ROT(PCTX *ctx)
{
  unsigned char rots[36];

  if (peelbits(ctx,ctx->AC,rots,36,0)) return(1);

  bitrot(ctx,rots,36,1);

  if (packbits(ctx,ctx->AC,rots,36,0,1)) return(1);

  return(OK_EXIT);

}

INITOP("ROTC",op_ROTC,0)
_SUB int op_ROTC(PCTX *ctx)
{

  unsigned char rots[72];

  if (peelbits(ctx,ctx->AC,rots,36,0)) return(1);
  if (peelbits(ctx,ctx->AC+1,&rots[36],36,0)) return(1);

  bitrot(ctx,rots,72,1);

  if (packbits(ctx,ctx->AC,rots,36,0,1)) return(1);
  if (packbits(ctx,ctx->AC+1,&rots[36],36,0,1)) return(1);

  return(OK_EXIT);
}

