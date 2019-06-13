// Definition of Memory Pages

// This is currently TOPS-10 centric -- don't know when we can make generic

#define PAGE_SIZE 512           // Words
#define PAGE_MASK 0777          // Bits in mask
#define PAGE_SIZE_BITS 9        // Number bits per word
#define PAGE_BUCKET_SIZE 4096   // How many pages to set up frame for
#define PAGE_BUCKET_SIZE_BITS 12 // Bits total
#define PAGE_BUCKET_TOTAL 512  // For a total of 2**30 words
#define NUMBER_ACCUMULATORS 16

#define NORMAL_HISEG_FLOOR 0x400000

#define PAGE_WRITABLE 1
#define PAGE_SHARABLE 2
#define PAGE_CONCEALED 4
#define PAGE_HISEG 8
#define PAGE_SYMBOL 16
#define PAGE_CLEARED 32

typedef struct page_container {
  unsigned int pagenum;
  unsigned int pageflags;
  unsigned int m[PAGE_SIZE];       // First 32 bits of word 
  unsigned char o[PAGE_SIZE/2];    // Remaining 4 bits
} WPAGE;

typedef struct page_bucket {
  WPAGE *page_list[PAGE_BUCKET_TOTAL];
} PAGEB;

typedef struct job_context {
  BIGV jobnum;
  int hiseg_floor;
  BIGV accumulators[NUMBER_ACCUMULATORS];
  PAGEB *pb[PAGE_BUCKET_TOTAL];

  // Caches

  int lastpage;
  int lastbucket;

  WPAGE *curpage;
  PAGEB *curbucket;

  // Errors

#define MEM_NONERROR 0             // Clear error
#define MEM_WRITE_NONPAGE 1        // Write attempt to non-existant page
#define MEM_READ_NONPAGE 2         // Read attempt to non-existant page
#define MEM_WRITE_WLPAGE 3         // Write against write-locked page
#define MEM_READ_CONCEAL 4         // Read against a concealed page

#define MEM_PAGE_EXISTS 10         // Page already there in create_page
#define MEM_PAGE_NONEXIST 11       // Nonexistant page

  int memerror;

  // OS Settings

  /*   Watch bits      Bits   Symbol    Meaning
                       9      ST.WCN    /MESSAGE:CONTINUATION.
                       10     ST.WFL    /MESSAGE:FIRST.
                       11     ST.WPR    /MESSAGE:PREFIX.
                       9-11   ST.WMS    /MESSAGE:ALL (bit mask).
                       18     ST.WCX    Watch contexts.
                       19     ST.WDY    Watch daytime at start.
                       20     ST.WRN    Watch runtime.
                       21     ST.WWT    Watch wait time.
                       22     ST.WDR    Watch disk reads.
                       23     ST.WDW    Watch disk writes.
                       24     ST.WVR    Watch versions.
                       25     ST.WMT    Watch statistics for magtapes.
                       26     ST.WFI    Watch file accessed.
                       18-26  ST.WAL    Watch all.    */

  BIGV watchbits;                  // TOPS-10 watch bits
  BIGV vmwatch;                    // VM Specific watch bits

} JOBCTX;

#define jctx ctx->jCTX

#define SEGMENTNUM(addr) ((addr) >> 18)
#define SEGMENTADDR(addr) ((addr) & 0777777)

#define PAGEBUCKET(page) ((page) >> PAGE_BUCKET_SIZE_BITS)
#define BUCKETSLOT(page) ((page) & 07777)

#define PAGEADDR(addr) ((addr) & 0777)
#define PAGENUM(addr) ((addr) >> PAGE_SIZE_BITS)
#define BUCKETNUM(addr) ((addr) >> (PAGE_SIZE_BITS + PAGE_BUCKET_SIZE_BITS))
#define CHKERROR(jctx) if (jctx->memerror!=MEM_NONERROR) return(100)
#define CLRERROR(jctx) jctx->memerror = MEM_NONERROR;
#define READMEM(jctx,addr) ((addr)<16 ? jctx->accumulators[addr] \
     : read_memval(jctx,addr,0))
#define WRITEMEM(jctx,addr,value) if ((addr)<16) \
     jctx->accumulators[addr]=value; else write_memval(jctx,addr,value,0);

// Prototypes for pager code

JOBCTX *create_pager_jctx(void);
BIGV read_memval(JOBCTX *, int, int);
void write_memval(JOBCTX *, int, BIGV, int);
void destroy_page(WPAGE *opage);
WPAGE *create_raw_page(unsigned int pagenum, unsigned int pageflags);
void zero_page(WPAGE *inpage);
int create_page(JOBCTX *injob,unsigned int pagenum, unsigned int pageflags);
void write_page(JOBCTX *ijctx, int pagenum, BIGV *inarray);
void printcore(JOBCTX *ijctx,int detail);
BIGV adjust_core(JOBCTX *ijctx, int hiseg, int loseg, int PC);
