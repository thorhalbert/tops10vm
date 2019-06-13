#include <stdio.h>
#include <string.h>

#include "psr.h"

// #define MEMSIZE 128*1024  /* Nailed for now */

// #define BOOTIMAGE "/home/halberts/diags/ka10/dakaf.sav.asc.bz2"

/* DAKAA 8-Feb-2001 
   DAKAB 9-Feb-2001
   DAKAC 9-Feb-2001
   DAKAD 12-Feb-2001
   DAKAE 15-Feb-2001
   DAKAF 15-Feb-2001
*/

extern int inst;

PCTX *psr_create_pctx()
{

  PCTX *newpctx;

  newpctx = (PCTX *) malloc(sizeof(PCTX));
  if (newpctx==NULL) exit(100);

  newpctx->jCTX = create_pager_jctx();

  newpctx->pstatus = 0;  /* Clear the processor status bits */
  newpctx->xct_depth = 0; /* Clear xct depth */
  newpctx->PC = 0;
  newpctx->PSTAT = PSTAT_HALTED;
  newpctx->PMODE = CT_KL;  /* Start running as a KL-10 processor */
  newpctx->pstatus |= SB_USER; /* We start in user mode */
  newpctx->pstatus &= ~SB_IOT; /* User I/O mode is off */
  newpctx->exins = 0;
  newpctx->debugop = 0;
  newpctx->debugthisop = 0;

  newpctx->OP=0;
  newpctx->AC=0;
  newpctx->E=0;
  newpctx->IN=0;
  newpctx->IB=0;

  return(newpctx);
}

PCTX *psr_setup()
{

  PCTX *base_ctx;

  base_ctx = psr_create_pctx();

  build_xbar();          /* Build the operator lookup table */
  bind_operators();      /* Bind the operator codes to table */

  //  dump_ndef(); /* Show unbound operators (DEBUG) */

  ka_install(base_ctx);  /* Install the KA IO and processor */

  return(base_ctx);

}
