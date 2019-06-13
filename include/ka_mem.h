/* Physical page structure for KA-10 Processor */

#ifndef DEFVAL
#define DEFVAL extern
#endif

#define KA_MEM_CAPACITY 256 * 1024
#define BLOCK 1024
#define KA_MAX_BLOCK 256

#define KA_BLOCK 256

struct ka_phys_block {
  unsigned int block_bytes[(KA_K>>1) * 9];  /* 72 bits = 9 bytes */
};

/* map[0] = word 1 - bits 28-35 */
/* map[1] = word 1 - bits 20-27 */
/* map[2] = word 1 - bits 12-19 */
/* map[3] = word 1 - bits 4-11 */
/* map[4] = word 2 - bits 28-35 */
/* map[5] = word 2 - bits 20-27 */
/* map[6] = word 2 - bits 12-19 */
/* map[7] = word 2 - bits 4-11 */
/* map[9] bits 4-7 = word 1 - bits 0-3 (bit order backwards C.vs.36 bits) */
/* map[9] bits 0-3 = word 2 - bits 0-3 */

DEFVAL int ka_blockcapacity = KA_MAX_BLOCK;  /* Defaults to full memory */

/* Pages do not exist until an attempt is made to write to them.  They are 
   then malloc'd and added to the ka_physpage array - also, they always
   return zero memory values if they don't exist */

DEFVAL struct ka_phys_block *phys_block[KA_MAX_BLOCK];

/* Relocation and protection registers */

DEFVAL int prot_low, prot_hi;
DEFVAL int reloc_low, reloc_hi;
DEFVAL int high_protect;

#define INBLOCKADDR(x) ((x)&01777)
#define BLOCKNUM(x) ((x)>>10)

/* High speed ac's (no packing/unpacking into the phys_block structure) */

DEFVAL long long unsigned int ac_block[16];

