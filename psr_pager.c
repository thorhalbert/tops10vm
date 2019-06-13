#include <stdio.h>
#include <assert.h>

#include "psr.h"

BIGV adjust_core(JOBCTX *ijctx, int hiseg, int loseg, int PC)
{

  int i;
  int loseg_t=0,hiseg_t=0;
  int loseg_k,hiseg_k;
  BIGV r;

  if (hiseg)
    hiseg &= ~PAGE_MASK;   // Round down to page start
  if (loseg)
    loseg &= ~PAGE_MASK;  

  // See if we are adjusting the hiseg

  if (hiseg > 0) {
    if (hiseg < ijctx->hiseg_floor) 
      hiseg = ijctx->hiseg_floor - 1;  // Drop entire hiseg
    if (PC >= hiseg)
      return( -1 );   // We're eliminating code we're now running from
  
    for (i=ijctx->hiseg_floor; i<=0777777; i+=PAGE_SIZE) {
      int pagev,bucket,slot;

      pagev = PAGENUM(i);
      bucket = PAGEBUCKET(pagev);
      slot = BUCKETSLOT(pagev);

      if (ijctx->pb[bucket]) {
	if (ijctx->pb[bucket]->page_list[slot]) {
	  if (i>hiseg) {
	    if (ijctx->pb[bucket]->page_list[slot]->pageflags & PAGE_WRITABLE) {
	      free(ijctx->pb[bucket]->page_list[slot]);
	      ijctx->pb[bucket]->page_list[slot] = NULL;
	    }
	    else {
	      printf("?PSR_PAGER - Attempt to remove read-only high-segment\n");
	      exit(100);
	    }
	  }
	} else {
	  // NEED TO FIGURE OUT PROPER RULES FOR EXPANDING HISEG
	  if (i<=hiseg)  
	    create_page(ijctx,pagev, PAGE_WRITABLE);
	}
      }
    }
  }

  // See if we are adjusting the loseg

  if (loseg > 0) {
    if (loseg >= ijctx->hiseg_floor) 
      return( -1 );   // Can't expand program above high-segment
   
    for (i=0; i< ijctx->hiseg_floor-1; i+=PAGE_SIZE) {
      int pagev,bucket,slot;

      pagev = PAGENUM(i);
      bucket = PAGEBUCKET(pagev);
      slot = BUCKETSLOT(pagev);

      if (ijctx->pb[bucket]) {
	if (ijctx->pb[bucket]->page_list[slot]) {
	  if (i>loseg) {
	    free(ijctx->pb[bucket]->page_list[slot]);
	    ijctx->pb[bucket]->page_list[slot] = NULL;
	  }
	} else {
	  if (i<=loseg)  
	    create_page(ijctx,pagev, PAGE_WRITABLE);
	}
      }
    }
  }

  // Count up the core for a return

  for (i=0; i<=0777777; i+=PAGE_SIZE) {
    int pagev,bucket,slot;

    pagev = PAGENUM(i);
    bucket = PAGEBUCKET(pagev);
    slot = BUCKETSLOT(pagev);

    if (ijctx->pb[bucket]) {
      if (ijctx->pb[bucket]->page_list[slot]) {
	if (i < ijctx->hiseg_floor)
	  loseg_t ++;
	else
	  hiseg_t ++;
      }
    }
  }

  loseg_k = (loseg_t+1) / (1024 / PAGE_SIZE);
  hiseg_k = (hiseg_t+1) / (1024 / PAGE_SIZE);

  // Format up the return

  r = hiseg_k;
  r <<= 18;
  r |= loseg_k;

  return(r);

}

void printcore(JOBCTX *ijctx,int detail)
{

  int i;
  int loseg_t=0,hiseg_t=0;
  int obucket= -1;

  assert(PAGE_SIZE <= 1024);   // Just in case pages get bigger


  if (detail)
    printf("Core Map: \n");


  for (i=0; i<=0777777; i+=PAGE_SIZE) {
    int u,pagev,bucket,slot,sgb,adb,sge,ade;

    pagev = PAGENUM(i);
    bucket = PAGEBUCKET(pagev);
    slot = BUCKETSLOT(pagev);

    if (ijctx->pb[bucket]) {
      u = bucket*PAGE_SIZE*PAGE_BUCKET_SIZE;
      sgb = SEGMENTNUM(u);
      adb = SEGMENTADDR(u);
      u = ((bucket+1)*PAGE_SIZE*PAGE_BUCKET_SIZE)-1;
      sge = SEGMENTNUM(u);
      ade = SEGMENTADDR(u);
      if (detail && obucket!=bucket)
	printf("  Bucket %o: [Seg %o/%06o - Seg %o/%06o]\n",
	       bucket,sgb,adb,sge,ade);
      obucket = bucket;
      if (ijctx->pb[bucket]->page_list[slot]) {
	if (detail) {
	  u = pagev * PAGE_SIZE;
	  sgb = SEGMENTNUM(u);
	  adb = SEGMENTADDR(u);
	  u = ((pagev+1)*PAGE_SIZE)-1;
	  ade = SEGMENTADDR(u);
	  printf("    Page %o: [Seg %o/%06o-%06o]",
		 pagev,sgb,adb,ade);
	  if (ijctx->pb[bucket]->page_list[slot]->pageflags & PAGE_WRITABLE) printf(" WR");
	  if (ijctx->pb[bucket]->page_list[slot]->pageflags & PAGE_SHARABLE) printf(" SH");
	  if (ijctx->pb[bucket]->page_list[slot]->pageflags & PAGE_CONCEALED) printf(" CO");
	  if (ijctx->pb[bucket]->page_list[slot]->pageflags & PAGE_HISEG) printf(" HS");
	  if (ijctx->pb[bucket]->page_list[slot]->pageflags & PAGE_SYMBOL) printf(" SY");
	  if (ijctx->pb[bucket]->page_list[slot]->pageflags & PAGE_CLEARED) printf(" CL");
	  printf("\n");
	}
	if (i < ijctx->hiseg_floor)
	  loseg_t ++;
	else
	  hiseg_t ++;
      }
    }
  }

  // Make sure our rounding is right

  printf("[Core utilization Low-Seg=%dK (%d pages), Hi-Seg=%dK (%d pages)]\n",
	 (loseg_t+1) / (1024 / PAGE_SIZE), loseg_t,
	 (hiseg_t+1) / (1024 / PAGE_SIZE), hiseg_t);

}

JOBCTX *create_pager_jctx()
{

  int i;

  JOBCTX *newjctx;

  newjctx = (JOBCTX *) malloc(sizeof (JOBCTX));
  if (newjctx==NULL) exit(100);

  newjctx->jobnum = 0;
  for (i=0; i<NUMBER_ACCUMULATORS; i++)
    newjctx->accumulators[i] = 0;
  for (i=0; i<PAGE_BUCKET_TOTAL; i++)
    newjctx->pb[i] = NULL;
  newjctx->hiseg_floor = NORMAL_HISEG_FLOOR;
  newjctx->lastpage = -1;
  newjctx->lastbucket = -1;
  newjctx->curpage = NULL;
  newjctx->curbucket = NULL;
  newjctx->memerror = MEM_NONERROR;

  // OS Specific

  newjctx->watchbits = 0;
  newjctx->vmwatch = 0;

  return(newjctx);

}

void zero_page(WPAGE *inpage)
{

  unsigned int pagenum;
  unsigned int pageflags;

  pagenum = inpage->pagenum;
  pageflags = inpage->pageflags;

  memset((void *) inpage, 0, sizeof (WPAGE));

  inpage->pagenum = pagenum;
  inpage->pageflags = pageflags;
}

PAGEB *create_raw_bucket(void)
{

  PAGEB *newb;

  newb = (PAGEB *) malloc(sizeof (PAGEB));
  if (newb==NULL) {
    printf("?PSR_PAGER - Cannot allocate new bucket\n");
    exit(100);
  }

  memset((void *) newb, 0, sizeof (PAGEB));

  return(newb);

}

int create_page(JOBCTX *ijctx,unsigned int pagenum, unsigned int pageflags)
{

  int bucket;
  int bslot;

  bucket = PAGEBUCKET(pagenum);
  bslot = BUCKETSLOT(pagenum);

  if (ijctx->pb[bucket]==NULL) {
    ijctx->pb[bucket] = create_raw_bucket();
  }

  if (ijctx->pb[bucket]->page_list[bslot]) {
    ijctx->memerror = MEM_PAGE_EXISTS;
    return(1);
  }

  ijctx->pb[bucket]->page_list[bslot] = create_raw_page(pagenum,pageflags);

  ijctx->memerror = MEM_NONERROR;

  //  printf("[Create page %o (%o)]\n",pagenum,pageflags);

  return(0);

}

WPAGE *create_raw_page(unsigned int pagenum, unsigned int pageflags)
{

  WPAGE *npage;

  npage = (WPAGE *) malloc(sizeof (WPAGE));
  if (npage==NULL) {
    printf("?PSR_PAGER - Cannot allocate a new page!\n");
    exit(100);
  }

  // We'll be nice and completely zero out the new page
  // Of course, core wouldn't act like this

  memset((void *) npage, 0, sizeof (WPAGE));

  npage->pagenum = pagenum;
  npage->pageflags = pageflags;

  return(npage);

}

void destroy_page(WPAGE *opage)
{

  free(opage);  // Quick and easy for now

}

void write_page(JOBCTX *ijctx, int pagenum, BIGV *inarray)
{
  int i;
  int pageroot;

  pageroot = pagenum * PAGE_SIZE;

  // Write the page out

  for (i=0; i<PAGE_SIZE; i++) 
    write_memval(ijctx, pageroot+i, inarray[i], 0);

  // For test, read the page back and check it 
  // SHOULD BE REMOVED AFTER SUCESSFUL TESTING

  for (i=0; i<PAGE_SIZE; i++) {
    BIGV testv;

    testv = read_memval(ijctx, pageroot+i, 0);
    if (testv != inarray[i]) {
      printf("?PSR_PAGER - Page %o element %o - mismatch %o,,%o <> %o,,%o\n",
	     pagenum,i,
	     LH(testv),RH(testv),
	     LH(inarray[i]),RH(inarray[i]));
      exit(100);
    }
  }
}
 
BIGV read_memval(JOBCTX *ijctx, int addr,int perm)
{
  BIGV retval;
  int pagenum,bucket,bslot,pslot;
  WPAGE *cpage;
  PAGEB *bpage;

  pagenum = PAGENUM(addr);
  pslot = PAGEADDR(addr);

  bucket = PAGEBUCKET(pagenum);
  bslot = BUCKETSLOT(pagenum);

  if (ijctx->pb[bucket]==NULL) {
    ijctx->memerror = MEM_READ_NONPAGE;
    return(0ULL);
  }

  bpage = ijctx->pb[bucket];
  
  if (bpage->page_list[bslot]==NULL) {
    ijctx->memerror = MEM_READ_NONPAGE;
    return(0ULL);
  }

  cpage = bpage->page_list[bslot];

  if ((pslot & 1)==0) // Even
    retval = cpage->o[pslot>>1] >> 4;  // Left 4 bits of word 
  else // Odd
    retval = cpage->o[pslot>>1];       // Right 4 bits of word

  retval &= 017;
  retval <<= 32;
  retval |= cpage->m[pslot];

  ijctx->memerror = MEM_NONERROR;

  return(retval);
}

// WE HAVEN'T IMPLEMENTED MEMORY PROTECTION YET ON WRITE!

void write_memval(JOBCTX *ijctx, int addr, BIGV value, int perm)
{
  BIGV prcval;
  int pagenum,bucket,bslot,pslot,tval;
  WPAGE *cpage;
  PAGEB *bpage;

  pagenum = PAGENUM(addr);
  pslot = PAGEADDR(addr);

  bucket = PAGEBUCKET(pagenum);
  bslot = BUCKETSLOT(pagenum);

  if (ijctx->pb[bucket]==NULL) {
    ijctx->memerror = MEM_WRITE_NONPAGE;
    return;
  }

  bpage = ijctx->pb[bucket];
  
  if (bpage->page_list[bslot]==NULL) {
    ijctx->memerror = MEM_WRITE_NONPAGE;
    return;
  }

  cpage = bpage->page_list[bslot];

  prcval = value;
  prcval &= 0xFFFFFFFF;  // Sorry couldn't calculate octal that quick
  
  cpage->m[pslot] = prcval;

  prcval = value;
  prcval >>= 32;
  tval = prcval;

  if ((pslot & 1)==0) { // Even - left 4 bits
    cpage->o[pslot>>1] &= 0x0F;     // clear left 4
    cpage->o[pslot>>1] |= (tval & 0x0F) << 4;   
    
  }  else { // Odd - right 4
    cpage->o[pslot>>1] &= 0xF0;     // clear right 4
    cpage->o[pslot>>1] |= (tval & 0x0F);   

  }

  ijctx->memerror = MEM_NONERROR;

}


