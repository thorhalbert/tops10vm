#include "op.h"

void exec_word(PCTX *ctx,int inE);

INITOP("XCT",op_XCT,0)

_SUB int op_XCT(PCTX *ctx)
{

  exec_word(ctx, cE);

  setPCSET;  /* Fake into not incrementing the PC */

  return(OK_EXIT);

}
