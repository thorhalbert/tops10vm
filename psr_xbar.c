#include <stdio.h>

#include "psr.h"

#define DEFOPS
#include "opcodelist.h"

struct psr_xbar master_xbar[01000];

void set_debugop(char *inop)
{
  int i;

  for (i=0; i<= 0777; i++) {
    if (master_xbar[i].onam) 
      if (strncmp(master_xbar[i].onam, inop)==0) {
	master_xbar[i].pflag |= DEBUGOP;
	return;
      }
  }

  printf("?? No such operator %s\n",inop); // Error, but ignore
}

void show_debugop()
{
  int i;

  printf("Debug Ops:");
  for (i=0; i<= 0777; i++) {
    if (master_xbar[i].onam) 
      if (master_xbar[i].pflag & DEBUGOP)
	printf(" %s",master_xbar[i].onam);
  }
  printf("\n");
}

void dump_ndef(void)
{

  int i;

  printf("Unbuilt Opcodes:");

  for (i=040; i<= 0777; i++) {
    if (master_xbar[i].onam) 
      if (master_xbar[i].pfun==0) {
	//if (master_xbar[i].pflag==KA10) 
	printf(" %s (%o)",
	       master_xbar[i].onam,i);
      }
  }
  printf("\n\n");
}

void build_xbar(void)
{

  int i;

  for (i=0; op_tab[i].onam!=NULL; i++) {
    int op;

    if (op_tab[i].adr)   /* UUO Opcode - skip */
      continue;
      
    op = op_tab[i].op;

    if (op_tab[i].ac)   /* AC!=0 entry - skip */
      continue;


    if (master_xbar[op].onam) { /* Collision alias - skip */
      /*printf("See alias %s - %o\n", op_tab[i].onam,op_tab[i].op);*/
      continue;
    }

    master_xbar[op].pflag = op_tab[i].pflag;
    master_xbar[op].onam = op_tab[i].onam;

  }
}

void register_operator(char *opname, int (*pfun)(PCTX *ctx), int b)
{

  int i;
  int j;

  for (i=0; i< 0777; i++) {
    if (master_xbar[i].onam) {
      if (strcmp(master_xbar[i].onam,opname)==0) {
	master_xbar[i].pfun = pfun;
	master_xbar[i].bytop = b;
	return;
      }
    }
  }

  printf("?PSR_XBAR - Attemp to Register Unrecognized opcode: %s\n",
	 opname);
  exit(100);

}

void register_operator_rng(int l, int h, int (*pfun)(PCTX *ctx), int b)
{
  int i;

  for (i=l; i<= h; i++) {
    master_xbar[i].pfun = pfun;
    master_xbar[i].bytop = b;
  }
}

#ifdef MAINTEST
int main()
{

  build_xbar();
  walk_dump();
}
#endif
