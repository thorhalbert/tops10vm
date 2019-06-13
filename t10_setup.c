#include "op.h"

#include "tops10-monctx.h"

T10MCTX *create_mctx()
{

  int s;
  T10MCTX *nmctx;

  s = sizeof(T10MCTX);

  nmctx = (T10MCTX *) malloc(s);
  if (nmctx==NULL) {
    printf("Couldn't allocate T10MCTX\n");
    exit(100);
  }

  memset((void *) nmctx, 0, s);  // Clear new structure completely

  return(nmctx);

}
