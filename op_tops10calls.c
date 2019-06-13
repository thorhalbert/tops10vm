#include "op.h"

#include "tops10-callis.h"

INITOP("TTCALL",op_TTCALL,0)

_SUB int op_TTCALL(PCTX *ctx)
{

  return(t10_TTCALL(ctx));

}

INITOP("CALLI",op_CALLI,0)

_SUB int op_CALLI(PCTX *ctx)
{

  char *calliname;

  // Dispatch or error return table

  switch(cE) {

  case CALLI_LIGHTS:	return(t10_CALLI_LIGHTS(ctx));
  case CALLI_RESET:	return(t10_CALLI_RESET(ctx));
  case CALLI_DDTIN:	calliname="DDTIN"; break;
  case CALLI_SETDDT:	calliname="SETDDT"; break;
  case CALLI_DDTOUT:	calliname="DDTOUT"; break;
  case CALLI_DEVCHR:	calliname="DEVCHR"; break;
  case CALLI_DDTGT:	calliname="DDTGT"; break;
  case CALLI_GETCHR:	calliname="GETCHR"; break;
  case CALLI_DDTRL:	calliname="DDTRL"; break;
  case CALLI_WAIT:	calliname="WAIT"; break;
  case CALLI_CORE:	return(t10_CALLI_CORE(ctx));
  case CALLI_EXIT:	return(t10_CALLI_EXIT(ctx));
  case CALLI_UTPCLR:	calliname="UTPCLR"; break;
  case CALLI_DATE:	return(t10_CALLI_DATE(ctx));
  case CALLI_LOGIN:	calliname="LOGIN"; break;
  case CALLI_APRENB:	calliname="APRENB"; break;
  case CALLI_LOGOUT:	calliname="LOGOUT"; break;
  case CALLI_SWITCH:	calliname="SWITCH"; break;
  case CALLI_REASSI:	calliname="REASSI"; break;
  case CALLI_TIMER:	return(t10_CALLI_TIMER(ctx));
  case CALLI_MSTIME:	return(t10_CALLI_MSTIME(ctx));
  case CALLI_GETPPN:	return(t10_CALLI_GETPPN(ctx));
  case CALLI_TRPSET:	calliname="TRPSET"; break;
  case CALLI_TRPJEN:	calliname="TRPJEN"; break;
  case CALLI_RUNTIM:	calliname="RUNTIM"; break;
  case CALLI_PJOB:	return(t10_CALLI_PJOB(ctx));
  case CALLI_SLEEP:	return(t10_CALLI_SLEEP(ctx));
  case CALLI_SETPOV:	calliname="SETPOV"; break;
  case CALLI_PEEK:	calliname="PEEK"; break;
  case CALLI_GETLIN:	calliname="GETLIN"; break;
  case CALLI_RUN:	calliname="RUN"; break;
  case CALLI_SETUWP:	calliname="SETUWP"; break;
  case CALLI_REMAP:	calliname="REMAP"; break;
  case CALLI_GETSEG:	calliname="GETSEG"; break;
  case CALLI_GETTAB:	return(t10_CALLI_GETTAB(ctx));
  case CALLI_SPY:	calliname="SPY"; break;
  case CALLI_SETNAM:	calliname="SETNAM"; break;
  case CALLI_TMPCOR:	calliname="TMPCOR"; break;
  case CALLI_DSKCHR:	calliname="DSKCHR"; break;
  case CALLI_SYSSTR:	calliname="SYSSTR"; break;
  case CALLI_JOBSTR:	calliname="JOBSTR"; break;
  case CALLI_STRUUO:	calliname="STRUUO"; break;
  case CALLI_SYSPHY:	calliname="SYSPHY"; break;
  case CALLI_FRECHN:	calliname="FRECHN"; break;
  case CALLI_DEVTYP:	calliname="DEVTYP"; break;
  case CALLI_DEVSTS:	calliname="DEVSTS"; break;
  case CALLI_DEVPPN:	calliname="DEVPPN"; break;
  case CALLI_SEEK:	calliname="SEEK"; break;
  case CALLI_RTTRP:	calliname="RTTRP"; break;
  case CALLI_LOCK:	calliname="LOCK"; break;
  case CALLI_JOBSTS:	calliname="JOBSTS"; break;
  case CALLI_LOCATE:	calliname="LOCATE"; break;
  case CALLI_WHERE:	calliname="WHERE"; break;
  case CALLI_DEVNAM:	calliname="DEVNAM"; break;
  case CALLI_CTLJOB:	calliname="CTLJOB"; break;
  case CALLI_GOBSTR:	calliname="GOBSTR"; break;
  case CALLI_ACTIVA:	calliname="ACTIVA"; break;
  case CALLI_DEACTI:	calliname="DEACTI"; break;
  case CALLI_HPQ:	calliname="HPQ"; break;
  case CALLI_HIBER:	calliname="HIBER"; break;
  case CALLI_WAKE:	calliname="WAKE"; break;
  case CALLI_CHGPPN:	calliname="CHGPPN"; break;
  case CALLI_SETUUO:	calliname="SETUUO"; break;
  case CALLI_DEVGEN:	calliname="DEVGEN"; break;
  case CALLI_OTHUSR:	calliname="OTHUSR"; break;
  case CALLI_CHKACC:	calliname="CHKACC"; break;
  case CALLI_DEVSIZ:	calliname="DEVSIZ"; break;
  case CALLI_DAEMON:	calliname="DAEMON"; break;
  case CALLI_JOBPEK:	calliname="JOBPEK"; break;
  case CALLI_ATTACH:	calliname="ATTACH"; break;
  case CALLI_DAEFIN:	calliname="DAEFIN"; break;
  case CALLI_FRCUUO:	calliname="FRCUUO"; break;
  case CALLI_DEVLNM:	calliname="DEVLNM"; break;
  case CALLI_PATHd:	calliname="PATH."; break;
  case CALLI_METERd:	calliname="METER."; break;
  case CALLI_MTCHRd:	calliname="MTCHR."; break;
  case CALLI_JBSETd:	calliname="JBSET."; break;
  case CALLI_POKEd:	calliname="POKE."; break;
  case CALLI_TRMNOd:	calliname="TRMNO."; break;
  case CALLI_TRMOPd:	calliname="TRMOP."; break;
  case CALLI_RESDVd:	calliname="RESDV."; break;
  case CALLI_UNLOKd:	calliname="UNLOK."; break;
  case CALLI_DISKd:	calliname="DISK."; break;
  case CALLI_DVRSTd:	calliname="DVRST."; break;
  case CALLI_DVURSd:	calliname="DVURS."; break;
  case CALLI_XTTSKd:	calliname="XTTSK."; break;
  case CALLI_CAL11d:	calliname="CAL11."; break;
  case CALLI_MTAIDd:	calliname="MTAID."; break;
  case CALLI_IONDXd:	calliname="IONDX."; break;
  case CALLI_CNECTd:	calliname="CNECT."; break;
  case CALLI_MVHDRd:	calliname="MVHDR."; break;
  case CALLI_ERLSTd:	calliname="ERLST."; break;
  case CALLI_SENSEd:	calliname="SENSE."; break;
  case CALLI_CLRSTd:	calliname="CLRST."; break;
  case CALLI_PIINId:	calliname="PIINI."; break;
  case CALLI_PISYSd:	calliname="PISYS."; break;
  case CALLI_DEBRKd:	calliname="DEBRK."; break;
  case CALLI_PISAVd:	calliname="PISAV."; break;
  case CALLI_PIRSTd:	calliname="PIRST."; break;
  case CALLI_IPCFRd:	calliname="IPCFR."; break;
  case CALLI_IPCFSd:	calliname="IPCFS."; break;
  case CALLI_IPCFQd:	calliname="IPCFQ."; break;
  case CALLI_PAGEd:	calliname="PAGE."; break;
  case CALLI_SUSETd:	calliname="SUSET."; break;
  case CALLI_COMPTd:	calliname="COMPT."; break;
  case CALLI_SCHEDd:	calliname="SCHED."; break;
  case CALLI_ENQd:	calliname="ENQ."; break;
  case CALLI_DEQd:	calliname="DEQ."; break;
  case CALLI_ENQCd:	calliname="ENQC."; break;
  case CALLI_TAPOPd:	calliname="TAPOP."; break;
  case CALLI_FILOPd:	calliname="FILOP."; break;
  case CALLI_CAL78d:	calliname="CAL78."; break;
  case CALLI_NODEd:	calliname="NODE."; break;
  case CALLI_ERRPTd:	calliname="ERRPT."; break;
  case CALLI_ALLOCd:	calliname="ALLOC."; break;
  case CALLI_PERFd:	calliname="PERF."; break;
  case CALLI_DIAGd:	calliname="DIAG."; break;
  case CALLI_DVPHYd:	calliname="DVPHY."; break;
  case CALLI_GTNTNd:	calliname="GTNTN."; break;
  case CALLI_GTXTNd:	calliname="GTXTN."; break;
  case CALLI_ACCTd:	calliname="ACCT."; break;
  case CALLI_DTEd:	calliname="DTE."; break;
  case CALLI_DEVOPd:	calliname="DEVOP."; break;
  case CALLI_SPPRMd:	calliname="SPPRM."; break;
  case CALLI_MERGEd:	calliname="MERGE."; break;
  case CALLI_UTRPd:	calliname="UTRP."; break;
  case CALLI_PIJBId:	calliname="PIJBI."; break;
  case CALLI_SNOOPd:	calliname="SNOOP."; break;
  case CALLI_TSKd:	calliname="TSK."; break;
  case CALLI_KDPd:	calliname="KDP."; break;
  case CALLI_QUEUEd:	calliname="QUEUE."; break;
  case CALLI_RECONd:	calliname="RECON."; break;
  case CALLI_PITMRd:	calliname="PITMR."; break;
  case CALLI_ACCLGd:	calliname="ACCLG."; break;
  case CALLI_NSPd:	calliname="NSP."; break;
  case CALLI_NTMANd:	calliname="NTMAN."; break;
  case CALLI_DNETd:	calliname="DNET."; break;
  case CALLI_SAVEd:	calliname="SAVE."; break;
  case CALLI_CMANDd:	calliname="CMAND."; break;
  case CALLI_PIBLKd:	calliname="PIBLK."; break;
  case CALLI_SCSd:	calliname="SCS."; break;
  case CALLI_SEBLKd:	calliname="SEBLK."; break;
  case CALLI_CTXd:	calliname="CTX."; break;
  case CALLI_PIFLGd:	calliname="PIFLG."; break;
  case CALLI_IPCFMd:	calliname="IPCFM."; break;
  case CALLI_LLMOPd:	calliname="LLMOP."; break;
  case CALLI_LATOPd:	calliname="LATOP."; break;
  case CALLI_KNIBTd:	calliname="KNIBT."; break;
  case CALLI_CHTRNd:	calliname="CHTRN."; break;
  case CALLI_ETHNTd:	calliname="ETHNT."; break;
  case CALLI_ENTVCd:	calliname="ENTVC."; break;
  case CALLI_NETOPd:	calliname="NETOP."; break;
  case CALLI_DDPd:	calliname="DDP."; break;
  case CALLI_SEGOPd:	calliname="SEGOP."; break;
  default:
    printf("?T10_CALLI - Unknown CALLI %o at PC %06o\n",cE,cPC);
    return(OK_EXIT);   /* Will return to the error return */
  }

  printf("?T10_CALLI - Unimplimented CALLI %o [%s] at PC %06o\n",cE,calliname,cPC);
  return(OK_EXIT);     /* Return to the error return */

  //setPCSET; // Save this for a potential correct return;

}



INITOP("CALL",op_CALL,0)
_SUB int op_CALL(PCTX *ctx)
{
  printf("?T10_CALL - Unimplimented UUO CALL at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}

INITOP("INIT",op_INIT,0)
_SUB int op_INIT(PCTX *ctx)
{
  return(t10_INIT(ctx));
}

INITOP("OPEN",op_OPEN,0)
_SUB int op_OPEN(PCTX *ctx)
{
  return(t10_OPEN(ctx));
}

INITOP("RDCLK",op_RDCLK,0)
_SUB int op_RDCLK(PCTX *ctx)
{
  printf("?T10_RDCLK - Unimplimented UUO RDCLK at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}


INITOP("RENAME",op_RENAME,0)
_SUB int op_RENAME(PCTX *ctx)
{
  printf("?T10_RENAME - Unimplimented UUO RENAME at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}

INITOP("IN",op_IN,0)
_SUB int op_IN(PCTX *ctx)
{
  printf("?T10_IN - Unimplimented UUO IN at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}

INITOP("OUT",op_OUT,0)
_SUB int op_OUT(PCTX *ctx)
{
  printf("?T10_OUT - Unimplimented UUO OUT at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}

INITOP("SETSTS",op_SETSTS,0)
_SUB int op_SETSTS(PCTX *ctx)
{
  printf("?T10_SETSTS - Unimplimented UUO SETSTS at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}

INITOP("STATO",op_STATO,0)
_SUB int op_STATO(PCTX *ctx)
{
  printf("?T10_STATO - Unimplimented UUO STATO at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}

INITOP("STATZ",op_STATZ,0)
_SUB int op_STATZ(PCTX *ctx)
{
  printf("?T10_STATZ - Unimplimented UUO STATZ at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}

INITOP("INBUF",op_INBUF,0)

_SUB int op_INBUF(PCTX *ctx)
{
  return(t10_INBUF(ctx));
}

INITOP("OUTBUF",op_OUTBUF,0)
_SUB int op_OUTBUF(PCTX *ctx)
{
  return(t10_OUTBUF(ctx));
}

INITOP("INPUT",op_INPUT,0)
_SUB int op_INPUT(PCTX *ctx)
{
  printf("?T10_INPUT - Unimplimented UUO INPUT at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}

INITOP("OUTPUT",op_OUTPUT,0)
_SUB int op_OUTPUT(PCTX *ctx)
{
  printf("?T10_OUTPUT - Unimplimented UUO OUTPUT at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}

INITOP("CLOSE",op_CLOSE,0)
_SUB int op_CLOSE(PCTX *ctx)
{
  printf("?T10_CLOSE - Unimplimented UUO CLOSE at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}

INITOP("RELEAS",op_RELEAS,0)
_SUB int op_RELEAS(PCTX *ctx)
{
  return(t10_RELEAS(ctx));
}

INITOP("MTAPE",op_MTAPE,0)
_SUB int op_MTAPE(PCTX *ctx)
{
  printf("?T10_MTAPE - Unimplimented UUO MTAPE at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}

INITOP("UGETF",op_UGETF,0)
_SUB int op_UGETF(PCTX *ctx)
{
  printf("?T10_UGETF - Unimplimented UUO UGETF at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}

INITOP("USETI",op_USETI,0)
_SUB int op_USETI(PCTX *ctx)
{
  printf("?T10_USETI - Unimplimented UUO USETI at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}

INITOP("USETO",op_USETO,0)
_SUB int op_USETO(PCTX *ctx)
{
  printf("?T10_USETO - Unimplimented UUO USETO at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}

INITOP("LOOKUP",op_LOOKUP,0)
_SUB int op_LOOKUP(PCTX *ctx)
{
  printf("?T10_LOOKUP - Unimplimented UUO LOOKUP at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}

INITOP("ENTER",op_ENTER,0)
_SUB int op_ENTER(PCTX *ctx)
{
  printf("?T10_ENTER - Unimplimented UUO ENTER at PC %06o\n",cPC);
  cPSTAT = PSTAT_HALTED;
  return(OK_PSTAT);
}
