// Main Module

#include <popt.h>
#include <stdio.h>
#include <string.h>

#include "psr.h"

#include "tops10-files.h"

extern int inst;

int segments = 1;
int locore_min = 0;
int hicore_min = 0;
int trace = TRACE_NONE;
int proctype = CT_KL;
int kernel_type = KT_T10;
int transfer = 0;
char watch_day;
char watch_run;
char watch_wait;
char watch_reads;
char watch_writes;
char watch_versions;
char watch_tape;
char watch_core;
int debugop;

char dumpargs=0;

void dumpallargs()
{

  printf("Processor:");
  switch(proctype) {
  case CT_P6: printf(" PDP-6"); break;
  case CT_KA: printf(" KA-10"); break;
  case CT_KL: printf(" KL-10"); break;
  case CT_KI: printf(" KI-10"); break;
  case CT_KS: printf(" KS-10"); break;
  case CT_XKL: printf(" XKL-10"); break;
  }
  
  printf(" OS:");
  switch(kernel_type) {
  case KT_T10: printf(" Tops-10"); break;
  case KT_T20: printf(" Tops-20"); break;
  case KT_ITS: printf(" ITS"); break;
  }

  printf(" Seg: %s",segments?"ENABLED":"DISABLED");
  printf(" Low-Core:");
  if (locore_min)
    printf(" %dK",locore_min);
  else 
    printf(" UNSET");
  printf(" HiSEG:");
  if (hicore_min)
    printf(" %dK",hicore_min);
  else 
    printf(" UNSET");
  printf("\n");
  printf("Watches:");
  if (watch_day) printf(" DAY");
  if (watch_run) printf(" RUN");
  if (watch_wait) printf(" WAIT");
  if (watch_reads) printf(" READS");
  if (watch_writes) printf(" WRITES");
  if (watch_versions) printf(" VERSIONS");
  if (watch_tape) printf(" TAPE");
  if (watch_core) printf(" CORE");
  if (watch_day+watch_run+watch_wait+watch_reads+
      watch_writes+watch_versions+watch_tape+watch_core==0)
    printf(" NONE");
  printf("\n");
  if (transfer>0) {
    if (transfer<0400) 
      printf("Transfer Address Offset: +%o\n",transfer);
    else
      printf("Transfer Address (start address): %06o\n",transfer);
  }
  if (debugop) 
    show_debugop();
}

#define ARG_P6 101
#define ARG_KA 102
#define ARG_KL 103
#define ARG_KI 104
#define ARG_KS 105
#define ARG_XKL 106
#define ARG_SEG 110
#define ARG_NOSEG 111
#define ARG_LOC 120
#define ARG_HIC 121
#define ARG_TRC 130
#define ARG_TRW 131
#define ARG_TRNO 132
#define ARG_WALL 150
#define ARG_WRUN 151
#define ARG_WDAY 152
#define ARG_WWAIT 153
#define ARG_WRD 154
#define ARG_WWR 155
#define ARG_WVR 156
#define ARG_WTAP 157
#define ARG_WCOR 158
#define ARG_NWALL 170
#define ARG_NWRUN 171
#define ARG_NWDAY 172
#define ARG_NWWAIT 173
#define ARG_NWRD 174
#define ARG_NWWR 175
#define ARG_NWVR 176
#define ARG_NWTAP 177
#define ARG_NWCOR 178
#define ARG_ST 190
#define ARG_T10 200
#define ARG_T20 201
#define ARG_ITS 202
#define ARG_DUMP 400
#define ARG_DOP 410

#define DEFDEB (POPT_ARG_NONE | POPT_ARGFLAG_ONEDASH | POPT_ARGFLAG_DOC_HIDDEN)
#define DEFOPT (POPT_ARG_NONE | POPT_ARGFLAG_ONEDASH)
#define DEFSTR (POPT_ARG_STRING | POPT_ARGFLAG_ONEDASH)

static void t10ArgCallback(poptContext con,
			   enum poptCallbackReason reason,
			   const struct poptOption *opt, 
			   const char *arg,const void *data);

struct poptOption optionsTable[] = {
  // Setup callback
  { NULL, 0, POPT_ARG_CALLBACK, (void *) t10ArgCallback, 0, NULL, NULL },
  // Processors
  { "P6", 0, DEFOPT, NULL, ARG_P6, "Emulate a PDP-6 (not implemented)", NULL },
  { "KA", 0, DEFOPT, NULL, ARG_KA, "Emulate a KA-10", NULL },
  { "KL", 0, DEFOPT, NULL, ARG_KL, "Emulate a KL-10", NULL },
  { "KI", 0, DEFOPT, NULL, ARG_KI, "Emulate a KI-10", NULL },
  { "KS", 0, DEFOPT, NULL, ARG_KS, "Emulate a KS-10", NULL },
  { "XKL", 0, DEFOPT, NULL, ARG_XKL, "Emulate an XKL-10", NULL },
  // Segments
  { "segments", 0, DEFOPT, NULL, ARG_SEG, "Permit multiple segments", NULL },  
  { "nosegments", 0, DEFOPT, NULL, ARG_NOSEG, "Don't permit multiple segments", NULL },  
  // High and low-core 
  { "locore", 0, DEFSTR, NULL, ARG_LOC, "Minimum low-core on load", "decimal-K" },
  { "hicore", 0, DEFSTR, NULL, ARG_HIC, "Minimum hiseg core on load", "decimal-K" },
  // Trace options
  { "trace", 0, DEFOPT, NULL, ARG_TRC, "Normal Instruction Trace", NULL },
  { "tracewide", 0, DEFOPT, NULL, ARG_TRW, "Wide Instruction Trace", NULL },
  { "notrace", 0, DEFOPT, NULL, ARG_TRNO, "Turn Off Tracing", NULL },
  // Watch options
  { "watch-all", 0, DEFOPT, NULL, ARG_WALL, "Turn On All Watch Flags", NULL },
  { "watch-day", 0, DEFOPT, NULL, ARG_WDAY, "Show Time at Program Start", NULL },
  { "watch-run", 0, DEFOPT, NULL, ARG_WRUN, "Show Runtime", NULL },
  { "watch-wait", 0, DEFOPT, NULL, ARG_WWAIT, "Show Waittime", NULL },
  { "watch-reads", 0, DEFOPT, NULL, ARG_WRD, "Show Reads", NULL },
  { "watch-writes", 0, DEFOPT, NULL, ARG_WWR, "Show Writes", NULL },
  { "watch-versions", 0, DEFOPT, NULL, ARG_WVR, "Show Program Names and Versions", NULL },
  { "watch-tape", 0, DEFOPT, NULL, ARG_WTAP, "Show Tape I/O", NULL },
  { "watch-core", 0, DEFOPT, NULL, ARG_WCOR, "Show Core Usage", NULL },
  { "nowatch-all", 0, DEFOPT, NULL, ARG_NWALL, "Turn Off All Watch Flags", NULL },
  { "nowatch-day", 0, DEFOPT, NULL, ARG_NWDAY, "Don't Show Time at Program Start", NULL },
  { "nowatch-run", 0, DEFOPT, NULL, ARG_NWRUN, "Don't Show Runtime", NULL },
  { "nowatch-wait", 0, DEFOPT, NULL, ARG_NWWAIT, "Don't Show Waittime", NULL },
  { "nowatch-reads", 0, DEFOPT, NULL, ARG_NWRD, "Don't Show Reads", NULL },
  { "nowatch-writes", 0, DEFOPT, NULL, ARG_NWWR, "Don't Show Writes", NULL },
  { "nowatch-versions", 0, DEFOPT, NULL, ARG_NWVR, "Don't Show Program Names and Versions", NULL },
  { "nowatch-tape", 0, DEFOPT, NULL, ARG_NWTAP, "Don't Show Tape I/O", NULL },
  { "nowatch-core", 0, DEFOPT, NULL, ARG_NWCOR, "Don't Show Core Usage", NULL },
  // Transfer address
  { "transfer", 0, DEFSTR, NULL, ARG_ST, "Transfer address or offset", "octal addr" },
  // OS Options
  { "tops10", 0, DEFOPT, NULL, ARG_T10, "TOPS-10 Monitor Calls", NULL },
  { "tops20", 0, DEFOPT, NULL, ARG_T20, "TOPS-10 Monitor Calls", NULL },
  { "its", 0, DEFOPT, NULL, ARG_ITS, "ITS Monitor Calls", NULL },
  // Help options
  { "dumpargs", 0, DEFDEB, NULL, ARG_DUMP, "Dump arguments (test popt)", NULL },
  { "debugop", 0, DEFSTR, NULL, ARG_DOP, "Debug operator", "operator name" },
  POPT_AUTOHELP
  POPT_TABLEEND
};

static void t10ArgCallback(poptContext con, 
			   enum poptCallbackReason reason,
			   const struct poptOption *opt, 
			   const char *arg,const void *data)
{
  int offs;

  switch (opt->val) {
  case ARG_P6: proctype = CT_P6; break;
  case ARG_KA: proctype = CT_KA; break;
  case ARG_KL: proctype = CT_KL; break;
  case ARG_KI: proctype = CT_KI; break;
  case ARG_KS: proctype = CT_KS; break;
  case ARG_XKL: proctype = CT_XKL; break;
  case ARG_SEG: segments = 1; break;
  case ARG_NOSEG: segments = 0; break;
  case ARG_LOC: sscanf(arg, "%d", &locore_min); break;
  case ARG_HIC: sscanf(arg, "%d", &hicore_min); break;
  case ARG_TRC: trace = TRACE_ON; break;
  case ARG_TRW: trace = TRACE_WIDE; break;
  case ARG_TRNO: trace = TRACE_NONE; break;
  case ARG_WALL: watch_day=watch_run=watch_wait=watch_reads=
		   watch_writes=watch_versions=watch_tape=watch_core=1; break;
  case ARG_WRUN: watch_run = 1; break;
  case ARG_WDAY: watch_day = 1; break;
  case ARG_WWAIT: watch_wait = 1; break;
  case ARG_WRD: watch_reads = 1; break;
  case ARG_WWR: watch_writes = 1; break;
  case ARG_WVR: watch_versions = 1; break;
  case ARG_WTAP: watch_tape = 1; break;
  case ARG_WCOR: watch_core = 1; break;
  case ARG_NWALL: watch_day=watch_run=watch_wait=watch_reads=
		   watch_writes=watch_versions=watch_tape=watch_core=0; break;
  case ARG_NWRUN: watch_run = 0; break;
  case ARG_NWDAY: watch_day = 0; break;
  case ARG_NWWAIT: watch_wait = 0; break;
  case ARG_NWRD: watch_reads = 0; break;
  case ARG_NWWR: watch_writes = 0; break;
  case ARG_NWVR: watch_versions = 0; break;
  case ARG_NWTAP: watch_tape = 0; break;
  case ARG_NWCOR: watch_core = 0; break;
  case ARG_ST:   sscanf(arg,"%o",&transfer); break;
  case ARG_T10: kernel_type = KT_T10; break;
  case ARG_T20: kernel_type = KT_T20; break;
  case ARG_ITS: kernel_type = KT_ITS; break;
  case ARG_DUMP: dumpargs = 1; break;
  case ARG_DOP: set_debugop(arg); debugop=1; break;
  default:
    break;
  }

}

int main(int argc, const char **argv)
{

  PCTX *basectx;
  int err;
  int trans;
  char c;

  int offs=0;
  char *execfile;

  poptContext optCon;

  basectx = psr_setup();  // Need to setup the processor first

  optCon = poptGetContext(NULL, argc, argv, optionsTable, 0);
  poptSetOtherOptionHelp(optCon, "[OPTIONS]* <executable-file>");

  if (argc < 2) {
    poptPrintUsage(optCon, stderr, 0);
    exit(1);
  }

 
  while ((c = poptGetNextOpt(optCon)) >= 0) ;

  execfile = NULL;
  execfile = (char *) poptGetArg(optCon);

  if ((execfile==NULL) || !(poptPeekArg(optCon) == NULL)) {
    fprintf(stderr,"Specify only one executable file\n");
    poptPrintUsage(optCon, stderr, 0);
    exit(100);
  }

  if (c < -1) {
    /* an error occurred during option processing */
    fprintf(stderr, "%s: %s\n",
	    poptBadOption(optCon, POPT_BADOPTION_NOALIAS),
	    poptStrerror(c));
    exit(100);
  }

  if (dumpargs)
    dumpallargs();

  basectx->KTYPE = kernel_type;
  basectx->PMODE = proctype;
  basectx->segments = segments;
  basectx->TRACE = trace;
  basectx->watch_day = watch_day;
  basectx->watch_run = watch_run;
  basectx->watch_wait = watch_wait;
  basectx->watch_reads = watch_reads;
  basectx->watch_writes = watch_writes;
  basectx->watch_versions = watch_versions;
  basectx->watch_tape = watch_tape;
  basectx->watch_core = watch_core;

  basectx->debugop = debugop;

  basectx->oshook = (void *) create_mctx();  // Add the OS mCTX context

  load_executable(basectx,execfile,&trans);

  if (hicore_min || locore_min)
    (void) adjust_core(basectx->jCTX, 
		       hicore_min * PAGE_SIZE, 
		       locore_min * PAGE_SIZE, 0);

  if (watch_core)
    printcore(basectx->jCTX,1);

  // Look for a start offset (<0400) or a new start address override

  if (transfer<0400)
    trans += transfer;
  else
    trans = transfer;

  err = start_processor(basectx,trans);

  printf("\n[T10VM - Exit - Instructions executed %d]\n",inst);
  
  exit(0);

}

