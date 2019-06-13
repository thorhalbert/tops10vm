#include <stdio.h>

#include "psr.h"

// 36 bit manipulation routines


// Unpack 2 36 bit values into 9 bytes in order
// oc[8] = MSB, oc[0] = LSB

int unpack236(PCTX *ctx, int addr, unsigned char *oc)
{

  BIGV A,B;
  int t,u;

  // Read in memory

  A = READMEM(jctx, addr);
  CHKERROR(jctx);
  B = READMEM(jctx, addr + 1);
  CHKERROR(jctx);

  // Hex better for dealing with multiples of 4 bits

  t = A & 0xFF;  
  oc[0] = t;
  A >>= 8;

  t = A & 0xFF;  
  oc[1] = t;
  A >>= 8;

  t = A & 0xFF;  
  oc[2] = t;
  A >>= 8;

  t = A & 0xFF;  
  oc[3] = t;
  A >>= 8;

  u = A & 0x0F;
  t = B & 0x0F;  
  oc[4] = u;
  oc[4] |= t << 4;
  B >>= 4;

  t = B & 0xFF;  
  oc[5] = t;
  B >>= 8;

  t = B & 0xFF;  
  oc[6] = t;
  B >>= 8;

  t = B & 0xFF;  
  oc[7] = t;
  B >>= 8;

  t = B & 0xFF;  
  oc[8] = t;

  return(0);

}

// Unpack 2 36 bit values into 9 bytes in order
// oc[8] = MSB, oc[0] = LSB

int pack236(PCTX *ctx, int addr, unsigned char *oc)
{

  BIGV A,B;
  int t;

  // Hex better for dealing with multiples of 4 bits

  t = oc[4] & 0xF;
  A = t;
  A <<= 4;

  A |= oc[3];
  A <<= 8;

  A |= oc[2];
  A <<= 8;

  A |= oc[1];
  A <<= 8;

  A |= oc[0];

  B = oc[8];
  B <<= 8;

  B = oc[7];
  B <<= 8;

  B = oc[6];
  B <<= 8;

  B = oc[4];
  B <<= 8;

  t = (oc[4] & 0xF0) >> 4;
  B |= t;

  // Write to memory

  WRITEMEM(jctx, addr, A);
  CHKERROR(jctx);
  WRITEMEM(jctx, addr + 1, B);
  CHKERROR(jctx);

  return(0);

}

// Unpack 36 bit values into 5 bytes in order
// oc[4] = MSB, oc[0] = LSB

int unpack36(PCTX *ctx, int addr, unsigned char *oc)
{

  BIGV A;
  int t,u;

  // Read in memory

  A = READMEM(jctx, addr);
  CHKERROR(jctx);

  // Hex better for dealing with multiples of 4 bits

  t = A & 0xFF;  
  oc[0] = t;
  A >>= 8;

  t = A & 0xFF;  
  oc[1] = t;
  A >>= 8;

  t = A & 0xFF;  
  oc[2] = t;
  A >>= 8;

  t = A & 0xFF;  
  oc[3] = t;
  A >>= 8;

  u = A & 0x0F;
  oc[4] = u;

  return(0);

}

// Unpack 36 bit values into 5 bytes in order
// oc[4] = MSB, oc[0] = LSB

int pack36(PCTX *ctx, int addr, unsigned char *oc)
{

  BIGV A;
  int t;

  // Hex better for dealing with multiples of 4 bits

  t = oc[4] & 0xF;
  A = t;
  A <<= 4;

  A |= oc[3];
  A <<= 8;

  A |= oc[2];
  A <<= 8;

  A |= oc[1];
  A <<= 8;

  A |= oc[0];

  // Write to memory

  WRITEMEM(jctx, addr, A);
  CHKERROR(jctx);

  return(0);

}

/* Write bits into the word (LSB (dec bit 35) written to zero 
   peel off 'numbits' bits starting in the word at 'packbits' */

int peelbits(PCTX *ctx, int addr, unsigned char *oc, int numbits, int packstart)
{

  BIGV A;
  int t,u;

  // Read in memory

  A = READMEM(jctx, addr);
  CHKERROR(jctx);

  // Trunc off packstart

  if (packstart>0)
    A >>= packstart;

  for (t=0; t<numbits; t++) {
    oc[t] = A & 1;
    A >>= 1;
  }
  
  return(0);
}

/* Unpack bits from array and *OR* them onto the output word.  There is
   a flag for pre-clearing the word - starts placing the bits at 'packstart'
   from the right, and then 'numbits' left from there  */

int packbits(PCTX *ctx, int addr, unsigned char *oc, int numbits, int packstart,
	     int clear)
{

  BIGV target,outword;
  int t;

  target = 0;

  for (t=(numbits-1); t>=0; t--) {
    target <<= 1;
    if (oc[t])
      target |= 1;
  }

  if (packstart>0)
    target <<= packstart;

  if (!clear) {
    outword = READMEM(jctx,addr);
    CHKERROR(jctx);
  } else
    outword = 0;

  outword |= target;

  WRITEMEM(jctx,addr,outword);
  CHKERROR(jctx);

  return(0);
}

// Unpack chars from sixbit from halfword

void unpacksixhw(int inval, char o[3])
{

  int ob;

  ob = inval & 0770000;
  ob >>= 12;

  o[0] = ob + ' ';

  ob = inval & 0007700;
  ob >>= 6;

  o[1] = ob + ' ';

  ob = inval & 0000077;

  o[2] = ob + ' ';

}

void unpacksixbit(BIGV inval, char o[6])
{

  unpacksixhw((int)LH(inval), &o[0]);
  unpacksixhw((int)RH(inval), &o[3]);

}

BIGV packasciz(char iv[5],int len)
{
  BIGV t;
  int i,z,m;
  char lc[5];

  m = 5;
  if (len<5) m = len;

  z = 0;

  for (i=0; i<5; i++) 
    lc[i] = 0;

  for (i=0; i<m; i++) 
      lc[i] = iv[i];

  t = iv[0];
  t <<= 7;
  t |= iv[1];
  t <<= 7;
  t |= iv[2];
  t <<= 7;
  t |= iv[3];
  t <<= 7;
  t |= iv[4];
  t <<= 1;

  return(t);
}
