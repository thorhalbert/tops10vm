#include "io_inst.h"

/* not used */

#ifdef IFWENEED
struct io_inst ka_tab[] = {
  /* E-Bus devices */
  /* Console */
  { 070004, "DATAI APR" },  /* Read console switches into E */
  { 070054, "DATAO PI" },   /* Display E on memory indicators - PROGRAM DATA */
  { 071054, "DATAO PTR" },  /* Set console address and condition (KI?) */
  /* Priority Interrupts */
  { 070060, "CONO PI" },    /* Performs Priority Interrupt functions */
  { 070064, "CONI PI" },    /* Read Priority Interrupt status */
  /* Processor Conditions */
  { 070020, "CONO APR" },   /* Assign interrupt level into E and functions */
  { 070024, "CONI APR" },   /* Read status of processor into E */
  /* Program and Memory Management */
  { 070014, "DATAO APR" },  /* Load protection and relocation regs from E */
  /* DK10 Real Time Clock */
  { 070720, "CONO CLK" },   /* Assigns priority interrupt and performs funs */
  { 070724, "CONI CLK" },   /* Read interval register and status into E */
  { 070714, "DATAO CLK" },  /* Load contents of interval with E */
  { 070704, "DATAI CLK" },  /* Read contents of clock counter into E */
  { 0, 0 },
};
#endif

#define IO_DEV(a) (a>>2)

#define    IO_BLKI  	 000
#define    IO_DATAI  	 004
#define    IO_BLKO  	 010
#define    IO_DATAO  	 014
#define    IO_CONO  	 020
#define    IO_CONI  	 024
#define    IO_CONSZ  	 030
#define    IO_CONSO  	 034

#define IO_ATTACH 0100
#define IO_RESET 0110
#define IO_RESETALL 0120

struct io_attachment {
  int dev;   /* The actual dev # (not *4) */
  char *dnam; /* The device descriptor (typical device name) */
  char *desc; /* Name of the actual device */
  int (*pfun)(PCTX *ctx,int dev,int oper);  
};
