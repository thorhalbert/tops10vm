#include "op.h"

#undef INITOP
#define INITOP(n,f,b) int f(PCTX *); 
#undef INITBOP
#define INITBOP(h,l,f,b) int f(PCTX *); 

#include "opinit.inc"

void bind_operators()
{

#undef INITOP
#define INITOP(n,f,b) register_operator(n,f,b);
#undef INITBOP
#define INITBOP(l,h,f,b) register_operator_rng(l,h,f,b);

#include "opinit.inc"

}

