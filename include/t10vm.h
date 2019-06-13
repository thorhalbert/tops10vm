// Tops 10 system setups

#include "tops10-uuosym.h"

#define INT_FILEFMT_ASC 1
#define INT_FILEFMT_B36 2
#define INT_FILEFMT_UNIX 3

// Prototypes for TOPS-10 modules

FILE *pdp10_direct_open_read(char *fname,char *defext,int *pop, int *fmt);
int read36unix(FILE *infil, int fmt, int count, BIGV *retarr);
int load_10exe(PCTX *ctx, char *infile, int *transadr);
int load_10sav(PCTX *ctx, char *infile, int *transadr);
int load_executable(PCTX *ctx, char *infile, int *transadr);

