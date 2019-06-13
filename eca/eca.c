

#include "eca.h"

/*

         symbol contains A-Z 0-9 _ . $ %
         number base is octal

         Parser tokens:

             symbol:
	     }
             keyword 
             opcode


	 Keywords:

	     INCLUDE
	     OPDEF
	     VALUE
	     LITERAL
	     CONTEXT
	     ASCIZ
	     SIXBIT
	     XWD


---------------------------------


          Version Zero Syntax



          :LABEL
          // Comment
          - operator accum, address
          KEYWORD
	         OPDEF op=opname accum, address
                 VALUE nam=value
                 ASCIZ del chars del
		 SIXBIT del chars del
		 INCLUDE file
		 SEARCH file  -- doesn't scan for pass 2
		 XWD a,b
		 WORD a

	       address
	             label +/- number
		     value +/- number
		     . +/- number

*/

int pass;   // Two pass assembler
int fatalerror=0;

int startaddr = 0400;
int curloc = 0400;   // Default starting address of global context area
int hiwater=0;

#define EWS(a) while (isspace(*a)) a++

SYMBOL *sroot=NULL,*stail=NULL;

int eatfile(char *infile);
char *eatsym(char *ib, char *outs);

int isoctal(int ic)
{

  if (ic<'0') return(0);
  if (ic>'7') return(0);
  return(1);
}

int parseerror(FILET *inft,char *buf,char *err)
{
  
  printf("?ECA - %s:%d - ",inft->ifile,inft->filenum);
  printf("%s - %s\n",buf,err);
  fatalerror = 1;
  return(1);
}

void dumpsym()
{


  int lh,rh;
  SYMBOL *insym,*loop;

  for (loop=sroot; loop!=NULL; loop=loop->next) {
    switch(loop->symtype) {
    case SYM_VALUE:
    case SYM_OPDEF:
      if (loop->use==0) continue;
      break;
    }

    lh = LH(loop->value);
    rh = RH(loop->value);

    printf("%-20s %06o %06o ",
	   loop->symname,
	   lh,rh);

    switch(loop->symtype) {
    case SYM_VALUE:
      printf("VALUE"); break;
    case SYM_UNKNOWN: 
      printf("UNKNOWN"); break;
    case SYM_UNDEF: 
      printf("UNDEF"); break;
    case SYM_OPDEF:
      printf("OPDEF"); break;
    case SYM_LABEL: 
      printf("LABEL"); break;
    default:
      printf("HUH?");
    }
    printf("%4d\n",loop->use);
  }
  return;

}

WORD36 *osav;
int savsiz = -1;
int savpag = 0;

void saveloc(int pc,WORD36 opw)
{

  int i;

  if (savsiz < 0) {
    savsiz = hiwater + 511;
    savsiz >>= 9;
    if (savsiz <= 1) savsiz = 1;
    savpag = savsiz;
    savsiz <<= 9;

    osav = (WORD36 *) malloc((sizeof (WORD36)) * savsiz);
    if (osav==NULL) {
      printf("Unable to allocate %d words for output buffer\n",savsiz);
      exit(100);
    }
    for (i=0; i<savsiz; i++)
      osav[i] = 0ULL;
  }

  osav[pc] = opw;
}

void outexe(char *ofile)
{

  FILE *oiov;
  int i,dv;
  int lh,rh;

  oiov = fopen(ofile,"w");
  if (oiov==NULL) {
    printf("Cannot open output file %s\n",ofile);
    exit(100);
  }

  dv = 0;

  fprintf(oiov,"1776,,3\n"); // Dir header
  fprintf(oiov,"100000,,1\n"); // Writable file page 1
  fprintf(oiov,"%o,,0\n", (savpag - 1) << 9);
  fprintf(oiov,"1777,,1\n");
  
  for (i=0; i<512 - 4; i++)
    fprintf(oiov,"0,,0\n");

  for (i=0; i<savsiz; i++) {
    lh = LH(osav[i]);
    rh = RH(osav[i]);
    fprintf(oiov,"%o,,%o\n",lh,rh);
  }

  fclose(oiov);
  
}

SYMBOL *findsym(char *sym,int inc)
{

  SYMBOL *loop;

  for (loop=sroot; loop!=NULL; loop=loop->next) 
    if (strcmp(sym, loop->symname)==0) {
      loop->use += inc;
      return(loop);
    }
  return(NULL);

}

int addsym(FILET *inft, char *sym, WORD36 inword, int symtype)
{

  int lh,rh;
  SYMBOL *insym,*loop;

  lh = LH(inword);
  rh = RH(inword);

  // printf("Add symbol: %s\tat addr %06o %06o\n",sym, lh,rh);

  insym = findsym(sym,0);

  // Symbol never seen before

  if (insym==NULL) {
    insym = (SYMBOL *) malloc(sizeof(SYMBOL));
    if (insym==NULL) {
      printf("?ECA - %s:%d - ",inft->ifile,inft->filenum);
      printf("no memory - addsym\n");
      exit(100);
    }

    insym->symname = strdup(sym);
    insym->symtype = symtype;
    insym->symflags = 0;
    insym->value = inword;
    insym->next = NULL;
    insym->use = 0;

    // This linearly searched linked list of course sucks totally

    if (sroot)
      stail->next = insym;
    else
      sroot = insym;
    stail = insym;
    return(0);
  }

  // Reconcile symbol with existing entry in table

  if (symtype==SYM_VALUE) {

    // VALUEs are permitted to be changed
    if (insym->symtype==SYM_VALUE) {
      int lh1,rh1,lh2,rh2;

      lh1 = (int) LH(insym->value);
      rh1 = (int) RH(insym->value);
      lh2 = (int) LH(inword);
      rh2 = (int) RH(inword);

      if (insym->value==inword) return(0);  // No changes -- no error

      printf("%%ECA - %s:%d - ",inft->ifile,inft->filenum);
      printf("Symbol Value %s changed from %06o,,%06o to %06o,,%06o\n",
	     insym->symname,lh1,rh1,lh2,rh2);
      insym->value = inword;
      return(0);
    }

    printf("?ECA - %s:%d - ",inft->ifile,inft->filenum);
    printf("Value name %s already exists -- cannot redefine\n",insym->symname);
    fatalerror = 1;
    return(1);
  }

  if (symtype==SYM_LABEL) {
    
    // Labels can make undefined things defined
    if (insym->symtype==SYM_UNKNOWN) {
      insym->symtype = symtype;
      insym->value = inword;
      return(0);
    }

    // Otherwise can't be duplicated
    if (pass==1) {
      printf("?ECA - %s:%d - ",inft->ifile,inft->filenum);
      printf("Label name %s already exists -- cannot redefine\n",insym->symname);      
      fatalerror = 1;
      return(1);
    } else return(0);
  }

  if (symtype==SYM_OPDEF) {
    // Operators cannot be redefined unless the new def is identical
    if (insym->symtype==SYM_OPDEF && 
	insym->value==inword) return(0);
    printf("?ECA - %s:%d - ",inft->ifile,inft->filenum);
    printf("Operator name %s already exists -- cannot redefine\n",insym->symname);      
    fatalerror = 1;
    return(1);
  }

  printf("?ECA - %s:%d - ",inft->ifile,inft->filenum);
  printf("Unknown flag %d symbol %s\n",symtype,insym->symname);
    fatalerror = 1;

  return(1);

}

char *eatsym(char *ib, char *outs)
{

  char *ob;
  int obc;

  ob = outs;
  obc = 0;

  while (obc<MAXSYM-2) {
    if (isalpha(*ib) ||
	isdigit(*ib) ||
	*ib == '$' ||
	*ib == '.' ||
	*ib == '%' ||
	*ib == '_') {
      *ob = toupper(*ib);
      ob++; ib++;
      *ob = '\0';
      obc++;
      continue;
    }
    break;
  }
  return(ib);
}

int isoctsym(char *inc)
{

  int ok= -1;

  EWS(inc);
  while (*inc!='\0') {
    if (isoctal(*inc)) {
      if (ok<0) ok = 1;
      inc++;
      continue;
    }
    if (isspace(*inc)) {
      break;
    }
    return(0);  // Not
  }

  return(ok==1);
}
  

WORD36 cvtoctal(char *ib, char **segb)
{

  WORD36 val;

  EWS(ib);

  val = 0;
  while (isoctal(*ib)) {
    val *= 8;
    val += (*ib - '0');
    ib++;
  }

  if (segb)
    *segb = ib;

  return(val);
}

WORD36 chkvalue(FILET *inft,char *sym1)
{

  SYMBOL *fsym;

  if (strcmp(sym1,".")==0) 
    return((WORD36) curloc);
  
  fsym = findsym(sym1,1);
  if (fsym) {
    return(fsym->value);
  }

  if (pass==1) {
    if (addsym(inft, sym1, 0ULL, SYM_UNKNOWN)) {
      fatalerror= 1;
      return(0);
    }
    return(0ULL);
  }

  printf("?ECA - %s:%d - ",inft->ifile,inft->filenum);
  printf("Symbol undefined in pass 2 (shouldn't happen): %s\n",sym1);
  fatalerror= 1;
  
  return(1);
}

// Eval a symbol and return its value 

/*
      symbol
      number
      symbol + number
      symbol - number

*/

WORD36 evalsym(FILET *inft, char *ib)
{

  char sym1[MAXSYM],sym2[MAXSYM],s;
  WORD36 s1,s2;
  int lh,rh;

  EWS(ib);

  if (*ib=='\0') return(0ULL);

  ib = eatsym(ib,sym1);
  EWS(ib);
  s = 0;
  if (*ib=='+') {
    s = *ib;
    ib++;
    EWS(ib);
    ib = eatsym(ib,sym2);
  } else
    if (*ib=='-') {
      s = *ib;
      ib++;
      EWS(ib);
      ib = eatsym(ib,sym2);
    }
  if (*ib!='\0') {
    printf("?ECA - %s:%d - ",inft->ifile,inft->filenum);
    printf("Illegal expression element %s\n",ib);
    fatalerror = 1;
  }

  s1 = 0;
  s2 = 0;

  if (isoctsym(sym1))  
    s1 = cvtoctal(sym1, NULL);  // Is octal
  else 
    s1 = chkvalue(inft,sym1);
  if (fatalerror) return(0);

  lh = LH(s1);
  rh = RH(s1);
  //  printf(" %06o %06o",lh,rh);

  if (s) {
    if (isoctsym(sym2))  
      s2 = cvtoctal(sym2, NULL);  // Is octal
    else 
      s2 = chkvalue(inft,sym2);
  }
  if (fatalerror) return(0);

  // These numbers aren't normalized so, negative numbers not likely

  if (s) {
    lh = LH(s2);
    rh = RH(s2);
    //    printf(" %c %06o %06o",s,lh,rh);
  }

  switch (s) {
  case '+':
    s1 += s2;
    break;
  case '-':
    s1 -= s2;
    break;
  }

  lh = LH(s1);
  rh = RH(s1);

  //  printf(" = %06o %06o\n",lh,rh);

  return(s1);
}

int parseop(FILET *inft, char *ib)
{

  char opnam[MAXSYM],acname[MAXSYM],addr[MAXSYM];
  SYMBOL *insym,*loop;
  WORD36 t;
  int lop,lac,lad,ind,idx;
  WORD36 uac,uad,opw;
  char *inop;

  inop = strdup(ib);

  opnam[0] = acname[0] = addr[0] = '\0';
  ind = 0;
  idx = 0;

  // Parse off the operator

  EWS(ib);
  ib = eatsym(ib,opnam);
  EWS(ib);

  // See if there's an accumulator

  if (*ib) {
    char *f;
    f = strchr(ib,',');
    if (f) {
      *f = '\0';
      strcpy(acname,ib);
      strcpy(addr, f+1);
    } else {
      // No accumulator
      strcpy(addr,ib);
      acname[0] = '\0';
    }
  }

  insym = findsym(opnam,1);

  if (insym==NULL) {
    printf("%%ECA - %s:%d - ",inft->ifile,inft->filenum);
    printf("Unknown opcode: %s\n",opnam);
  fatalerror= 1;
    return(1);
  }

#define OP(a) ((((long long int)(a))&OPM)>>OPS)
#define AC(a) ((((long long int)(a))&ACM)>>ACS)
  t = OP(insym->value);
  lop = (int) t;
  t = AC(insym->value);
  lac = (int) t;
  t = insym->value & RWM;
  lad = (int) t;

  uac = evalsym(inft,acname);
  if (fatalerror) return(1);
  uad = evalsym(inft,addr);
  if (fatalerror) return(1);

  if (pass==1) {
    curloc++;
    return(0);
  }

  if (lac && uac) {
    printf("%%ECA - %s:%d - ",inft->ifile,inft->filenum);
    printf("Accumulator use redefines instruction: %s - %s\n",opnam,inop);
    fatalerror= 1;
    return(1);
  }
  if (lac==0)
    lac = uac;

  if (lad && uad) {
    printf("%%ECA - %s:%d - ",inft->ifile,inft->filenum);
    printf("Address use redefines instruction: %s - %s\n",opnam,inop);
    fatalerror= 1;
    return(1);
  }
  if (lad==0)
    lad = (uad & 0777777);

  printf("%06o/ %03o %02o %06o     %s\n",
	 curloc,
	 lop,lac,lad,
	 inop);

  // Indirect and index not yet implemented

  opw = lop & 0777;
  opw <<= 4;
  opw |= lac & 017;
  opw <<= (5 + 18);
  opw |= lad & 0777777;

  saveloc(curloc,opw);  // Put in the buffer

  curloc++;

  free(inop);

  return(0);

}

int parse_opdef(FILET *inft, char *ib)
{

  int op,ac,ad,c;
  char outs[MAXSYM];
  char *org=ib;
  WORD36 opw;

  EWS(ib);
  ib = eatsym(ib,outs);
  EWS(ib);

  if (*ib!='=') 
    return(parseerror(inft,org,"bad symbol in opdef"));
  ib++;
  EWS(ib);

  c = sscanf(ib,"%o,%o,%o",&op,&ac,&ad);
  if (c!=3) {
    printf("Scan of %s returns %d\n",ib,c);
    return(parseerror(inft,org,"bad list in opdef"));
  }

  opw = op & 0777;
  opw <<= 4;
  opw |= ac & 017;
  opw <<= (5 + 18);
  opw |= ad & 0777777;

  return(addsym(inft,outs,opw,SYM_OPDEF));

  return(0);
}

int parse_value(FILET *inft, char *ib)
{

  char outs[MAXSYM];
  char *org=ib;
  int lh,rh;
  WORD36 val;

  EWS(ib);
  ib = eatsym(ib,outs);
  EWS(ib);

  if (*ib!='=') 
    return(parseerror(inft,org,"bad symbol in value"));
  ib++;
  EWS(ib);

  val = cvtoctal(ib,NULL);

  return(addsym(inft,outs,val,SYM_VALUE));

  return(0);
}

int parse_asciz(FILET *inft, char *ib)
{
  printf("ASCIZ: %s\n",ib);
  return(0);
}

int parse_sixbit(FILET *inft, char *ib)
{
  printf("SIXBIT: %s\n",ib);
  return(0);
}

int parse_include(FILET *inft, char *ib)
{
  return(eatfile(ib));
}

int parse_search(FILET *inft, char *ib)
{
  if (pass==1)
    return(eatfile(ib));
  else 
    return(0);
}

int parse_xwd(FILET *inft, char *ib)
{
  printf("XWD: %s\n",ib);
  return(0);
}

int parse_word(FILET *inft, char *ib)
{
  printf("WORD: %s\n",ib);
  return(0);
}

int inparse(FILET *inft, char *ib)
{

  char *w,*s;
  char outs[MAXSYM];

  w = ib;

  s = strchr(w,'\n');
  if (s) {
    *s = '\0';
    for (s--; s>ib; s--)
      if (!isspace(*s)) 
	break;
      else
	*s = '\0';
  }
  s = strchr(w,'\r');  // PC compat
  if (s) {
    *s = '\0';
    for (s--; s>ib; s--)
      if (!isspace(*s))
	break;
      else
	*s = '\0';
  }

  s = strchr(w,'/');
  if (s) 
    if (*(s+1)=='/') {
      *s = '\0';  // No way to quote a // yet
      for (s--; s>ib; s--)
	if (isspace(*s)) break;
	else
	  *s = '\0';
    }

  EWS(w);
  if (*w=='\0') return(0);

  if (*w==':') {
    WORD36 inaddr;
    w++;
    EWS(w);
    w = eatsym(w,outs);
    if (outs[0]=='\0') 
      return(parseerror(inft,ib,"symbol expected after label"));
    inaddr = curloc;
    return(addsym(inft,outs,inaddr,SYM_LABEL));
  }

  if (*w=='-') {
    w++;
    EWS(w);
    return(parseop(inft,w));
  }

  w = eatsym(w,outs);
  EWS(w);
    
  if (strcmp(outs,"OPDEF")==0) 
    return(parse_opdef(inft,w));
  if (strcmp(outs,"VALUE")==0) 
    return(parse_value(inft,w));
 if (strcmp(outs,"ASCIZ")==0) 
    return(parse_asciz(inft,w));
  if (strcmp(outs,"SIXBIT")==0) 
    return(parse_sixbit(inft,w));
  if (strcmp(outs,"INCLUDE")==0) 
    return(parse_include(inft,w));
  if (strcmp(outs,"SEARCH")==0) 
    return(parse_search(inft,w));
  if (strcmp(outs,"XWD")==0) 
    return(parse_xwd(inft,w));
  if (strcmp(outs,"WORD")==0) 
    return(parse_word(inft,w));

  printf("What's left? /%s/\n",w);
  fatalerror= 1;
  return(1);
                       
}

int eatfile(char *infile)
{

  FILET filectx;

  filectx.ifile = strdup(infile);
  filectx.filenum = 0;
  filectx.ib = (char *) malloc(1000);
  filectx.iov = fopen(infile,"r");
  if (filectx.iov==NULL) {
    printf("Couldn't open %s\n",infile);
    exit(100);
  }

  while (!feof(filectx.iov)) {
    if (fgets(filectx.ib,1000,filectx.iov)==NULL) break;
    filectx.filenum ++;
    if (inparse(&filectx,filectx.ib)) return(1);
  }

  fclose(filectx.iov);
  printf("[Process file %s - %d lines]\n",filectx.ifile,filectx.filenum);

  return(0);
}

int main(int argc, char **argv)
{

  int i;

  pass = 1;
  curloc = 0400; 

  for (i=1; i<argc; i++) 
    if (eatfile(argv[i])) break;

  hiwater = curloc;
  pass = 2;
  curloc = 0400; 

  for (i=1; i<argc; i++) 
    if (eatfile(argv[i])) break;

  saveloc(0120, (WORD36) startaddr);  // Write the start addr

  outexe("eca.exe.asc");
 
  dumpsym();

  exit(0);

}
