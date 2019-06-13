#include "psr.h"

#include "opcodelist.h"

#include "ka_io.h"
#include "ka_devs.h"
#include "ka_devt.h"

extern MEMLOC *main_core;

struct io_attachment io_devices[0100];

int ka_dev_apr(PCTX *ctx,int dev, int oper);
int ka_dev_pi(PCTX *ctx,int dev, int oper);

void ka_do_attach(int devnum, char *devabr, 
		  int (*pfun)(PCTX *ctx,int dev, int oper),
		  char *descrip)
{

  int iod;

  iod = IO_DEV(devnum);
  if ((iod==0 && devnum!=0) ||
      iod<0 || iod>0100) {
    printf("Bad IO attach?  dev=%o table=%o\n",devnum,iod);
    exit(100);
  }

  if (io_devices[iod].dnam) {
    printf("Bad IO attach? Conflict - New = %o/%s/%s - Old = %o/%s/%s\n",
	   devnum,devabr,descrip,
	   io_devices[iod].dev,
	   io_devices[iod].dnam,
	   io_devices[iod].desc);
    exit(100);
  }

  io_devices[iod].dev = devnum;
  io_devices[iod].dnam = devabr;
  io_devices[iod].desc = descrip;
  io_devices[iod].pfun = pfun;

}

void ka_init_attachments()
{

  int i;

  for (i=0; i<0100; i++) {
    io_devices[i].dev = 0;
    io_devices[i].dnam = 0;
    io_devices[i].desc = 0;
    io_devices[i].pfun = 0;
  }

  ka_do_attach(IODEV_APR,"APR",ka_dev_apr,"Arithmetic Processor");
  ka_do_attach(IODEV_PI,"PI",ka_dev_pi,"Priority Interrupt System");

}

int ka_io(PCTX *ctx)
{

  char opc[20];
  char dev[20];
  int i;

  BIGV tv;
  int iodev;
  int opcode;
  int devop;

  int mode_user;
  int mode_iot;
  
  mode_user=ctx->pstatus & SB_USER;
  mode_iot=ctx->pstatus & SB_IOT;

  if (mode_user && (!mode_iot))  /* I/O can only be in EXEC or IOT mode */
    return(OK_MUUO);

  tv = ctx->exins;
  tv &= IOOPMASK;
  tv >>= IOOPMASKS;

  opcode = tv;
  
  tv = ctx->exins;
  tv &= DEVMASK;
  tv >>= DEVMASKS;

  iodev = tv;

  tv = ctx->exins;
  tv &= DEVOPMASK;
  tv >>= DEVOPMASKS;

  devop = tv;

  if (io_devices[IO_DEV(iodev)].dnam) 
    return(io_devices[IO_DEV(iodev)].pfun(ctx,iodev,devop));

  sprintf(dev,"%o",iodev);
  for (i=0; ka_io_devices[i].dev<01000; i++) {
    if (iodev==ka_io_devices[i].dev) {
      strcpy(dev,ka_io_devices[i].code);
      break;
    }
  }

  strcpy(opc,"UNKNOWN");
  switch(devop) {
  case 000:
    strcpy(opc,"BLKI");
    break;
  case 004:
    strcpy(opc,"DATAI");
    break;
  case 010:
    strcpy(opc,"BLKO");
    break;
  case 014:
    strcpy(opc,"DATAO");
    break;
  case 020:
    strcpy(opc,"CONO");
    break;
  case 024:
    strcpy(opc,"CONI");
    break;
  case 030:
    strcpy(opc,"CONSZ");
    break;
  case 034:
    strcpy(opc,"CONSO");
    break;
  }

  printf("\n\n%o/ Unimplemented I/O instruction %o (%s %s)",
	 ctx->PC,
	 opcode,
	 opc,dev);
  printf("\n");
  dumpac(ctx);
  ctx->PSTAT = PSTAT_HALTED;

  ctx->xct_depth --;

  return(OK_EXIT);

}

void ka_install(PCTX *ctx)
{

  int i;

  for (i=0700; i<=0777; i++) {
    master_xbar[i].pflag = KA10;
    master_xbar[i].onam = "IO";
    master_xbar[i].pfun = ka_io;
    master_xbar[i].hits = 0;
    master_xbar[i].bytop = 0;
  }

  ka_init_attachments();
}
