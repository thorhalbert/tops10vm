#include "op.h"

#include "tops10-gettabs.h"

char *t10_SYSNAME="T10VM Tops-10 VM";  // Must be <= 24 chars
char *t10_SYSDATE="03-Apr-02";         // System build date


// 16    .GTLVD - Level D Disk Parameters

int t10_ciGETTABdGTLVD(PCTX *ctx,int comarg,int gettab)
{
  int vset=0;
  BIGV t;

  switch(comarg) {
  case 00:	// %LDMFD - MFD PPN [1,1] - 
    vset = 1; t = 0000001000001ULL; break;
  case 01:	// %LDSYS - SYS PPN [1,4] - 
    vset = 1; t = 0000001000004ULL; break;
  case 02:	// %LDFFA - Full file access PPN [1,2] - 
    vset = 1; t = 0000001000002ULL; break;
  case 03:	// %LDHLP - Not-logged-in PPN [2,5] - 
    vset = 1; t = 0000002000005ULL; break;
  case 04:	// %LDQUE - Queue area PPN [3,3] - 
    vset = 1; t = 0000003000003ULL; break;
  case 05:	// %LDSPB - Addr of first PPB - Addr of next PPB to scan - 
    vset = 0; t = 0ULL; break;
  case 06:	// %LDSTR - First structure data block - Offset to next str data blk - 
    vset = 0; t = 0ULL; break;
  case 07:	// %LDUNI - First unit data block - Offset to nxt unit data blk - 
    vset = 0; t = 0ULL; break;
  case 010:	// %LDSWP - First swap unit - Offset to next swap unit - 
    vset = 0; t = 0ULL; break;
  case 011:	// %LDCRN - Number of 4-wd blks allocated at ONCE-only - 
    vset = 0; t = 0ULL; break;
  case 012:	// %LDSTP - Standard file protection - 
    vset = 0; t = 0ULL; break;
  case 013:	// %LDUFP - Standard UFD protection - 
    vset = 0; t = 0ULL; break;
  case 014:	// %LDMBN - Obsolete - 
    vset = 2; t = 0ULL; break;
  case 015:	// %LDQUS - SIXBIT queue structure name - 
    vset = 0; t = 0ULL; break;
  case 016:	// %LDCRP - CRASH PPN [10,1] - 
    vset = 1; t = 0000010000001ULL; break;
  case 017:	// %LDSFD - Maximum depth of SFDs to write - 
    vset = 0; t = 0ULL; break;
  case 020:	// %LDSPP - Spooled file protection - 
    vset = 0; t = 0ULL; break;
  case 021:	// %LDSYP - Standard SYS: protection - 
    vset = 0; t = 0ULL; break;
  case 022:	// %LDSSP - Standard SYS:filename.SYS protection - 
    vset = 0; t = 0ULL; break;
  case 023:	// %LDMNU - Maximum negative USETI that reads extended RIBs - 
    vset = 0; t = 0ULL; break;
  case 024:	// %LDMXT - Maximum blocks to transfer with 1 I/O operation - 
    vset = 0; t = 0ULL; break;
  case 025:	// %LDNEW - Experimental SYS PPN [1,5] - 
    vset = 1; t = 0000001000005ULL; break;
  case 026:	// %LDOLD - Old SYS PPN [1,3] - 
    vset = 1; t = 0000001000003ULL; break;
  case 027:	// %LDUMD - User-mode diagnostics PPN [6,10] - 
    vset = 1; t = 0000006000010ULL; break;
  case 030:	// %LDNDB - Default disk buffers in ring - 
    vset = 0; t = 0ULL; break;
  case 031:	// %LDMSL - Maximum units in active swapping list - 
    vset = 0; t = 0ULL; break;
  case 032:	// %LDALG - ALGOL library PPN [5,4] - 
    vset = 1; t = 0000005000004ULL; break;
  case 033:	// %LDBLI - BLISS library PPN [5,5] - 
    vset = 1; t = 0000005000005ULL; break;
  case 034:	// %LDFOR - FORTRAN library PPN [5,6] - 
    vset = 1; t = 0000005000006ULL; break;
  case 035:	// %LDMAC - MACRO source library PPN [5,7] - 
    vset = 1; t = 0000005000007ULL; break;
  case 036:	// %LDUNV - UNIVERSAL file library PPN [5,17] - 
    vset = 1; t = 0000005000017ULL; break;
  case 037:	// %LDPUB - Public user library PPN [1,6] - 
    vset = 1; t = 0000001000006ULL; break;
  case 040:	// %LDTED - Text editor library PPN [5,10] - 
    vset = 1; t = 0000005000010ULL; break;
  case 041:	// %LDREL - .REL file library PPN [5,11] - 
    vset = 1; t = 0000005000011ULL; break;
  case 042:	// %LDRNO - RUNOFF library PPN [5,12] - 
    vset = 1; t = 0000005000012ULL; break;
  case 043:	// %LDSNO - SNOBOL library PPN [5,13] - 
    vset = 1; t = 0000005000013ULL; break;
  case 044:	// %LDDOC - .DOC file library PPN [5,14] - 
    vset = 1; t = 0000005000014ULL; break;
  case 045:	// %LDFAI - FAIL library PPN [5,15] - 
    vset = 1; t = 0000005000015ULL; break;
  case 046:	// %LDMUS - Music library PPN [5,16] - 
    vset = 1; t = 0000005000016ULL; break;
  case 047:	// %LDDEC - Standard DIGITAL software [10,7] - 
    vset = 1; t = 0000010000007ULL; break;
  case 050:	// %LDSLP - AOBJN pointer to active swap list - 
    vset = 0; t = 0ULL; break;
  case 051:	// %LDBAS - BASIC library PPN [5,1] - 
    vset = 1; t = 0000005000001ULL; break;
  case 052:	// %LDCOB - COBOL library PPN [5,2] - 
    vset = 1; t = 0000005000002ULL; break;
  case 053:	// %LDMXI - PDP-11 library PPN [5,3] - 
    vset = 1; t = 0000005000002ULL; break;
  case 054:	// %LDNEL - NELIAC library PPN [5,20] - 
    vset = 1; t = 0000005000020ULL; break;
  case 055:	// %LDDMP - Dump PPN [5,21] - 
    vset = 1; t = 0000005000021ULL; break;
  case 056:	// %LDPOP - POP2 library PPN [5,22] - 
    vset = 1; t = 0000005000022ULL; break;
  case 057:	// %LDTST - TEST library PPN [5,23] - 
    vset = 1; t = 0000005000023ULL; break;
  case 060:	// %LDLSO* - If nonzero, call DAEMON to log soft overruns - 
    vset = 0; t = 0ULL; break;
  case 061:	// %LDMBR* - Massbus register pointers - 
    vset = 0; t = 0ULL; break;
  case 062:	// %LDBBP* - Pointer to BAT pointer - Channel terminal fail count - 
    vset = 0; t = 0ULL; break;
  case 063:	// %LDDBS - DBMS library PPN [5,24] - 
    vset = 1; t = 0000005000024ULL; break;
  case 064:	// %LDEXP* - Offset of expected channel term word in CDB - 
    vset = 0; t = 0ULL; break;
  case 065:	// %LDMIC - MIC macro library PPN [5,25] - 
    vset = 1; t = 0000005000025ULL; break;
  case 066:     // %LDTPS - Text processing system library PPN [5,26] - 
    vset = 1; t = 0000005000026ULL; break;
  case 067:	// %LDCTL - .CTL file library PPN [5,27] - 
    vset = 1; t = 0000005000027ULL; break;
  case 070:	// %LDGAM - Games library PPN [5,30] - 
    vset = 1; t = 0000005000030ULL; break;
  case 071:	// %LDACT - System accounting PPN [1,7] - 
    vset = 1; t = 0000001000007ULL; break;
  case 072:	// %LDAPL - APL library PPN [5,31] - 
    vset = 1; t = 0000001000031ULL; break;
  case 073:	// %LDECT - RIB error threshold - 
    vset = 0; t = 0ULL; break;
  case 074:	// %LDTOT - Total RIB errors - 
    vset = 0; t = 0ULL; break;
  case 075:	// %LDDOR - Addr of first dormant acc table,,addr of last dormant acc table - 
    vset = 0; t = 0ULL; break;
  case 076:	// %LDCOR - Addr first free 4-wd core blk,,0 - 
    vset = 0; t = 0ULL; break;
  case 077:	// %LDINT - Disk interference count - 
    vset = 0; t = 0ULL; break;
  case 0100:	// %LDD60 - D60 library PPN [5,32] - 
    vset = 1; t = 0000005000032ULL; break;
  case 0101:	// %LDERT - Obsolete - 
    vset = 2; t = 0ULL; break;
  case 0102:	// %LDPT1 - Obsolete - 
    vset = 2; t = 0ULL; break;
  case 0103:	// %LDPT2 - Obsolete - 
    vset = 2; t = 0ULL; break;
  case 0104:	// %LDLTH - Obsolete - 
    vset = 2; t = 0ULL; break;
  case 0105:	// %LDCDA - Offset of UNICDA in UDB - 
    vset = 0; t = 0ULL; break;
  case 0106:	// %LDDES - Offset of UNIDES in UDB - 
    vset = 0; t = 0ULL; break;
  case 0107:	// %LDPTR - Pointer to in-core copies of retrieval pointers - 
    vset = 0; t = 0ULL; break;
  case 0110:	// %LDMSS - Max strs in sys search list - Max strs in job search list - 
    vset = 0; t = 0ULL; break;
  case 0111:	// %LDSLB - Offset of UNISLB in UDB - 
    vset = 0; t = 0ULL; break;
  case 0112:	// %LDUTP - Define ersatz device UTP - 
    vset = 0; t = 0ULL; break;
  case 0113:	// %LDINI - INI PPN - 
    vset = 0; t = 0ULL; break;
  case 0114:	// %LDESZ - Obsolete - 
    vset = 2; t = 0ULL; break;
  case 0115:	// %LDKON - Pointer to first controller's data block - 
    vset = 0; t = 0ULL; break;
  case 0116:	// %LDLBF - Default number of disk buffers - 
    vset = 0; t = 0ULL; break;
  case 0117:	// %LDDVU - Offset to device unit number - 
    vset = 0; t = 0ULL; break;
  case 0120:	// %LDCSZ - Size of disk cache, in blocks - 
    vset = 0; t = 0ULL; break;
  case 0121:	// %LDRDC - Monitor cache block read calls - 
    vset = 0; t = 0ULL; break;
  case 0122:	// %LDRDH - Monitor cache block read hits - 
    vset = 0; t = 0ULL; break;
  case 0123:	// %LDWRC - Monitor cache block write calls - 
    vset = 0; t = 0ULL; break;
  case 0124:	// %LDWRH - Monitor cache block write hits - 
    vset = 0; t = 0ULL; break;
  case 0125:	// %LDHSF - CSHFND calls - 
    vset = 0; t = 0ULL; break;
  case 0126:	// %LDHSC - CSHFND collisions in hash table - 
    vset = 0; t = 0ULL; break;
  case 0127:	// %LDHSL - Length of cache hash table - 
    vset = 0; t = 0ULL; break;
  case 0130:	// %LDHST - Address of cache hash table - 
    vset = 0; t = 0ULL; break;
  case 0131:	// %LDCHD - Address of cache list header - 
    vset = 0; t = 0ULL; break;
  case 0132:	// %LDSPN - DDB offset for spooled file name - 
    vset = 0; t = 0ULL; break;
  case 0133:	// %LDSPM - DDB offset for spooled parameter block pointer - 
    vset = 0; t = 0ULL; break;
  case 0134:	// %LDBLK - DDB offset for I/O block number - 
    vset = 0; t = 0ULL; break;
  case 0135:	// %LDRSU - DDB offset to retrieval/acc blocks - 
    vset = 0; t = 0ULL; break;
  case 0136:	// %LDNMB - DDB offset for NMB of father SFD - 
    vset = 0; t = 0ULL; break;
  case 0137:	// %LDUPS - PPN for use by mail programs (UPS: device) - 
    vset = 0; t = 0ULL; break;
  case 0140:	// %LDSEB - Address of pointer to first system error block - 
    vset = 0; t = 0ULL; break;
  case 0141:	// %LDROD - Number of times a Data Request Block was not available - 
    vset = 0; t = 0ULL; break;
  case 0142:	// %LDFNT - Library PPN for printer fonts (FNT:) - 
    vset = 0; t = 0ULL; break;
  case 0143:	// %LDSET - Bit mask of disk sets mounted on the system. - 
    vset = 0; t = 0ULL; break;
  case 0144:	// %LDDET - First detached UDB - Offset to next UDB - 
    vset = 0; t = 0ULL; break;
  case 0145:	// %LDOCS - Original (configured) size of disk cache - 
    vset = 0; t = 0ULL; break;
  case 0146:	// %LDSRT - Swap read error threshold (compare with %LDECT) - 
    vset = 0; t = 0ULL; break;
  case 0147:	// %LDSRC - Swap read error count (compare with %LDTOT) - 
    vset = 0; t = 0ULL; break;
  case 0150:	// %LDADL - Header of doubly-linked list of active DRBs - 
    vset = 0; t = 0ULL; break;
  }

  // Dispatch

  switch(vset) {

  case 2:  // Assuming we're going to have an obsolete entry do error return

    WRITEMEM(jctx, ctx->AC, t);
    CHKERROR(jctx);
    return(OK_EXIT);  // Error return - obsolete entry

  case 0:  // Unimplemented - Whine

    printf("?T10_ciGETTAB - .GTLVD - Level D Disk Parameters - Unimplemented entry %o at PC %06o\n",
	   comarg, ctx->PC);
    WRITEMEM(jctx, ctx->AC, t);
    CHKERROR(jctx);
    return(OK_EXIT);  // Error return - unimplemented

  case 1:  // Success

    WRITEMEM(jctx, ctx->AC, t);
    CHKERROR(jctx);
    ctx->PC ++;
    return(OK_EXIT);  // Normal Return
  }

}


// 11    .GTCNF - System Configuration Table

int t10_ciGETTABdGTCNF(PCTX *ctx,int comarg,int gettab)
{
  int vset=0;
  BIGV t;
  int l;

  switch(comarg) {
  case 00:	//    %CNFG0  |          System name (1st of 5 ASCIZ words)           |
    l = strlen(t10_SYSNAME);
    t = packasciz(&t10_SYSNAME[0],l-0);
    vset = 1; break;
  case 01:	//    %CNFG1  |          System name (2nd of 5 ASCIZ words)           |
    l = strlen(t10_SYSNAME);
    t = packasciz(&t10_SYSNAME[5],l-5);
    vset = 1; break;
  case 02:	//    %CNFG2  |          System name (3rd of 5 ASCIZ words)           |
    l = strlen(t10_SYSNAME);
    t = packasciz(&t10_SYSNAME[10],l-10);
    vset = 1; break;
  case 03:	//    %CNFG3  |          System name (4th of 5 ASCIZ words)           |
    l = strlen(t10_SYSNAME);
    t = packasciz(&t10_SYSNAME[15],l-15);
    vset = 1; break;
  case 04:	//    %CNFG4  |          System name (5th of 5 ASCIZ words)           |
    l = strlen(t10_SYSNAME);
    t = packasciz(&t10_SYSNAME[20],l-20);
    vset = 1; break;
  case 05:	//    %CNDT0  |      System creation date (1st of 2 ASCIZ words)      |
    l = strlen(t10_SYSDATE);
    t = packasciz(&t10_SYSDATE[0],l-0);
    vset = 1; break;
  case 06:	//    %CNDT1  |      System creation date (2nd of 2 ASCIZ words)      |
    l = strlen(t10_SYSDATE);
    t = packasciz(&t10_SYSDATE[5],l-5);
    vset = 1; break;
  case 07:	//    %CNTAP  |             SIXBIT name of system device              |
    vset = 0; t = 0ULL; break;
  case 010:	//   %CNTIM  |             Encoded time of day in jiffies            |
    vset = 0; t = 0ULL; break;
  case 011:	//   %CNDAT  |          Encoded date (15-bit binary format)          |
    vset = 0; t = 0ULL; break;
  case 012:	//   %CNSIZ  |             System memory size (in words)             |
    vset = 0; t = 0ULL; break;
  case 013:	//   %CNOPR  |              SIXBIT name of operator TTY              |
    vset = 0; t = 0ULL; break;
  case 014:	//   %CNDEV  |    Start of DDB chain     |         Reserved          |
    vset = 0; t = 0ULL; break;
  case 015:	//   %CNSJN  |-(Max number of high segs) |Max number of current jobs |
    vset = 0; t = 0ULL; break;
  case 016:	//   %CNTWR  |        Two-register hardware and software flag        |
    vset = 0; t = 0ULL; break;
  case 017:	//   %CNSTS* |   Feature test switches   |       Switch states       |
    vset = 0; t = 0ULL; break;
  case 020:	//   %CNSER  |                  CPU0 serial number                   |
    vset = 0; t = 0ULL; break;
  case 021:	//   %CNNSM  |        Number of nanoseconds per memory cycle         |
    vset = 0; t = 0ULL; break;
  case 022:	//   %CNPTY  | Number of 1st PTY (CTY+1) | Number of PTYs in system  |
    vset = 0; t = 0ULL; break;
  case 023:	//   %CNFRE  |           Pointer to bit map of core blocks           |
    vset = 0; t = 0ULL; break;
  case 024:	//   %CNLOC  |          Address of low-segment core blocks           |
    vset = 0; t = 0ULL; break;
  case 025:	//   %CNSTB  |                       Obsolete                        |
    vset = 2; t = 0ULL; break;
  case 026:	//   %CNOPL  |     Pointer to line data block (LDB) of OPR TTY       |
    vset = 0; t = 0ULL; break;
  case 027:	//   %CNTTF  |              Pointer to TTY free chunks               |
    vset = 0; t = 0ULL; break;
  case 030:	//   %CNTTC  |   Number of TTY chunks    | Address of 1st TTY chunk  |
    vset = 0; t = 0ULL; break;
  case 031:	//   %CNTTN  |               Number of free TTY chunks               |
    vset = 0; t = 0ULL; break;
  case 032:	//   %CNLNS  |            Pointer to current command TTY             |
    vset = 0; t = 0ULL; break;
  case 033:	//   %CNLNP  |-Number of TTY+PTY+CTY lines | Addr of LINTAB          |
    vset = 0; t = 0ULL; break;
  case 034:	//   %CNVER  |                Monitor version number                 |
    vset = 0; t = 0ULL; break;
  case 035:	//   %CNDSC  |-Len of dataset ctrl tbl  |  Address of control table  |
    vset = 0; t = 0ULL; break;
  case 036:	//   %CNDLS  |                       Obsolete                        |
    vset = 2; t = 0ULL; break;
  case 037:	//   %CNCCI  |                       Obsolete                        |
    vset = 2; t = 0ULL; break;
  case 040:	//   %CNSGT  | Ptr to last dormant seg deleted to free a seg number  |
    vset = 0; t = 0ULL; break;
  case 041:	//   %CNPOK  |     Last location changed by a POKE. monitor call     |
    vset = 0; t = 0ULL; break;
  case 042:	//   %CNPUC  | Job that made last POKE.  |   Number of POKE.s made   |
    vset = 0; t = 0ULL; break;
  case 043:	//   %CNWHY  |    SIXBIT reason for last reload (operator input)     |
    vset = 0; t = 0ULL; break;
  case 044:	//   %CNTIC  |           Number of clock ticks per second            |
    vset = 0; t = 0ULL; break;
  case 045:	//   %CNPDB  |  Pointer to process data block (PDB) pointer tables   |
    vset = 0; t = 0ULL; break;
  case 046:	//   %CNRTC  |        Resolution of runtime clock (units/sec)        |
    vset = 0; t = 0ULL; break;
  case 047:	//   %CNCHN  | Ptr to channel data block |         Reserved          |
    vset = 0; t = 0ULL; break;
  case 050:	//   %CNLMX  |       Maximum number of logged-in jobs allowed        |
    vset = 0; t = 0ULL; break;
  case 051:	//   %CNBMX  |         Maximum number of batch jobs allowed          |
    vset = 0; t = 0ULL; break;
  case 052:	//   %CNBMN  |       Minimum number of jobs reserved to batch        |
    vset = 0; t = 0ULL; break;
  case 053:	//   %CNDTM  |        Date/time in universal date/time format        |
    vset = 0; t = 0ULL; break;
  case 054:	//   %CNLNM  |               Number of jobs logged in                |
    vset = 0; t = 0ULL; break;
  case 055:	//   %CNBNM  |            Number of batch jobs logged in             |
    vset = 0; t = 0ULL; break;
  case 056:	//   %CNYER  |                     Current year                      |
    vset = 0; t = 0ULL; break;
  case 057:	//   %CNMON  |                     Current month                     |
    vset = 0; t = 0ULL; break;
  case 060:	//   %CNDAY  |               Current day of the month                |
    vset = 0; t = 0ULL; break;
  case 061:	//   %CNHOR  |                  Current hour (0-23)                  |
    vset = 0; t = 0ULL; break;
  case 062:	//   %CNMIN  |                 Current minute (0-59)                 |
    vset = 0; t = 0ULL; break;
  case 063:	//   %CNSEC  |                 Current second (0-59)                 |
    vset = 0; t = 0ULL; break;
  case 064:	//   %CNGMT  |            Offset from Greenwich Mean Time            |
               //            |            (such that %CNGMT +%CNDTM = GMT)           |
    vset = 0; t = 0ULL; break;
  case 065:	//   %CNDBG_*|                     Debug status                      |
    vset = 0; t = 0ULL; break;
  case 066:	//   %CNFRU  |     Number of free core blocks in use by monitor      |
    vset = 0; t = 0ULL; break;
  case 067:	//   %CNTCM  |                Addr of last TTY chunk                 |
    vset = 0; t = 0ULL; break;
  case 070:	//   %CNCVN  |    Customer version number (JOBDAT loc. 136)          |
    vset = 0; t = 0ULL; break;
  case 071:	//   %CNDVN  |    DIGITAL version number (JOBDAT loc. 137)           |
    vset = 0; t = 0ULL; break;
  case 072:	//   %CNDFC  |      Number of DF10 data channels on the system       |
    vset = 0; t = 0ULL; break;
  case 073:	//   %CNRTD  |              Number of realtime devices               |
    vset = 0; t = 0ULL; break;
  case 074:	//   %CNHPQ  |            Number of high-priority queues             |
    vset = 0; t = 0ULL; break;
  case 075:	//   %CNLDB  |   TTY device data blk wrd pointing to line data blk   |
    vset = 0; t = 0ULL; break;
  case 076:	//   %CNMVO  |           Maximum vector offset for PISYS.            |
    vset = 0; t = 0ULL; break;
  case 077:	//   %CNMIP  |              Maximum priority for PISYS.              |
    vset = 0; t = 0ULL; break;
  case 0100:	//  %CNMER  |Offset of MTA err rep word |  Address of 1st MTA DDB   |
    vset = 0; t = 0ULL; break;
  case 0101:	//  %CNET1  |        User address of exec AC T1 (for DAEMON)        |
    vset = 0; t = 0ULL; break;
  case 0102:	//  %CNLSD  |           Length of short device data block           |
    vset = 0; t = 0ULL; break;
  case 0103:	//  %CNLLD  |           Length of long device data block            |
    vset = 0; t = 0ULL; break;
  case 0104:	//  %CNLDD  |           Length of disk device data block            |
    vset = 0; t = 0ULL; break;
  case 0105:	//  %CNEXM  |   Addr in JOBDAT of last Examine or Deposit command   |
    vset = 0; t = 0ULL; break;
  case 0106:	//  %CNST2* |             Software configuration flags              |
    vset = 0; t = 0ULL; break;
  case 0107:	//  %CNPIM  |              Minumum condition in PISYS.              |
    vset = 0; t = 0ULL; break;
  case 0110:	//  %CNPIL  |                Length of internal PITs                |
    vset = 0; t = 0ULL; break;
  case 0111:	//  %CNPIA  |                   Address of JBTPIA                   |
    vset = 0; t = 0ULL; break;
  case 0112:	//  %CNMNT* |                     Monitor type                      |
    vset = 0; t = 0ULL; break;
  case 0113:	//  %CNOCR  |    Addr of 1st CDR DDB    |   Offset to card count    |
    vset = 0; t = 0ULL; break;
  case 0114:	//  %CNOCP  |    Addr of 1st CDP DDB    |   Offset to card count    |
    vset = 0; t = 0ULL; break;
  case 0115:	//  %CNPGS  |          Unit of core allocation (in words)           |
    vset = 0; t = 0ULL; break;
  case 0116:	//  %CNMMX  |Maximum allowable CORMAX (total phys mem for all jobs  |
    vset = 0; t = 0ULL; break;
  case 0117:	//  %CNNSC  |              Number of scheduler classes              |
    vset = 0; t = 0ULL; break;
  case 0120:	//  %CNUTF  |             Exponential user time factor              |
    vset = 0; t = 0ULL; break;
  case 0121:	//  %CNHSO  |       Address of start of monitor high segment        |
    vset = 0; t = 0ULL; break;
  case 0122:	//  %CNHSL  |            Length of monitor high segment             |
    vset = 0; t = 0ULL; break;
  case 0123:	//  %CNNWC  | Number of words in core (highest addr of on-line mem) |
    vset = 0; t = 0ULL; break;
  case 0124:	//  %CNNXM  |    AOBJN pointer to NXMTAB used to scan for zeros     |
    vset = 0; t = 0ULL; break;
  case 0125:	//  %CNNDB  |          Addr of 1st network node data block          |
    vset = 0; t = 0ULL; break;
  case 0126:	//  %CNTKB  |           Offset in MTA KDB of addr of CDB            |
    vset = 0; t = 0ULL; break;
  case 0127:	//  %CNDDC  | Offset into TTY DDB of character counts (Obsolete)    |
    vset = 0; t = 0ULL; break;
  case 0130:	//  %CNHDL  |                  Obsolete                             |
    vset = 2; t = 0ULL; break;
  case 0131:	//  %CNBTX  |         Address of reload .CCL text for BOOT          |
    vset = 0; t = 0ULL; break;
  case 0132:	//  %CNTDB  |           Offset in MTA UDB of addr of DDBs           |
    vset = 0; t = 0ULL; break;
  case 0133:	//  %CNMTK  |  Address of first MTA KDB in system (Obsolete)        |
    vset = 2; t = 0ULL; break;
  case 0134:	//  %CNCPU  |         Number of CPUs monitor was built for          |
    vset = 0; t = 0ULL; break;
  case 0135:	//  %CNDJB  |             Byte pointer to jobno in DDB              |
    vset = 0; t = 0ULL; break;
  case 0136:	//  %CNSUP  |                     System uptime                     |
    vset = 0; t = 0ULL; break;
  case 0137:	//  %CNBCP  |                 Bootstrap CPU number                  |
    vset = 0; t = 0ULL; break;
  case 0140:	//  %CNBCL  |               Bootstrap CTY line number               |
    vset = 0; t = 0ULL; break;
  case 0141:	//  %CNNCR  |             Number of CPUs allowed to run             |
    vset = 0; t = 0ULL; break;
  case 0142:	//  %CNMBS  |     Monitor bootstrap file structure (from BOOT)      |
    vset = 0; t = 0ULL; break;
  case 0143:	//  %CNMBF  |              Monitor bootstrap file name              |
    vset = 0; t = 0ULL; break;
  case 0144:	//  %CNMBX  |           Monitor bootstrap file extension            |
    vset = 0; t = 0ULL; break;
  case 0145:	//  %CNMBD  |           Monitor bootstrap file directory            |
    vset = 0; t = 0ULL; break;
  case 0146:	//  %CNBPM  |     Maximum number of SNOOP. breakpoints allowed      |
    vset = 0; t = 0ULL; break;
  case 0147:	//  %CNMXF  |    First free virtual address above the monitor       |
    vset = 0; t = 0ULL; break;
  case 0150:	//  %CNLVO  |          Virtual address where LDBs start             |
    vset = 0; t = 0ULL; break;
  case 0151:	//  %CNHXC  |     Maximum number of FILOP. extended channels        |
    vset = 0; t = 0ULL; break;
  case 0152:	//  %CNVSH  |    Monitor virtual start address of high segment      |
    vset = 0; t = 0ULL; break;
  case 0153:	//  %CNRST  |       Universal date/time of last role switch         |
                //          |               on multiple CPU systems                 |
    vset = 0; t = 0ULL; break;
  case 0154:	//  %CNDCH  |              Offset into LDB of LDBDCH                |
    vset = 0; t = 0ULL; break;
  case 0155:	//  %CNSF1  |              Monitor bootstrap 1st SFD                |
    vset = 0; t = 0ULL; break;
  case 0156:	//  %CNSF2  |              Monitor bootstrap 2nd SFD                |
    vset = 0; t = 0ULL; break;
  case 0157:	//  %CNSF3  |              Monitor bootstrap 3rd SFD                |
    vset = 0; t = 0ULL; break;
  case 0160:	//  %CNSF4  |              Monitor bootstrap 4th SFD                |
    vset = 0; t = 0ULL; break;
  case 0161:	//  %CNSF5  |              Monitor bootstrap 5th SFD                |
    vset = 0; t = 0ULL; break;
  case 0162:	//  %CNFLN  |                TTY number of FRCLIN                   |
    vset = 0; t = 0ULL; break;
  case 0163:	//  %CNPNP  |                Pointer to PTY table                   |
    vset = 0; t = 0ULL; break;
  case 0164:	//  %CNCAT  |         Pointer to network link address table         |
    vset = 0; t = 0ULL; break;
  case 0165:	//  %CNLPD  |                   Length of PDB                       |
    vset = 0; t = 0ULL; break;
  case 0166:	//  %CNJPK* |             Max. size of JOBPEK transfers             |
    vset = 0; t = 0ULL; break;
  case 0167:	//  %CNDAE* |          Previous and current monitor versions        |
    vset = 0; t = 0ULL; break;
  case 0170:	//  %CNHSH  |             AOBJN pointer to ENQ. HSHTAB              |
    vset = 0; t = 0ULL; break;
  case 0171:	//  %CNACS  |           Offset to PDB for account string            |
    vset = 0; t = 0ULL; break;
  case 0172:	//  %CNTOP  |           Pointer to TRMOP. dispatch table            |
    vset = 0; t = 0ULL; break;
  case 0173:	//  %CNSFD  |                   Pointer to JBTSFD                   |
    vset = 0; t = 0ULL; break;
  case 0174:	//  %CNCIP  |                   Pointer to CIPWT                    |
    vset = 0; t = 0ULL; break;
  case 0175:	//  %CNPRV  |     Privilege word to be used by privileged jobs      |
                //          |                 (FRCLIN, INITIA)                      |
    vset = 0; t = 0ULL; break;
  case 0176:	//  %CNCV1  |      First word of CTERM version string (8-bit)       |
    vset = 0; t = 0ULL; break;
  case 0177:	//  %CNCV2  |     Second word of CTERM version string (8-bit)       |
    vset = 0; t = 0ULL; break;
  case 0200:	//  %CNLHN  |         Pointer to LAT host node data base            |
    vset = 0; t = 0ULL; break;
  case 0201:	//  %CNIVM  |         "AND" mask for .GTIMI/.GTIMO/.GTVIR           |
    vset = 0; t = 0ULL; break;
  case 0202:	//  %CNACB  |      Address of first Allocation Control Block        |
    vset = 0; t = 0ULL; break;
  case 0203:	//  %CNAHB  |      Address of first Allocation Header Block         |
    vset = 0; t = 0ULL; break;
  case 0204:	//  %CNIDB  |         Address of IPA20 DRAM dump buffer             |
    vset = 0; t = 0ULL; break;
  case 0205:	//  %CNDTT  |           System-default terminal type                |
    vset = 0; t = 0ULL; break;
  case 0206:	//  %CNSUM  |          System update, in milliseconds               |
    vset = 0; t = 0ULL; break;
  case 0207:	//  %CNREM  |          Offset of LDBREMs in Line Data Blocks        |
    vset = 0; t = 0ULL; break;
  case 0210:	// %CNK4S   |          Offset of UNIK4S in Line Data Blocks         |
    vset = 0; t = 0ULL; break;
  case 0211:	//  %CNOPT  |                 SIXBIT startup option                 |
    vset = 0; t = 0ULL; break;
  case 0212:	//  %CNDJN  |                   DAEMON job number                   |
    vset = 0; t = 0ULL; break;
  }

  // Dispatch

  switch(vset) {

  case 2:  // Assuming we're going to have an obsolete entry do error return

    WRITEMEM(jctx, ctx->AC, t);
    CHKERROR(jctx);
    return(OK_EXIT);  // Error return - obsolete entry

  case 0:  // Unimplemented - Whine

    printf("?T10_ciGETTAB - .GTCNF - System Configuration Table - Unimplemented entry %o at PC %06o\n",
	   comarg, ctx->PC);
    WRITEMEM(jctx, ctx->AC, t);
    CHKERROR(jctx);
    return(OK_EXIT);  // Error return - unimplemented

  case 1:  // Success

    WRITEMEM(jctx, ctx->AC, t);
    CHKERROR(jctx);
    ctx->PC ++;
    return(OK_EXIT);  // Normal Return
  }

}

_SUB int t10_CALLI_GETTAB(PCTX *ctx)
{

  BIGV t;

  int comarg;
  int gettab;

  t = READMEM(jctx, cAC);
  comarg = (int) LH(t);
  gettab = (int) RH(t);

  // Dispatch/Error table

  switch(gettab) {

  case dGTABS: 
    printf("?T10_ciGETTAB - .GTABS - Address Break Word"); 
    break;
  case dGTADR: 
    printf("?T10_ciGETTAB - .GTADR - Job Relocation and Protection"); 
    break;
  case dGTAOT: 
    printf("?T10_ciGETTAB - .GTAOT - ANF-10 Object Translation Table"); 
    break;
  case dGTBTX: 
    printf("?T10_ciGETTAB - .GTBTX - BOOT Text String"); 
    break;
  case dGTC0C: 
    printf("?T10_ciGETTAB - .GTC0C - CPU0 CPU Data Block Constants"); 
    break;
  case dGTC0V: 
    printf("?T10_ciGETTAB - .GTC0V - CPU0 CPU Data Block Variables"); 
    break;
  case dGTC1C: 
    printf("?T10_ciGETTAB - .GTC1C - CPU1 CPU Data Block Constants"); 
    break;
  case dGTC1V: 
    printf("?T10_ciGETTAB - .GTC1V - CPU1 CPU Data Block Variables"); 
    break;
  case dGTC2C: 
    printf("?T10_ciGETTAB - .GTC2C - CPU2 CPU Data Block Constants"); 
    break;
  case dGTC2V: 
    printf("?T10_ciGETTAB - .GTC2V - CPU2 CPU Data Block Variables"); 
    break;
  case dGTC3C: 
    printf("?T10_ciGETTAB - .GTC3C - CPU3 CPU Data Block Constants"); 
    break;
  case dGTC3V: 
    printf("?T10_ciGETTAB - .GTC3V - CPU3 CPU Data Block Variables"); 
    break;
  case dGTC4C: 
    printf("?T10_ciGETTAB - .GTC4C - CPU4 CPU Data Block Constants"); 
    break;
  case dGTC4V: 
    printf("?T10_ciGETTAB - .GTC4V - CPU4 CPU Data Block Variables"); 
    break;
  case dGTC5C: 
    printf("?T10_ciGETTAB - .GTC5C - CPU5 CPU Data Block Constants"); 
    break;
  case dGTC5V: 
    printf("?T10_ciGETTAB - .GTC5V - CPU5 CPU Data Block Variables"); 
    break;
  case dGTCAP: 
    printf("?T10_ciGETTAB - .GTCAP - Job Capability Word"); 
    break;
  case dGTCCM: 
    printf("?T10_ciGETTAB - .GTCCM - Site-Specific Commands"); 
    break;
  case dGTCHN: 
    printf("?T10_ciGETTAB - .GTCHN - Channel Data Block Offsets"); 
    break;
  case dGTCM2: 
    printf("?T10_ciGETTAB - .GTCM2 - SET Command Names"); 
    break;
  case dGTCMP: 
    printf("?T10_ciGETTAB - .GTCMP - Obsolete"); 
    break;
  case dGTCMT: 
    printf("?T10_ciGETTAB - .GTCMT - SET TTY Command Names"); 
    break;
  case dGTCMW: 
    printf("?T10_ciGETTAB - .GTCMW - SET WATCH Command Names"); 
    break;
  case dGTCNF: // .GTCNF - System Configuration Table"); 
    return(t10_ciGETTABdGTCNF(ctx,comarg,gettab));
    break;
  case dGTCNO: 
    printf("?T10_ciGETTAB - .GTCNO - Charge Number"); 
    break;
  case dGTCOJ: 
    printf("?T10_ciGETTAB - .GTCOJ - Obsolete"); 
    break;
  case dGTCOM: 
    printf("?T10_ciGETTAB - .GTCOM - Monitor Command Names"); 
    break;
  case dGTCOR: 
    printf("?T10_ciGETTAB - .GTCOR - Obsolete"); 
    break;
  case dGTCQP: 
    printf("?T10_ciGETTAB - .GTCQP - Scheduler Class Quota"); 
    break;
  case dGTCRS: 
    printf("?T10_ciGETTAB - .GTCRS - Hardware Status After Crash"); 
    break;
  case dGTCRT: 
    printf("?T10_ciGETTAB - .GTCRT - Class Runtime"); 
    break;
  case dGTCTX: 
    printf("?T10_ciGETTAB - .GTCTX - Context Table"); 
    break;
  case dGTCVL: 
    printf("?T10_ciGETTAB - .GTCVL - Current Page Limits"); 
    break;
  case dGTDBS: 
    printf("?T10_ciGETTAB - .GTDBS - Obsolete"); 
    break;
  case dGTDCD: 
    printf("?T10_ciGETTAB - .GTDCD - CONI/DATAI To Device Status Block"); 
    break;
  case dGTDCF: 
    printf("?T10_ciGETTAB - .GTDCF - Obsolete"); 
    break;
  case dGTDCN: 
    printf("?T10_ciGETTAB - .GTDCN - SET DEFAULT Command Argument(s)"); 
    break;
  case dGTDDB: 
    printf("?T10_ciGETTAB - .GTDDB - I/O Wait DDB"); 
    break;
  case dGTDDH: 
    printf("?T10_ciGETTAB - .GTDDH - Device Data Block Chain Headers"); 
    break;
  case dGTDEV: 
    printf("?T10_ciGETTAB - .GTDEV - Segment Device or Structure"); 
    break;
  case dGTDFL: 
    printf("?T10_ciGETTAB - .GTDFL - User Defaults for Job"); 
    break;
  case dGTDNT: 
    printf("?T10_ciGETTAB - .GTDNT - Queue Headers"); 
    break;
  case dGTDVL: 
    printf("?T10_ciGETTAB - .GTDVL - Obsolete"); 
    break;
  case dGTEBR: 
    printf("?T10_ciGETTAB - .GTEBR - EBOX Jiffy Remainder"); 
    break;
  case dGTEBT: 
    printf("?T10_ciGETTAB - .GTEBT - KL10 EBOX Time"); 
    break;
  case dGTEDN: 
    printf("?T10_ciGETTAB - .GTEDN - Ersatz Device Names"); 
    break;
  case dGTENQ: 
    printf("?T10_ciGETTAB - .GTENQ - ENQ/DEQ Statistics"); 
    break;
  case dGTEQJ: 
    printf("?T10_ciGETTAB - .GTEQJ - ENQ/DEQ Queue Header"); 
    break;
  case dGTETH: 
    printf("?T10_ciGETTAB - .GTETH - Ethernet Information"); 
    break;
  case dGTFET: 
    printf("?T10_ciGETTAB - .GTFET - Feature Test Settings"); 
    break;
  case dGTGTB: 
    printf("?T10_ciGETTAB - .GTGTB - GETTAB Immediate"); 
    break;
  case dGTIDX: 
    printf("?T10_ciGETTAB - .GTIDX - Range of GETTAB Tables"); 
    break;
  case dGTIMI: 
    printf("?T10_ciGETTAB - .GTIMI - Job Page Count"); 
    break;
  case dGTIMO: 
    printf("?T10_ciGETTAB - .GTIMO - Swapped-Out Page Count"); 
    break;
  case dGTIPA: 
    printf("?T10_ciGETTAB - .GTIPA - IPCF Statistics"); 
    break;
  case dGTIPC: 
    printf("?T10_ciGETTAB - .GTIPC - IPCF Miscellaneous Data"); 
    break;
  case dGTIPI: 
    printf("?T10_ciGETTAB - .GTIPI - PID for [SYSTEM]INFO"); 
    break;
  case dGTIPP: 
    printf("?T10_ciGETTAB - .GTIPP - IPCF Pointers and Counts"); 
    break;
  case dGTIPQ: 
    printf("?T10_ciGETTAB - .GTIPQ - IPCF Flags and Quotas"); 
    break;
  case dGTISC: 
    printf("?T10_ciGETTAB - .GTISC - Swap-In Scan Tables"); 
    break;
  case dGTJLT: 
    printf("?T10_ciGETTAB - .GTJLT - LOGIN Time for Job"); 
    break;
  case dGTJTC: 
    printf("?T10_ciGETTAB - .GTJTC - Job Type and Scheduler Class"); 
    break;
  case dGTKCT: 
    printf("?T10_ciGETTAB - .GTKCT - Job Kilo-Core Ticks"); 
    break;
  case dGTKDB: 
    printf("?T10_ciGETTAB - .GTKDB - Controller Data Block Chain Headers"); 
    break;
  case dGTLBS: 
    printf("?T10_ciGETTAB - .GTLBS - Large Buffer Size"); 
    break;
  case dGTLIM: 
    printf("?T10_ciGETTAB - .GTLIM - Time Limit and Batch Status"); 
    break;
  case dGTLOC: 
    printf("?T10_ciGETTAB - .GTLOC - Remote Station Number"); 
    break;
  case dGTLPN: 
    printf("?T10_ciGETTAB - .GTLPN - Logged-In Project-Programmer Numbers"); 
    break;
  case dGTLVD: //     .GTLVD - Level D Disk Parameters"); 
    return(t10_ciGETTABdGTLVD(ctx,comarg,gettab));
  case dGTMBR: 
    printf("?T10_ciGETTAB - .GTMBR - MBOX Jiffy Remainder"); 
    break;
  case dGTMBT: 
    printf("?T10_ciGETTAB - .GTMBT - KL10 MBOX Time"); 
    break;
  case dGTMVL: 
    printf("?T10_ciGETTAB - .GTMVL - Maximum Page Limits"); 
    break;
  case dGTNDA: 
    printf("?T10_ciGETTAB - .GTNDA - NDB Address"); 
    break;
  case dGTNDB: 
    printf("?T10_ciGETTAB - .GTNDB - Byte Pointers to Node Data Block"); 
    break;
  case dGTNM1: 
    printf("?T10_ciGETTAB - .GTNM1 - User Name (first 6 characters)"); 
    break;
  case dGTNM2: 
    printf("?T10_ciGETTAB - .GTNM2 - User Name (last 6 characters)"); 
    break;
  case dGTNSP: 
    printf("?T10_ciGETTAB - .GTNSP - Obsolete"); 
    break;
  case dGTNSW: 
    printf("?T10_ciGETTAB - .GTNSW - Nonswapping Data Table"); 
    break;
  case dGTNTP: 
    printf("?T10_ciGETTAB - .GTNTP - Network Performance Data"); 
    break;
  case dGTNXM: 
    printf("?T10_ciGETTAB - .GTNXM - Nonexistent Memory Bit Table"); 
    break;
  case dGTOBI: 
    printf("?T10_ciGETTAB - .GTOBI - WTO and Batch Data"); 
    break;
  case dGTODP: 
    printf("?T10_ciGETTAB - .GTODP - ONCE-only Disk Parameters"); 
    break;
  case dGTOSC: 
    printf("?T10_ciGETTAB - .GTOSC - Swap-Out Scan Tables"); 
    break;
  case dGTPC: 
    printf("?T10_ciGETTAB - .GTPC - Wait DDB and User PC"); 
    break;
  case dGTPDB: 
    printf("?T10_ciGETTAB - .GTPDB - Job PDB Word"); 
    break;
  case dGTPID: 
    printf("?T10_ciGETTAB - .GTPID - Process Communication ID (IPCF)"); 
    break;
  case dGTPPN: 
    printf("?T10_ciGETTAB - .GTPPN - Job's PPN"); 
    break;
  case dGTPRG:
    printf("?T10_ciGETTAB - .GTPRG - User Program Name"); 
    break;
  case dGTPRV:
    printf("?T10_ciGETTAB - .GTPRV - Job Privilege Flags"); 
    break;
  case dGTPTR: 
    printf("?T10_ciGETTAB - .GTPTR - Program To Run"); 
    break;
  case dGTQJB: 
    printf("?T10_ciGETTAB - .GTQJB - Obsolete"); 
    break;
  case dGTQQQ: 
    printf("?T10_ciGETTAB - .GTQQQ - Obsolete"); 
    break;
  case dGTRCT: 
    printf("?T10_ciGETTAB - .GTRCT - Disk Blocks Read"); 
    break;
  case dGTRDI: 
    printf("?T10_ciGETTAB - .GTRDI - Program Run Directory"); 
    break;
  case dGTRDV: 
    printf("?T10_ciGETTAB - .GTRDV - Program Run Device"); 
    break;
  case dGTRFN: 
    printf("?T10_ciGETTAB - .GTRFN - Program Run File name"); 
    break;
  case dGTRS0: 
    printf("?T10_ciGETTAB - .GTRS0 - First SFD in Run Path"); 
    break;
  case dGTRS1: 
    printf("?T10_ciGETTAB - .GTRS1 - Second SFD in Run Path"); 
    break;
  case dGTRS2: 
    printf("?T10_ciGETTAB - .GTRS2 - Third SFD in Run Path"); 
    break;
  case dGTRS3: 
    printf("?T10_ciGETTAB - .GTRS3 - Fourth SFD in Run Path"); 
    break;
  case dGTRS4: 
    printf("?T10_ciGETTAB - .GTRS4 - Fifth SFD in Run Path"); 
    break;
  case dGTRSP: 
    printf("?T10_ciGETTAB - .GTRSP - Response Counter Table"); 
    break;
  case dGTRTD: 
    printf("?T10_ciGETTAB - .GTRTD - Realtime Status Words"); 
    break;
  case dGTSCN: 
    printf("?T10_ciGETTAB - .GTSCN - Scanner Data"); 
    break;
  case dGTSDT: 
    printf("?T10_ciGETTAB - .GTSDT - Swapping Data Table"); 
    break;
  case dGTSGN: 
    printf("?T10_ciGETTAB - .GTSGN - High Segment Parameters"); 
    break;
  case dGTSG2: 
    printf("?T10_ciGETTAB - .GTSG2 - Obsolete"); 
    break;
  case dGTSID: 
    printf("?T10_ciGETTAB - .GTSID - Special PID Table"); 
    break;
  case dGTSJB: 
    printf("?T10_ciGETTAB - .GTSJB - DECnet Session Control Block Pointer"); 
    break;
  case dGTSLF: 
    printf("?T10_ciGETTAB - .GTSLF - GETTAB Table Data"); 
    break;
  case dGTSNA: 
    printf("?T10_ciGETTAB - .GTSNA - Last SEND ALL in 9-bit"); 
    break;
  case dGTSPA: 
    printf("?T10_ciGETTAB - .GTSPA - Scheduler Performance Data"); 
    break;
  case dGTSPL: 
    printf("?T10_ciGETTAB - .GTSPL - Spooling Control Flags"); 
    break;
  case dGTSPS: 
    printf("?T10_ciGETTAB - .GTSPS - Status of Subsequent Processors"); 
    break;
  case dGTSQ: 
    printf("?T10_ciGETTAB - .GTSQ - Obsolete"); 
    break;
  case dGTSQH: 
    printf("?T10_ciGETTAB - .GTSQH - Obsolete"); 
    break;
  case dGTSSC: 
    printf("?T10_ciGETTAB - .GTSSC - Scheduler Scan Tables"); 
    break;
  case dGTSST: 
    printf("?T10_ciGETTAB - .GTSST - Scheduler Statistics"); 
    break;
  case dGTST2: 
    printf("?T10_ciGETTAB - .GTST2 - Second Job Status Word"); 
    break;
  case dGTSTM: 
    printf("?T10_ciGETTAB - .GTSTM - Time of Last Reset"); 
    break;
  case dGTSTS: 
    printf("?T10_ciGETTAB - .GTSTS - Job Status Word"); 
    break;
  case dGTSWP: 
    printf("?T10_ciGETTAB - .GTSWP - Job Swapping Parameters"); 
    break;
  case dGTSYS: 
    printf("?T10_ciGETTAB - .GTSYS - System-Wide Data"); 
    break;
  case dGTTCN: 
    printf("?T10_ciGETTAB - .GTTCN - Terminal Class Names"); 
    break;
  case dGTTDB: 
    printf("?T10_ciGETTAB - .GTTDB - Obsolete"); 
    break;
  case dGTTIM: 
    printf("?T10_ciGETTAB - .GTTIM - User Runtime"); 
    break;
  case dGTTMP: 
    printf("?T10_ciGETTAB - .GTTMP - Obsolete"); 
    break;
  case dGTTNM: 
    printf("?T10_ciGETTAB - .GTTNM - Terminal Type Names"); 
    break;
  case dGTTRQ: 
    printf("?T10_ciGETTAB - .GTTRQ - Time in Run Queue"); 
    break;
  case dGTTTY: 
    printf("?T10_ciGETTAB - .GTTTY - Job's Controlling Terminal"); 
    break;
  case dGTUPM: 
    printf("?T10_ciGETTAB - .GTUPM - Physical Page Number of UPMP"); 
    break;
  case dGTUUC: 
    printf("?T10_ciGETTAB - .GTUUC - Monitor Calls Executed"); 
    break;
  case dGTVIR: 
    printf("?T10_ciGETTAB - .GTVIR - Job's Virtual Size"); 
    break;
  case dGTVKS: 
    printf("?T10_ciGETTAB - .GTVKS - Virtual Kilo-Core Ticks"); 
    break;
  case dGTVM: 
    printf("?T10_ciGETTAB - .GTVM - Virtual Memory Data"); 
    break;
  case dGTVRT: 
    printf("?T10_ciGETTAB - .GTVRT - Paging Rage"); 
    break;
  case dGTWCH: 
    printf("?T10_ciGETTAB - .GTWCH - Watch Bits"); 
    break;
  case dGTWCT: 
    printf("?T10_ciGETTAB - .GTWCT - Disk Blocks Written"); 
    break;
  case dGTWHY: 
    printf("?T10_ciGETTAB - .GTWHY - Operator Reload Comments"); 
    break;
  case dGTWSN: 
    printf("?T10_ciGETTAB - .GTWSN - Names of Wait States"); 
    break;
  default:
    printf("?T10_ciGETTAB - Unknown GETTAB %o",gettab);
    break;
  }
  
  printf(" [%o] at PC %06d\n",comarg,ctx->PC);

  return(OK_EXIT);  // This will return us at the error return

}
