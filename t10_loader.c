#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "psr.h"

#include "t10vm.h"

int load_executable(PCTX *ctx, char *infile, int *transaddr)
{

  int i;

  i = load_10exe(ctx, infile, transaddr);
  if (i==0) return(0);

  i = load_10sav(ctx, infile, transaddr);
  if (i==0) return(0);

  printf("\n?T10_LOADER - Cannot execute %s\n",infile);
  exit(100);

  return(i);
}

/*

Description:   The old .SAV, .LOW, .SHR, .HGH and .XPN files have been
                  replaced by the .EXE type in order to provide a unified
                  format for saved core image files.  This type  of  file
                  consists of two distinct but related portions:

                  1.  Information about the structure of the file

                  2.  The data in the file

   The format of an executable file created by the monitor can  have  the
   following sections:

                +-------------------------------------------------------+
                | Directory Section                                     |
                |-------------------------------------------------------|
                | Entry Vector Section (optional)                       |
                |-------------------------------------------------------|
                | End Vector Section                                    |
                |-------------------------------------------------------|
                | File data                                             |
                +-------------------------------------------------------+

   Each section is one or more words describing the  data  in  the  file,
   introduced  by  an  identifier code in the left half and the length of
   the chunk in the right half.  At this time, the defined codes are:

        1.  Directory:  1776

        2.  Entry Vector:  1775

        3.  End:  1777

   Other sections may be added later  as  they  become  necessary.   Each
   section is described below:

   The save file starts with a directory of the pages of data.  All pages
   of  data  are  stored  on page boundaries in exactly the form they are
   loaded into the virtual address space.  There is no  zero  compression
   within pages; only entire pages are compressed.

   The format of the directory is:

        Word    Map
                +-------------------------------------------------------+
        0       | 1776                     | Size of directory          |
                |-------------------------------------------------------|
        1       | Flags                    | File page number           |
                |-------------------------------------------------------|
        2       | Repeat                   | Process page number        |
                |-------------------------------------------------------|
                | Flags                    | File page number           |
                |-------------------------------------------------------|
                | Repeat                   | Process page number        |
                |-------------------------------------------------------|
                                       .   .   .
                |-------------------------------------------------------|
                | Entry Vector                                          |
                |-------------------------------------------------------|

   Word 0 has 1776 in the left half and the  size  of  the  directory  in
   words in the right half.

   Word 1 has flag bits in the leftmost nine bits and a file page  number
   in  the right 27 bits.  If the file page number is zero, then the page
   is allocated but zero.  The flag bits are:

   Bits      Symbol    Description

   0         SV%HIS    Set if part of hiseg.
   1         SV%SHR    Set if page is sharable.
   2         SV%WRT    Set if page may be written.
   3         SV%CON    Page is concealed (access by PORTAL only).
   4         SV%SYM    Page is part of symbol table (not used).
   5         SV%ABZ    Page is allocated but zero (internal flag).

   Word 2 has a repeat count in its leftmost nine bits for one less  than
   the  number  of  consecutive  file  and memory pages described by this
   pointer.  The rightmost nine bits describe the  process  address  into
   which this page should be loaded.  Words 1 and 2 are repeated for each
   contiguous portion of the process  space  that  has  identical  access
   bits.

   The directory section is followed by the entry  vector  section.   The
   entry  vector is described by a 3-word entry vector block.  Word 0 has
   the 1775 in the left half, and the word  count  of  the  entry  vector
   block in the right half.

        Word    Map
                +-------------------------------------------------------+
                | Directory Section                                     |
                |-------------------------------------------------------|
        0       | 1775                     | Word count                 |
                |-------------------------------------------------------|
        1       | (JRST)                                                |
                |-------------------------------------------------------|
        2       | 30-bit Start Address                                  |
                |-------------------------------------------------------|
                | End Vector                                            |
                |-------------------------------------------------------|

   The entry vector is included only for multi-section programs.   It  is
   written in the following format by default:

   Word 0 contains the code (1775) in the left half and the word count of
   the entry vector block (always 3) in the right half).

   Word 1 contains the value 254000, which is the value of JRST with  the
   halves reversed.

   Word 2 contains the 30-bit starting address for the program.

   Alternate forms of the entry vector block can be written.   The  entry
   vector  block  then  points to the entry vector.  In this case, Word 1
   contains the length of the entry  vector,  and  Word  2  contains  the
   address of the entry vector.  The address in Word 2 points to an Entry
   Vector, in the following format:

                +-------------------------------------------------------+
                | 30-bit Start Address                                  |
                |-------------------------------------------------------|
                | 30-bit Reenter Address                                |
                |-------------------------------------------------------|
                | Version number of program                             |
                +-------------------------------------------------------+

   The entry vector block is followed by the End Block.   The  End  Block
   word has the value 1777,,1.

   The End Block is followed by the file data.

*/

int load_10exe(PCTX *ctx, char *infile, int *transaddr)
{

  FILE *inexe;
  int pop, fmt;
  int i,j,dirlen,dircod;
  BIGV *exe_dir;
  BIGV *pagebuf;
  BIGV t;
  int highmark;
  int readpage;
  int try;
  int ta;

  struct _dirlist {
    int exepage;
    int ppnpage;
    int flags;
    int rep;
  } dirlist[256];
  int dirc=0;

  jctx->hiseg_floor = 0;    // Find the hiseg floor from the EXE file

  for (i=0; i<256; i++) 
    dirlist[i].exepage = dirlist[i].ppnpage = dirlist[i].flags = dirlist[i].rep = 0;
  dirc = 0;

  inexe = pdp10_direct_open_read(infile,"EXE", &pop, &fmt);
  if (inexe==NULL) return(1);

  if (fmt==INT_FILEFMT_UNIX) {
    printf("?T10_LOADER - File %s is not in a 36 bit binary format\n",infile);
    exit(100);
  }

  exe_dir = (BIGV *) malloc(sizeof (BIGV) * PAGE_SIZE);
  assert(exe_dir);

  pagebuf = (BIGV *) malloc(sizeof (BIGV) * PAGE_SIZE);
  assert(pagebuf);

  // Read in page 0 of exe file

  i = read36unix(inexe, fmt, PAGE_SIZE, exe_dir);
  if (i!=PAGE_SIZE) {
    printf("?T10_LOADER - Bad format (no initial directory)\n");
    exit(100);
  }

  readpage = 0;

  dircod = LH(exe_dir[0]);
  dirlen = RH(exe_dir[0]);

  if (dircod!=UUO_xSVDIR) {
    printf("?T10_LOADER - Files does not start with an EXE directory\n");
    exit(100);
  }
   
  // Look for a possible start block

  ta = 0;

  if (LH(exe_dir[dirlen])!=UUO_xSVEND ||
      RH(exe_dir[dirlen])!=1) {
    if (LH(exe_dir[dirlen])==UUO_xSVSTA &&
	RH(exe_dir[dirlen])==3) { 
      if (exe_dir[dirlen+1]==0254000)
	ta = RH(exe_dir[dirlen+2]);
      if (LH(exe_dir[dirlen+3])!=UUO_xSVEND ||
	  RH(exe_dir[dirlen+3])!=1) {
	printf("?T10_LOADER - Found another block after start - what? - need to deal with this now\n");
	exit(100);
      }
    } else {
      printf("?T10_LOADER - Found a directory with no end block or start block - need to deal with this now\n");
      exit(100);
    }
  }

  // Decode the catalog

  highmark = 0;

  for (i=1; i<dirlen-1; i+=2) {
    BIGV pagenum,exepage,rc;
    unsigned int pageflags;
    int maxp;

    exepage = exe_dir[i] & RBIT23;
    pageflags = 0;

    if (exe_dir[i] & UUO_SV_HIS) pageflags |= PAGE_HISEG;
    if (exe_dir[i] & UUO_SV_SHR) pageflags |= PAGE_SHARABLE;
    if (exe_dir[i] & UUO_SV_WRT) pageflags |= PAGE_WRITABLE;
    if (exe_dir[i] & UUO_SV_CON) pageflags |= PAGE_CONCEALED;
    if (exe_dir[i] & UUO_SV_SYM) pageflags |= PAGE_SYMBOL;
    if (exepage==0) pageflags |= PAGE_CLEARED;

    rc = LH(exe_dir[i+1]);
    rc >>= 9;
    pagenum = exe_dir[i+1] & RBIT23;

    dirlist[dirc].exepage = (int) exepage;
    dirlist[dirc].ppnpage = (int) pagenum;
    dirlist[dirc].flags = pageflags;
    dirlist[dirc].rep = (int) rc + 1;

    maxp = dirlist[dirc].exepage + dirlist[dirc].rep;
    if (maxp > highmark) highmark = maxp;
    dirc++;

    // Figure out the low water mark to find out where the 
    //  hiseg_floor is - assumes pages are in order

    if (exe_dir[i] & UUO_SV_HIS) {
      if (jctx->hiseg_floor==0)
	jctx->hiseg_floor = pagenum * PAGE_SIZE;
      else
	if (jctx->hiseg_floor > (pagenum * PAGE_SIZE)) {
	  printf("?T10_LOADER Pages in EXE file out of order????\n");
	  exit(100);
	}
    }
  }

  // Print out the directory

  for (i=0; i<dirc; i++) {
    printf("Chunk %d: Exe-Page=%o PPN-Page=%o Repeat=%o [ ",i+1,
	   dirlist[i].exepage,
	   dirlist[i].ppnpage,
	   dirlist[i].rep);

    if (dirlist[i].flags & PAGE_HISEG) printf("HISEG ");
    if (dirlist[i].flags & PAGE_SHARABLE) printf("SHARABLE ");
    if (dirlist[i].flags & PAGE_WRITABLE) printf("WRITABLE ");
    if (dirlist[i].flags & PAGE_CONCEALED) printf("CONCEALED ");
    if (dirlist[i].flags & PAGE_SYMBOL) printf("SYMBOL ");
    if (dirlist[i].flags & PAGE_CLEARED) printf("CLEARED ");

    printf("]\n");
  }

  printf("[EXE File last page is %o]\n",highmark);

  // Create and process the empty pages

  for (i=0; i<dirc; i++) {
    if (dirlist[i].exepage==0) {
      for (j=0; j<dirlist[i].rep; j++) {
	create_page(jctx, dirlist[i].ppnpage + j, 
		    dirlist[i].flags);
	CHKERROR(jctx);
      }
    }
  }

  // Load up the file

  while (readpage < highmark-1) {  // Loop through the file

    i = read36unix(inexe, fmt, PAGE_SIZE, pagebuf);
    if (i!=PAGE_SIZE) {
      printf("?T10_LOADER - Error reading in body\n");
      exit(100);
    }

    readpage ++;
    //    printf("[Exe File Read %o] - ",readpage);
    
    try = 0;

    for (i=0; i<dirc; i++) {

      if (dirlist[i].exepage==0) continue;   // We've dealt with these

      if (readpage >= dirlist[i].exepage &&
	  readpage < (dirlist[i].exepage + dirlist[i].rep)) {
	int subpage;

	subpage = readpage - dirlist[i].exepage;

	create_page(jctx, dirlist[i].ppnpage + subpage, 
		    dirlist[i].flags);
	CHKERROR(jctx);
	try = 1;

	//	printf("[Write Page %o]\n",dirlist[i].ppnpage+subpage);
	write_page(jctx, dirlist[i].ppnpage + subpage, pagebuf); 

	break;  // we found our directory -- loop out
      }
    }

    if (try==0) 
      printf("Couldn't find page %o in directory\n",readpage);
  }

  if (pop)
    pclose(inexe);
  else
    fclose(inexe);

  printf("[End loading %s]\n",infile);

  t = READMEM(jctx, 0120); // .JBSA
  CHKERROR(jctx);

  if (jctx->hiseg_floor <= 0)
    jctx->hiseg_floor = 0400000;

  printf("[Transfer address is %06o Hiseg is %06o]\n",(int) RH(t),
	 jctx->hiseg_floor);

  *transaddr = (int) RH(t);

  return(0);
}

int load_10sav(PCTX *ctx, char *infile, int *transaddr)
{

  FILE *inexe;
  int pop, fmt;
  BIGV rt;
  int le,re,lh,rh;
  int lw=0,hwm=0;
  BIGV blv;
  int npage,opage = -1;

  *transaddr = 0;
  jctx->hiseg_floor = 0;    // Find the hiseg floor from the EXE file

  inexe = pdp10_direct_open_read(infile,"SAV", &pop, &fmt);
  if (inexe==NULL) return(1);

  if (fmt==INT_FILEFMT_UNIX) {
    printf("?T10_LOADER - File %s is not in a 36 bit binary format\n",infile);
    exit(100);
  }

  // Read in first word of file

  while (!feof(inexe)) {
    int i;
    i = read36unix(inexe, fmt, 1, &rt);
    if (i!=1) {
      printf("?T10_LOADER - Bad SAV format (no initial directory)\n");
      exit(100);
    }

    lh = le = (int) LH(rt);
    rh = re = (int) RH(rt);

    if (lh&0400000) le |= 037777000000;

    if (le==0254000) {
      /*printf("Transfer Address = %o\n",re);*/
      *transaddr = re;
      break;
    }

    if (le>=0) {
      printf("?T10_LOADER - SAV Not a count! %o,,%o\n", lh,rh);
      exit(10);
    }

    /*printf("Load %d words at %o\n",-le,re+1);*/
    lw += -le;

    for (i=0; i<(-le); i++) {
      int t;
      t = read36unix(inexe, fmt, 1, &rt);
      if (t!=1) {
	printf("?T10_LOADER - Bad SAV format (no initial directory)\n");
	exit(100);
      }

      lh = (int) LH(rt);
      rh = (int) RH(rt);

      blv = lh & RWM;
      blv <<= 18;
      blv |= rh & RWM;

      npage = PAGENUM(re+i+1);
      if (opage != npage)
	create_page(jctx, npage, 0);

      WRITEMEM(jctx, re+i+1, blv);
      CHKERROR(jctx);

      // printf("%o/ %o,,%o  %llo\n",re+i+1,lh,rh,blv);
      if (re+i+1>hwm) hwm = re+i+1;
    }
  }

  printf("[%d Words Loaded From %s]\n",lw,infile);
  printf("[Loader High-Water-Mark is %o]\n",hwm);

  if (pop)
    pclose(inexe);
  else
    fclose(inexe);

  printf("[End loading %s]\n",infile);
  
  if (*transaddr) {
    WRITEMEM(jctx, 0120, *transaddr);
    CHKERROR(jctx);
  }

  rt = READMEM(jctx, 0120); // .JBSA
  CHKERROR(jctx);

  if (jctx->hiseg_floor <= 0)
    jctx->hiseg_floor = 0400000;

  printf("[Transfer address is %06o Hiseg is %06o]\n",(int) RH(rt),
	 jctx->hiseg_floor);

  *transaddr = (int) RH(rt);

  return(0);
}

#if 0
int load_10sav(PCTX *ctx,char *infile)
{

  int lh,rh,le,re;
  FILE *inpo;
  int lw=0,hwm=0;
  BIGV blv;

  int transfer_address;

  char *botc;

  botc = (char *) malloc(strlen(infile) + 20);
  strcpy(botc, "bzcat ");
  strcat(botc, infile);

  inpo = popen(botc,"r");
  if (inpo==NULL) {
    printf("?T10_LOADER - Cannot open pipe %s\n",inpo);
    exit(10);
  }

  while (!feof(inpo)) {
    int i;
    fscanf(inpo,"%o,,%o",&lh,&rh);

    le = lh;
    re = rh;

    if (lh&0400000) le |= 037777000000;

    if (le==0254000) {
      /*printf("Transfer Address = %o\n",re);*/
      transfer_address = re;
      break;
    }

    if (le>=0) {
      printf("?T10_LOADER - Not a count! %o,,%o\n", lh,rh);
      exit(10);
    }

    /*printf("Load %d words at %o\n",-le,re+1);*/
    lw += -le;

    for (i=0; i<(-le); i++) {
      fscanf(inpo,"%o,,%o",&lh,&rh);

      blv = lh & RWM;
      blv <<= 18;
      blv |= rh & RWM;

      WRITEMEM(jctx, re+i+1, blv);
      CHKERROR(jctx);

      // printf("%o/ %o,,%o  %llo\n",re+i+1,lh,rh,blv);
      if (re+i+1>hwm) hwm = re+i+1;
    }
  }

  pclose(inpo);

  printf("[%d Words Loaded From %s]\n",lw,infile);
  printf("[Loader High-Water-Mark is %o]\n",hwm);

  return(0);
}
#endif

