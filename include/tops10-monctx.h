// Tops10 Monitor Context file

#include "tops10-files.h"

typedef struct _t10mctx {
  T10SFH *clist[T10SFH_MAXCHAN];  // Simple file handler channel table
} T10MCTX;

#define mCTX ((T10MCTX *) ctx->oshook)  // Cast the ctx hook into this struct

T10MCTX *create_mctx();
