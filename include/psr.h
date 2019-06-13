#include "mainmem.h"

#include "pagelayout.h"



typedef struct ctx_str {

  // Job context 

  JOBCTX *jCTX;

  // Processor Status Register PDP-10 

  int PC;

  char PMODE;              // What kind of computer are we?
#define CT_P6	1		// PDP-6 Type Processor
#define CT_KA	2		// KA-10 Type Processor
#define CT_KI	3		// KI-10 Type Processor
#define CT_KL	4		// KL-10 Type Processor
#define CT_KS	5		// KS-10 Type Processor
#define CT_XKL  6               // XKL TOAD-1 Processor

  char KTYPE;             // What kernel are we emulating?

#define KT_T10  1               // Tops-10
#define KT_T20  2               // Tops-20
#define KT_ITS  10              // ITS

  char segments;          // Permit multiple segments

  int TRACE;              // Type of trace to run 

#define TRACE_NONE 0
#define TRACE_ON 1
#define TRACE_WIDE 2

  char PSTAT;

#define PSTAT_RUNNING 1
#define PSTAT_HALTED 2
#define PSTAT_SINGLESTEP 3

  char PCSET;  /* The PC was overriden by op */

  BIGV pstatus;  // Processor status word

#define SB_MASK 0777740000000ULL

#define SB_AROV BIT00
#define SB_CRY0 BIT01
#define SB_CRY1 BIT02
#define SB_FOV  BIT03
#define SB_FPD  BIT04
#define SB_BIS  BIT04   // Byte Interrupt (KA only?)
#define SB_USER BIT05
#define SB_IOT  BIT06    
#define SB_PUBL BIT07
#define SB_AFI  BIT08
#define SB_TRAP2 BIT09
#define SB_TRAP1 BIT10
#define SB_FXU  BIT11
#define SB_DCK  BIT12

  int xct_depth;  /* To keep xct from going into an infinite recursion */

  BIGV exins;

  int OP;
  int AC;
  int E;
  int IN;
  int IB;
  BIGV PreE;     // Unmasked E - should still contain the original flags

  char watch_day;
  char watch_run;
  char watch_wait;
  char watch_reads;
  char watch_writes;
  char watch_versions;
  char watch_tape;
  char watch_core;
  
  int debugop;
  int debugthisop;

  void *oshook;   // Structure for OS-Context block

} PCTX;

#define OK_EXIT 0
#define OK_PSTAT 1
#define OK_PFLAG 2
#define OK_MUUO 10  /* Illegal instruction */
#define OK_LUUO 11
#define OK_UUO 12

#define OK_HALTPROC 20
#define OK_EXITJOB 21

// Prototypes for psr modules

PCTX *psr_create_pctx();
PCTX *psr_setup();
int unpack236(PCTX *ctx, int addr, unsigned char *oc);
int pack236(PCTX *ctx, int addr, unsigned char *oc);
int unpack36(PCTX *ctx, int addr, unsigned char *oc);
int pack36(PCTX *ctx, int addr, unsigned char *oc);
int peelbits(PCTX *ctx, int addr, unsigned char *oc, int numbits, int packstart);
int packbits(PCTX *ctx, int addr, unsigned char *oc, int numbits, int packstart,int clear);
void dumppsrvals(BIGV val);
void unpacksixhw(int inval, char o[3]);
void unpacksixbit(BIGV inval, char o[6]);
BIGV packasciz(char iv[5],int len);
