#include "op.h"

_SUB int t10_CALLI_LIGHTS(PCTX *ctx)
{

  int i;
  unsigned char rots[36];
  BIGV t;

  t = READMEM(jctx, ctx->AC);
  CHKERROR(jctx);

  printf("Lights: [%06o %06o]     ",(int)LH(t),(int)RH(t));

  if (peelbits(ctx,ctx->AC,rots,36,0)) return(1);

  for(i=35; i>=0; i--) {
    if (rots[i]) printf("#");
    else printf("-");
  }
  printf("\n");

  // Non-Error return

  ctx->PC ++;

  return(OK_EXIT);

}
