#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "psr.h"

#include "t10vm.h"

/* File Mapping


   You can use eleven data modes when performing I/O.  These  data  modes
   are:

        *ASCII              *Image Binary
        *8-bit ASCII        *Binary
        *ASCII Line          Image Dump
        *Packed Image        Dump Records
        *Byte                Dump
        *Image              

   Data modes preceded by an asterisk (*) transmit data in  buffered  I/O
   mode.   Packed  Image  mode  transmits  data  in buffered I/O mode for
   terminals only.  The remaining  data  modes  do  not  use  the  normal
   buffering  scheme.   These  data  modes  are  sometimes referred to as
   unbuffered modes or, more commonly, dump I/O data modes.

   All data transmissions are performed in either buffered  I/O  mode  or
   dump  I/O mode.  Your program specifies the mode of transmission in an
   argument to the INIT, OPEN, FILOP., or SETSTS monitor call.  The  data
   modes are listed in Table 11-2, and every data mode that is applicable
   to each device is described in the chapter describing the device.


     0       .IOASC   ASCII         Disk,  terminal,   magnetic   tape,
                                    DECtape,  plotter, card punch, card
                                    reader, line  printer,  paper  tape
                                    punch, paper tape reader

     1       .IOASL   ASCII Line    Disk,  terminal,   magnetic   tape,
                                    DECtape,  plotter, card punch, card
                                    reader, line  printer,  paper  tape
                                    punch, paper tape reader

     2       .IOPIM   Packed Image  Terminal

     3       .IOBYT   Byte          Magnetic tape, ANF-10 network task

     4       .IOAS8   8-bit ASCII   Terminal, network line printer, PTY

     5                              Reserved for DEC

     6-7                            Reserved for customer

     10      .IOIMG   Image         Disk,  terminal,   magnetic   tape,
                                    DECtape,  plotter, card punch, card
                                    reader, line  printer,  paper  tape
                                    punch, paper tape reader

     11-12                          Reserved for DEC

     13      .IOIBN   Image binary  Disk, magnetic tape, line  printer,
                                    DECtape,  plotter, card punch, card
                                    reader,  paper  tape  punch,  paper
                                    tape reader

     14      .IOBIN   Binary        Disk, magnetic tape, line  printer,
                                    DECtape,  plotter, card punch, card
                                    reader,  paper  tape  punch,  paper
                                    tape reader

     15      .IOIDP   Image dump    Display

     16      .IODPR   Dump record   Disk, magnetic tape, DECtape

     17      .IODMP   Dump          Disk, magnetic tape, DECtape
   ______________________________________________________________________


  Open File for WRITE:

   Environment variable: TOPS10_DEFAULT_BINARY ASC or B36 (DEFAULT=B36)
      or tops10.ini variable 

   Environment variable will control what kind of binaries are
   written out.  Output will not be compressed by default.

   Environment variable: TOPS10_DEFAULT_ASCII UNIX ASC B36 (DEFAULT=UNIX)
      or tops10.ini variable 

   Environment variable will control what kind of file will be
   written for an ASCII file type.  If UNIX, it will convert
   to regular 8 bit ASCII.  Otherwise it will deal with it as
   if it was binary.

  Opens FILE.EXT for READ:

   file.ext.asc (ascii version of file)
   file.ext.asc.bz2 (ascii version of file)
   file.ext.asc.gz (ascii version of file)
   file.ext.b36 (36-bit binary version of file)
   file.ext.b36.bz2 (36-bit version of file)
   file.ext.b36.gz (36-bit version of file)
   file.ext (assuming a ascii UNIX file)
   FILE.EXT (upper case - assuming ascii UNIX file)

  Full Filename Parsing:

   DEVNAM:FILE.EXE[P,PN,SFD,SFD]<PROT>

   DEVNAM maps to environment variable TOPS10_DEVNAM (TOPS10_DSKA)
      or to tops10.ini value

DSK Disk
DTA Dectape
TTY Terminals
PTY
RDx
LPT - printer
CDR - card reader
PTR - papertape reader
LPT - plotters
DIS - display light pens
TSK - Network nodes
MPX - Multiplexed devices

OPR
NUL
CTY
TTY

*/

int endeq(char *instr, char *matstr)
{

  int il,ml;

  il = strlen(instr);
  ml = strlen(matstr);

  if (il<ml) 
    return(0);          // Can't match -- too short

  if (strcmp(&instr[il-ml],matstr)==0) return(1);

  return(0);

}

char *strdup_lc(char *inv)
{

  int i,l;
  char *outv;

  l = strlen(inv);

  outv = (char *) malloc(l+1);
  if (outv==NULL) return(NULL);

  for (i=0; i<=l; i++)   // get that last trailing null
    outv[i] = tolower(inv[i]);

  return(outv);
}

char *strdup_uc(char *inv)
{

  int i,l;
  char *outv;

  l = strlen(inv);

  outv = (char *) malloc(l+1);
  if (outv==NULL) return(NULL);

  for (i=0; i<=l; i++)   // get that last trailing null
    outv[i] = toupper(inv[i]);

  return(outv);
}

struct _search_list {
  char *mask;
} search_list[] = {

  // %f - filename
  // %u - uppercase filename
  // %l - lowercase filename
  // %e - default extension uc
  // %d - default extension lc

  { "%l" },
  { "%u" },
  { "%f" },

  { "%l.%d" },
  { "%u.%e" },
  { "%f.%d" },

  { "%l.bz2" },
  { "%u.bz2" },
  { "%f.bz2" },

  { "%l.%d.bz2" },
  { "%u.%e.bz2" },
  { "%f.%d.bz2" },

  { "%l.gz" },
  { "%u.gz" },
  { "%f.gz" },

  { "%l.%d.gz" },
  { "%u.%e.gz" },
  { "%f.%d.gz" },

  { "%l.asc" },
  { "%u.asc" },
  { "%f.asc" },

  { "%l.b36" },
  { "%u.b36" },
  { "%f.b36" },

  { "%l.%d.asc" },
  { "%u.%e.asc" },
  { "%f.%d.asc" },

  { "%l.%d.b36" },
  { "%u.%e.b36" },
  { "%f.%d.b36" },

  { "%l.asc.bz2" },
  { "%u.asc.bz2" },
  { "%f.asc.bz2" },

  { "%l.b36.bz2" },
  { "%u.b36.bz2" },
  { "%f.b36.bz2" },

  { "%l.%d.asc.bz2" },
  { "%u.%e.asc.bz2" },
  { "%f.%d.asc.bz2" },

  { "%l.%d.b36.bz2" },
  { "%u.%e.b36.bz2" },
  { "%f.%d.b36.bz2" },

  { "%l.asc.gz" },
  { "%u.asc.gz" },
  { "%f.asc.gz" },

  { "%l.b36.gz" },
  { "%u.b36.gz" },
  { "%f.b36.gz" },

  { "%l.%d.asc.gz" },
  { "%u.%e.asc.gz" },
  { "%f.%d.asc.gz" },

  { "%l.%d.b36.gz" },
  { "%u.%e.b36.gz" },
  { "%f.%d.b36.gz" },

  { NULL },

};

// Directly open a file - intended for unix interface to launch executables

FILE *pdp10_direct_open_read(char *fname,char *defext,
			     int *pop, int *fmt)
{

  struct stat sb;
  FILE *fiov;

  char *unixpath;
  char *fnamb,*launch;
  char piputil[200];
  int fformat;

  int i;

  char *fmt_f;
  char *fmt_u;
  char *fmt_l;
  char *fmt_e;
  char *fmt_d;
  char *fptr;

  *fmt = 0;

  fiov = NULL;

  // Build some buffers

  fnamb = (char *) malloc(strlen(fname) + 50);
  launch = (char *) malloc(strlen(fname) + 50);
  strcpy(fnamb,fname);

  // Get the path off the incoming file

  fptr = strrchr(fnamb,'/');
  if (fptr) {
    *fptr = '\0';
    unixpath = strdup(fnamb);
    fptr++;
  } else {
    unixpath = strdup(".");
    fptr = fnamb;
  }

  // Build substitution buffersn

  fmt_f = strdup(fptr);
  fmt_u = strdup_uc(fptr);
  fmt_l = strdup_lc(fptr);
  fmt_e = strdup_uc(defext);
  fmt_d = strdup_lc(defext);

  // Go through the search list

  for (i=0; search_list[i].mask!=NULL; i++) {
    char c[2],*p;

    // Implement format string in search list

    strcpy(fnamb, unixpath);
    strcat(fnamb, "/");
    c[1] = '\0';
    for (p = search_list[i].mask; *p != '\0'; p++) {
      c[0] = *p;
      if (c[0] == '%') {
	p++;
	if (*p=='f') strcat(fnamb,fmt_f);
	else
	  if (*p=='u') strcat(fnamb,fmt_u);
	  else
	    if (*p=='l') strcat(fnamb,fmt_l);
	    else
	      if (*p=='e') strcat(fnamb,fmt_e);
	      else
		if (*p=='d') strcat(fnamb,fmt_d);
		else
		  strcat(fnamb,"BUGBUG");

	continue;
      }
      strcat(fnamb,c);
    }

    // Does this particular file exist

    if (stat(fnamb,&sb)==0) {   

      // Determine if we need to read through a pipe (compression)

      *pop = 0;
      piputil[0] = '\0';

      if (endeq(fnamb,".bz2"))
	strcpy(piputil,"bzcat");	  
      if (endeq(fnamb,".gz"))
	strcpy(piputil,"zcat");	  

      if (piputil[0]) 
	*pop = 1;

      // Figure out what format the file is in

      fformat = INT_FILEFMT_UNIX;
      if (endeq(fnamb,".b36.bz2") || 
	  endeq(fnamb,".b36.gz") ||
	  endeq(fnamb,".b36")) fformat = INT_FILEFMT_B36;
    
      if (endeq(fnamb,".asc.bz2") || 
	  endeq(fnamb,".asc.gz") ||
	  endeq(fnamb,".asc")) fformat = INT_FILEFMT_ASC;

      switch(fformat) {
      case INT_FILEFMT_UNIX:
	//printf("[TVMOPN - Open for read: %s]\n",fnamb);
	fiov = fopen(fnamb,"rb");
	break;
      case INT_FILEFMT_ASC:
      case INT_FILEFMT_B36:
	//printf("[TVMOPN - Open %s via %s: %s]\n",
	//       fformat==INT_FILEFMT_ASC?"ASC":"B36",
	//       piputil,fnamb);
       
	// **********SECURITY WARNING**********
	// Potential here for illegal chars?
	// we might need to strip the filename here to avoid exploits

	strcpy(launch, piputil);
	strcat(launch, " ");
	strcat(launch, fnamb);     
	fiov = popen(launch, "r");

	free(fmt_d);
	free(fmt_e);
	free(fmt_l);
	free(fmt_u);
	free(fmt_f);
	free(unixpath);
	free(fnamb);
	free(launch);

	*fmt = fformat;

	return(fiov);

      }
    }
  }

  *fmt = 0;

  free(fmt_d);
  free(fmt_e);
  free(fmt_l);
  free(fmt_u);
  free(fmt_f);
  free(unixpath);
  free(fnamb);
  free(launch);

  //  printf("?TVMFNF - File not found: %s\n",fname);

  return(fiov);

}
