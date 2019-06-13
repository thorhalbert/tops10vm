// Simple File Handler

// OPEN, ENTER, LOOKUP, RENAME

#include "op.h"

#include "tops10-uuosym.h"

#include "tops10-monctx.h"

// Free a channel

int sfh_freechannel(PCTX *ctx,int chan)
{
  if (mCTX->clist[chan])
    free(mCTX->clist[chan]);
  mCTX->clist[chan] = NULL;

  return(0);
}

// Create the channel (0 success, 1 error)

int sfh_createchan(PCTX *ctx,int chan, int mode, BIGV opmod, BIGV opdev, BIGV opbuf, char *ov, int devtype)
{

  T10SFH *nsfh;

  // Allocate new channel structure
  nsfh = (T10SFH *) malloc(T10SFH_SIZE);
  if (nsfh==NULL) {
    printf("Cannot allocate a T10SFH\n");
    exit(100);
  }

  // Zero the area
  memset((void *) nsfh, 0, T10SFH_SIZE);

  nsfh->state = SFH_STATE_CLOSED;
  nsfh->devtype = devtype;
  nsfh->flags = 0;
  nsfh->filemode = mode;
  nsfh->dOPMOD = opmod;
  nsfh->dOPDEV = opdev;
  nsfh->dOPBUF = opbuf;
  strcpy(nsfh->devnam, ov);
  
  mCTX->clist[chan] = nsfh;

  return(0);
}

// Open a device (return 0 on success, 1 on error)

int sfh_opendevice(PCTX *ctx,int chan, int mode, BIGV opmod, BIGV opdev, BIGV opbuf, char *ov)
{

  int devtype;

  // Check to see if the channel is available

  if (mCTX->clist[chan])
    switch(mCTX->clist[chan]->state) {
    case SFH_STATE_CLOSED:
      sfh_freechannel(ctx,chan);  // Closed - so free it
      break;
    case SFH_STATE_OPEN:
    case SFH_STATE_FILE:
    default:
      return(1);              // channel in use 
    }

  devtype = SFH_DEVICE_UNKNOWN;

  if (strcmp(ov,"TTY   ")==0) devtype = SFH_DEVICE_TTY;

  /* 
     
  TTY permits the following modes:

   18-21   IO.ERR    Error flags.  These  are  returned  by  the  monitor
                     after an I/O operation that failed:

                     Flag   Symbol    Error

                      18    IO.IMP    Not assigned to a job for image
                                      mode input.
                      19    IO.DER    Ignore interrupts for 0.75 seconds.
                      20    IO.DTE    Echo failure on output.
                      21    IO.BKT    Character lost on input.

                     If all of these bits are set,  the  remote  node  to
                     which the terminal is connected has failed.
      23   IO.ACT    Device active.
      25   IO.ABS    Enable using break mask.  (Refer to Section 15.4.)
      26   IO.BKA    Break on all characters.  An IN or INPUT  call  will
                     terminate   on   the  first  character  typed,  thus
                     enabling character input mode.
      27   IO.TEC    Truth in echoing  mode.   This  causes  all  control
                     characters  to be output as themselves (for example,
                     the ESCAPE character is not echoed as $ but as octal
                     33).
      28   IO.SUP    Suppress echoing.
      29   IO.LEM    Enable  special  editor  mode.   This  causes   some
                     control  characters (CTRL/R, CTRL/H, CTRL/U, CTRL/W,
                     and DELETE) to be passed to the program and  ignored
                     by   the   monitor,   except  to  echo  the  control
                     characters and to act as break characters.
   32-35   IO.MOD    Data mode:


                        0   .IOASC    ASCII mode.
                        1   .IOASL    ASCII line mode.
                        2   .IOPIM    Packed image mode.
                        4   .IOAS8    8-bit ASCII mode.
			10   .IOIMG    Image mode. 
  */

  if (strcmp(ov,"DSK   ")==0) devtype = SFH_DEVICE_DSK;

  /*

  I/O status bits for disk are as follows:

   Bits      Symbol    Meaning

   18-21     IO.ERR    Error flags:

                       Flag      Symbol    Error

                       18        IO.IMP    Attempt to write on software
                                           write-locked file structure or
                                           software redundancy failure
                                           occurred.
                       19        IO.DER    Error detected by device.
                       20        IO.DTE    Hard data error.
                       21        IO.BKT    Block too large.

     22      IO.EOF    End of file.
     23      IO.ACT    Device active.
     29      IO.WHD    Write disk pack headers.
     30      IO.SYN    Synchronous I/O.
   32-35     IO.MOD    Data mode:

                       Code      Symbol    Meaning

                         0       .IOASC    ASCII mode.
                         1       .IOASL    ASCII line mode.
                        10       .IOIMG    Image mode.
                        13       .IOIBN    Image binary mode.
                        14       .IOBIN    Binary mode.
                        16       .IODPR    Dump record mode.
                        17       .IODMP    Dump mode.
  */


  //  if (strcmp(ov,"LPT   ")==0) devtype = SFH_DEVICE_LPT;

  /*
    The I/O status bits for the line printer are as follows:

    Bits   Symbol    Meaning

      23   IO.ACT    Device active.
      25   IO.SVF    Suppresses  the  vertical  format  unit  on  a  line
                     printer.   This  allows  LN01  fonts and graphics to
                     print correctly.  Refer  to  the  TOPS-10  Operating
                     System Commands Manual for information on using LN01
                     fonts.
      29   IO.SFF    Suppress formfeeds on OUT, OUTPUT, and CLOSE monitor
                     calls.
   32-35   IO.MOD    Data mode:

                     Code   Symbol    Meaning

                        0   .IOASC    ASCII mode.
                        1   .IOASL    ASCII line mode.
                        4   .IOAS8    8-bit ASCII mode, for network line
                                      printers only.
                       10   .IOIMG    Image mode.

  */

  //  if (strcmp(ov,"MTA   ")==0) devtype = SFH_DEVICE_MTA;

  /*
    The I/O status bits for magtapes are listed below.

    Bits   Symbol    Meaning

   18-21   IO.ERR    Error flags.  If all these bits are set,  the  error
                     was  detected  by  the  tape  label handler; use the
                     DEVOP. call to determine the extended error code.

                     Flag   Symbol    Error

                      18    IO.IMP    Output attempted on a write-locked
                                      unit, or an illegal operation was
                                      attempted.
                      19    IO.DER    Data was missed on the tape or the
                                      tape was bad, or the transport is
                                      hung.
                      20    IO.DTE    Parity error.
                      21    IO.BKT    The record read from the tape is
                                      too long for the buffer.

      22   IO.EOF    End-of-file mark found.  You  must  clear  this  bit
                     using  SETSTS  before  reading  further, or CLOSE to
                     reset the tape status.

      23   IO.ACT    Device active.

      24   IO.BOT    Beginning of tape.

      25   IO.EOT    Physical end of tape was encountered.  Physical  EOT
                     is  several  feet before the actual end of tape.  It
                     is seen when passed over on a write operation as  an
                     error  return  with  this bit set in the file status
                     word.  You must clear this bit and condition  (using
                     the  SETSTS call) before another write operation can
                     be successful.  Physical EOT is  not  seen  on  read
                     operations.   Physical  EOT  does  not  prevent your
                     program from writing off the end of tape.   If  your
                     program  does  not heed the physical EOT warning, it
                     is allowed to keep writing.  Logical  EOT  does  not
                     prevent  your  program  from  reading past it.  Your
                     program must check for two  consecutive  EOF  marks,
                     which indicates the logical EOT.

      26   IO.PAR    Parity:
                          0 = even (BCD only)
                          1 = odd

   27-28   IO.DEN    Density:
                          0 = standard
                          1 = 200 BPI
                          2 = 556 BPI
                          3 = 800 BPI

                     Other densities (1600, 6250) must  be  specified  by
                     setting  IO.DEN  to  0  on an OPEN, and then using a
                     TAPOP.  to set the desired density.

                     Odd parity is preferred.  The  user  program  should
                     specify  even parity only when creating a tape to be
                     read in binary coded decimal (BCD) on  another  type
                     of computer system.

      29   IO.NRC    Read without reread check.

   32-35   IO.MOD    Data mode.  Defines method  for  writing  data  into
                     buffers.  The modes are:

                     Code   Symbol    Meaning

                        0   .IOASC    ASCII mode.
                        1   .IOASL    ASCII line mode.
                        3   .IOBYT    Byte mode.
                       10   .IOIMG    Image mode.
                       13   .IOIBN    Image binary mode.
                       14   .IOBIN    Binary mode.
                       16   .IODPR    Dump record mode.
                       17   .IODMP    Dump mode. */


  //  if (strcmp(ov,"PTY   ")==0) devtype = SFH_DEVICE_PTY;

*/
  The I/O status bits for the PTY are:

    Bits   Symbol    Meaning

      21   IO.BKT    More output sent than was accepted by the PTY.
      23   IO.ACT    Device active.
      24   IO.PTI    Job is waiting to receive input.
      25   IO.PTO    Job is waiting to send output.
      26   IO.PTM    Subjob is in monitor mode.
   32-35   IO.MOD    Data mode:

                     Code   Symbol    Meaning

                        0   .IOASC    ASCII mode.
                        1   .IOASL    ASCII line mode.
                        2   .IOPIM    Packed image mode (for full-SCNSER
                                      PTYs only).
                        4   .IOAS8    8-bit ASCII mode.

*/

  //  if (strcmp(ov,"PLT   ")==0) devtype = SFH_DEVICE_PLT;
/*
  The I/O status bits for the plotter are as follows:

    Bits   Symbol    Meaning

      23   IO.ACT    Device active.
   32-35   IO.MOD    Data mode:

                     Code   Symbol    Meaning

                       0    .IOASC    ASCII mode.
                       1    .IOASL    ASCII line mode.
                      10    .IOIMG    Image mode.
                      13    .IOIBN    Image binary mode.
                      14    .IOBIN    Binary mode.
*/


  if (sfh_createchan(ctx,chan,mode,opmod,opdev,opbuf,ov,devtype)) return(1);

  switch(devtype) {
  case SFH_DEVICE_TTY:
    mCTX->clist[chan]->flags = SFH_FLAG_STDOUT;
    mCTX->clist[chan]->iv = stdin;
    mCTX->clist[chan]->ov = stdout;
    mCTX->clist[chan]->state = SFH_STATE_DEVICE;
    return(0);  // TTY is open
  case SFH_DEVICE_DSK:
    mCTX->clist[chan]->flags = 0;
    mCTX->clist[chan]->iv = NULL;
    mCTX->clist[chan]->ov = NULL;
    mCTX->clist[chan]->state = SFH_STATE_OPEN;
    return(0);  // DSK is open
  default:
    return(1);  // Unsupported device
  }
}


int t10_OPEN(PCTX *ctx)
{

  BIGV op_opmod,op_opdev,op_opbuf;
  char ov[7];
  char *d;

  op_opmod = READMEM(jctx, ctx->E + UUO_xOPMOD);
  CHKERROR(jctx);

  op_opdev = READMEM(jctx, ctx->E + UUO_xOPDEV);
  CHKERROR(jctx);

  op_opbuf = READMEM(jctx, ctx->E + UUO_xOPBUF);
  CHKERROR(jctx);

  printf("OPEN Chan = %o, ",SFHCHAN(ctx->AC));

  printf("OPMOD %06o %06o, ",
	 (int) LH(op_opmod),
	 (int) RH(op_opmod));

  switch (op_opmod & UUO_IOxMOD) {
  case UUO_xIOASC: d = ".IOASC ASCII mode (for any device except display)."; break;
  case UUO_xIOASL: d = ".IOASL ASCII line mode (for any device except display)."; break;
  case UUO_xIOPIM: d = ".IOPIM Packed image mode (terminal only)."; break;
  case UUO_xIOBYT: d = ".IOBYT Byte mode (magtape device only)."; break;
  case UUO_xIOAS8: d = ".IOAS8 8-bit ASCII mode (terminal, pseudo-terminal, and line printers only)."; break;
  case UUO_xIOIMG: d = ".IOIMG Image mode (for any except display device)."; break;
  case UUO_xIOIBN: d = ".IOIBN Image binary mode (for disk, DECtape, magtape, plotter, card device, or papertape device)."; break;
  case UUO_xIOBIN: d = ".IOBIN Binary mode (for same devices as .IOIBN)."; break;
  case UUO_xIOIDP: d = ".IOIDP Image dump mode (for display devices only)."; break;
  case UUO_xIODPR: d = ".IODPR Dump record mode (for disk, DECtape, or magtape devices)."; break;
  case UUO_xIODMP: d = ".IODMP Dump mode (for disk, DECtape, or magtape devices)."; break;
  default:
    d = "Unknown open mode"; break;
  }

  unpacksixhw((int)LH(op_opdev), &ov[0]);
  unpacksixhw((int)RH(op_opdev), &ov[3]);

  ov[6] = '\0';
  printf("OPDEV /%s/, ",ov);

  printf("OPBUF %06o %06o\n",
	 (int) LH(op_opbuf),
	 (int) RH(op_opbuf));
  printf("Mode=%s\n",d);

  switch (sfh_opendevice(ctx, SFHCHAN(ctx->AC), op_opmod & UUO_IOxMOD,
		       op_opmod, op_opdev, op_opbuf, ov)) {
  case 0:  // Success 
    ctx->PC += 1;  
    break;
  default:  // Error
    ctx->PC += 0;  
    break;
  }

  return(OK_EXIT);
}

// INIT - obsolete form of OPEN

int t10_INIT(PCTX *ctx)
{

  BIGV op_opmod,op_opdev,op_opbuf;
  char ov[7];
  char *d;

  op_opmod = ctx->E;

  op_opdev = READMEM(jctx, ctx->PC + 1);
  CHKERROR(jctx);

  op_opbuf = READMEM(jctx, ctx->PC + 2);
  CHKERROR(jctx);

  printf("Chan = %o, ",SFHCHAN(ctx->AC));

  printf("OPMOD %06o %06o, ",
	 (int) LH(op_opmod),
	 (int) RH(op_opmod));

  switch (op_opmod & UUO_IOxMOD) {
  case UUO_xIOASC: d = ".IOASC ASCII mode (for any device except display)."; break;
  case UUO_xIOASL: d = ".IOASL ASCII line mode (for any device except display)."; break;
  case UUO_xIOPIM: d = ".IOPIM Packed image mode (terminal only)."; break;
  case UUO_xIOBYT: d = ".IOBYT Byte mode (magtape device only)."; break;
  case UUO_xIOAS8: d = ".IOAS8 8-bit ASCII mode (terminal, pseudo-terminal, and line printers only)."; break;
  case UUO_xIOIMG: d = ".IOIMG Image mode (for any except display device)."; break;
  case UUO_xIOIBN: d = ".IOIBN Image binary mode (for disk, DECtape, magtape, plotter, card device, or papertape device)."; break;
  case UUO_xIOBIN: d = ".IOBIN Binary mode (for same devices as .IOIBN)."; break;
  case UUO_xIOIDP: d = ".IOIDP Image dump mode (for display devices only)."; break;
  case UUO_xIODPR: d = ".IODPR Dump record mode (for disk, DECtape, or magtape devices)."; break;
  case UUO_xIODMP: d = ".IODMP Dump mode (for disk, DECtape, or magtape devices)."; break;
  default:
    d = "Unknown open mode"; break;
  }

  unpacksixhw((int)LH(op_opdev), &ov[0]);
  unpacksixhw((int)RH(op_opdev), &ov[3]);
  ov[6] = '\0';

  printf("OPDEV /%s/, ",ov);

  printf("OPBUF %06o %06o\n",
	 (int) LH(op_opbuf),
	 (int) RH(op_opbuf));
  printf("Mode=%s\n",d);

  switch (sfh_opendevice(ctx, SFHCHAN(ctx->AC), op_opmod & UUO_IOxMOD,
		       op_opmod, op_opdev, op_opbuf, ov)) {
  case 0:  // Success 
    ctx->PC += 3;  
    break;
  default:  // Error
    ctx->PC += 2;  
    break;
  }

  return(OK_EXIT);
}

// RELEASE close file - single return

int t10_RELEAS(PCTX *ctx)
{

  // No action if file already closed

  if (mCTX->clist[SFHCHAN(ctx->AC)]==NULL) return(OK_EXIT);

  switch(mCTX->clist[SFHCHAN(ctx->AC)]->state) {
  case SFH_STATE_CLOSED:
    return(OK_EXIT);
  case SFH_STATE_OPEN:
  case SFH_STATE_FILE:
  default:
    printf("?T10_SFH - Need to close files with RELEASE - not implemented PC %06o\n",ctx->PC);
    cPSTAT = PSTAT_HALTED;
    return(OK_PSTAT);
  }

  return(OK_EXIT);

}

// INBUF set input buffers

int t10_INBUF(PCTX *ctx)
{

  if (mCTX->clist[SFHCHAN(ctx->AC)]==NULL) return(OK_EXIT);
  mCTX->clist[SFHCHAN(ctx->AC)]->inbufs = ctx->E;

  return(OK_EXIT);
}

// OUTBUF set input buffers

int t10_OUTBUF(PCTX *ctx)
{

  if (mCTX->clist[SFHCHAN(ctx->AC)]==NULL) return(OK_EXIT);
  mCTX->clist[SFHCHAN(ctx->AC)]->outbufs = ctx->E;

  return(OK_EXIT);

}
