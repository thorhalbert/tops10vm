#include "op.h"

// Byte operations LDB,DPB,IBP,ILDB,IDPB

INITOP("LDB",op_LDB,0)
INITOP("DPB",op_DPB,0)
INITOP("IBP",op_IBP,0)
INITOP("ILDB",op_ILDB,0)
INITOP("IDPB",op_IDPB,0)

BIGV maskw[] = {
  0,
  0000000000001ULL,
  0000000000003ULL,
  0000000000007ULL,
  0000000000017ULL,
  0000000000027ULL,
  0000000000077ULL,
  0000000000177ULL,
  0000000000377ULL,
  0000000000777ULL,
  0000000001777ULL,
  0000000003777ULL,
  0000000007777ULL,
  0000000017777ULL,
  0000000037777ULL,
  0000000077777ULL,
  0000000177777ULL,
  0000000377777ULL,
  0000000777777ULL,
  0000001777777ULL,
  0000003777777ULL,
  0000007777777ULL,
  0000017777777ULL,
  0000037777777ULL,
  0000077777777ULL,
  0000177777777ULL,
  0000377777777ULL,
  0000777777777ULL,
  0001777777777ULL,
  0003777777777ULL,
  0007777777777ULL,
  0017777777777ULL,
  0037777777777ULL,
  0077777777777ULL,
  0177777777777ULL,
  0377777777777ULL,
  0777777777777ULL
};

#define calEdef BIGV _tv,new_cnE; int _ma, _ad, _ib, _in, new_E
#define calE(inval) \
  new_cnE = inval; \
  while (1) { \
    _tv = new_cnE; \
    _tv &= RWM; \
    _ad = _tv; \
    _tv = new_cnE; \
    _tv &= IBM; \
    _tv >>= IBS; \
    _ib = _tv; \
    _tv = new_cnE; \
    _tv &= INM; \
    _tv >>= INS; \
    _in = _tv; \
    new_E = _ad; \
    if (_in)  \
      new_E += READMEM(jctx,_in); \
    CHKERROR(jctx); \
    new_E &= RWM; \
    if (_ib==0) break; \
    _ma = new_E; \
    new_cnE = READMEM(jctx,_ma); \
    CHKERROR(jctx); \
  }

int getbps(PCTX *ctx, int *S, int *P, int *BE, BIGV *CE)
{

  BIGV getbp,t;
  calEdef;

  getbp = READMEM(jctx, cE);
  CHKERROR(jctx);

  calE(getbp);

  *CE = new_cnE;
  *BE = new_E;
  
  t = new_cnE & BPP;
  t >>= BPPS;

  *S = t;

  t = new_cnE & BPS;
  t >>= BPSS;

  *P = t;

}

/*
     Byte pointer format

     S is size of byte in bits
     P is bits remaining to right of byte

*/

// Load a byte

int op_LDB(PCTX *ctx)
{

  int S,P,BE;
  BIGV CE;

  // NEED TO CHECK S & P FOR RANGE

  // Compute an effective address from E

  (void) getbps(ctx,&S,&P,&BE,&CE); 
  CHKERROR(jctx);

  // Move the word down by P bits

  if (P>0)
    CE >>= P;

  // Mask of S bits

  CE &= maskw[S];

  // Return that in the accumulator

  WRITEMEM(jctx, cAC, CE);
  CHKERROR(jctx);

  return(OK_EXIT);

}

// Put a byte

int op_DPB(PCTX *ctx)
{

  int S,P,BE;
  BIGV CE,inac,inmask;

  inac = READMEM(jctx, cAC);
  CHKERROR(jctx);

  // NEED TO CHECK S & P FOR RANGE

  // Compute an effective address from E

  (void) getbps(ctx,&S,&P,&BE,&CE); 
  CHKERROR(jctx);

  // Mask off the incoming word

  inac &= maskw[S];
  inmask = maskw[S];

  // Move the word up by P bits to load it

  if (P>0) {
    inac <<= P;
    inmask <<= P;
  }

  // Zero out the output word then or our value on it

  CE &= ~inmask;   // zero out the word
  CE |= inac;      // put the value in

  // Write that into the output word

  WRITEMEM(jctx, BE, CE);
  CHKERROR(jctx);

  return(OK_EXIT);

}

// Increment a byte and increment

int op_ILDB(PCTX *ctx)
{

  int S,P,BE;
  BIGV CE,t;

  // NEED TO CHECK S & P FOR RANGE

  // Compute an effective address from E

  (void) getbps(ctx,&S,&P,&BE,&CE); 
  CHKERROR(jctx);

  // Increment the byte pointer

  P -= S;

  if (P<0) {
    P = 36 - S;
    BE++;        // Increment byte pointer
  }

  // Generate the new value - re-retreive E

  CE = READMEM(jctx, cE);
  CHKERROR(jctx);

  t = P;
  t <<= BPPS;

  CE &= ~BPP;
  CE |= t;

  CE &= LWM;
  CE |= BE;

  WRITEMEM(jctx, cE, CE);
  CHKERROR(jctx);

  return(op_LDB(ctx));

}

// Increment and Put a byte

int op_IDPB(PCTX *ctx)
{

  int S,P,BE;
  BIGV CE,inac,inmask,t;

  inac = READMEM(jctx, cAC);
  CHKERROR(jctx);

  // NEED TO CHECK S & P FOR RANGE

  // Compute an effective address from E

  (void) getbps(ctx,&S,&P,&BE,&CE); 
  CHKERROR(jctx);

  // Increment the byte pointer

  P -= S;

  if (P<0) {
    P = 36 - S;
    BE++;        // Increment byte pointer
  }

  // Generate the new value - re-retreive E

  CE = READMEM(jctx, cE);
  CHKERROR(jctx);

  t = P;
  t <<= BPPS;

  CE &= ~BPP;
  CE |= t;

  CE &= LWM;
  CE |= BE;

  WRITEMEM(jctx, cE, CE);
  CHKERROR(jctx);

  return(op_DPB(ctx));

}

// Increment

int op_IBP(PCTX *ctx)
{

  int S,P,BE;
  BIGV CE,inac,inmask,t;

  inac = READMEM(jctx, cAC);
  CHKERROR(jctx);

  // NEED TO CHECK S & P FOR RANGE

  // Compute an effective address from E

  (void) getbps(ctx,&S,&P,&BE,&CE); 
  CHKERROR(jctx);

  // Increment the byte pointer

  P -= S;

  if (P<0) {
    P = 36 - S;
    BE++;        // Increment byte pointer
  }

  // Generate the new value - re-retreive E

  CE = READMEM(jctx, cE);
  CHKERROR(jctx);

  t = P;
  t <<= BPPS;

  CE &= ~BPP;
  CE |= t;

  CE &= LWM;
  CE |= BE;

  WRITEMEM(jctx, cE, CE);
  CHKERROR(jctx);

  return(OK_EXIT);

}
