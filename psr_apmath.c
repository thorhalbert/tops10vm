// Arbitrary precision add/sub multiply/divider

#include <stdio.h>
#include <assert.h>

#include "apmath.h"

/*

   APC *apnew(int size)
   APC *apcopy(APC *inapc)
   APC *apdestroy(APC *desapc)

   int apadd(APC *answer, APC *add1, APC *add2)
       answer = add1 + add2

   int apsub(APC *anwser, APC *sub1, APC *sub2)
       answer = sub1 - sub2    

   int apmul(APC *product, APC *mul1, APC *mul2)
       product = mul1 * mul2;

   int abdiv(APC *div, APC *rem, APC *quot, APC *div)
       div = quot / div;  (if div=NULL, not returned)
       rem = quot % div;  (if rem=NULL, not returned)

   int ab2csignext(apc *num, int numtot, int numsign)
       Sign extend number to make 2s compliment

   int ab2unsign(apc *num, int numtot, int *numsign)
       Remove sign extension and set the sign

   int abcmp(apc *num1, apc *num2, int ignsign)
       +1,0,-1 if num1 > num2, ignore sign in calg if ignsign set

   int abeq(apc *num1, apc *num2, int ignsign)
       True if num1 == num2, ignore sign in calg if ignsign set

*/

/*

   How do we do this again?

   Addition (base 10)

               111
    + 1234   + 6789
    + 4321   + 9876
    ------   ------
    + 5555    16665 

       2
    + 2315   + 1234
    - 2222   - 4567
    ------   ------
    + 0093        

    same sign = a + b sign is same
    diff sign max - min sign is max
    special case: zero is positive

    Multiplication

      011
      112
      122
      122 
      1234
    * 4567
    ------
      8638
     7404o
    6170oo 
   4936ooo
   -------
   5635678

   Division

        00536
      _______
   23 ) 12345
        115oo
      -------
          845
          69o
      -------
          155
	  138
      -------
           17 <-- Remainder

   Signs easy on mult or div

   + * + = +,  + / + = +
   + * - = -,  - * + = -, + / - = -, - / + = -
   - * - = +,  - / - = +

   So, we do this exactly the same way, but base 256 instead of 10

*/

// AP Constructor

APC *apnew(int nsize)
{

  char *innew;
  APC *newapc;
  int i;

  newapc = (APC *) malloc(sizeof(APC));
  assert(newapc);

  newapc->bytesize = nsize;
  newapc->signb = 0;
  newapc->extend = 0;
  newapc->vals = (unsigned char *) 
    malloc(sizeof (unsigned char) * nsize);
  assert(newapc->vals);

  for (i=0; i<nsize; i++)
    newapc->vals[i] = 0;

  return(newapc);

}

// AP Copier

APC *apcopy(APC *inapc)
{

  char *innew;
  APC *newapc;
  int i,nsize;

  newapc = (APC *) malloc(sizeof(APC));
  assert(newapc);

  nsize = newapc->bytesize = inapc->bytesize;
  newapc->signb = inapc->signb;
  newapc->extend = inapc->extend;
  newapc->vals = (unsigned char *) 
    malloc(sizeof (unsigned char) * nsize);
  assert(newapc->vals);

  for (i=0; i<nsize; i++)
    newapc->vals[i] = inapc->vals[i];

  return(newapc);

}

// AP Destructor
  
void apdestroy(APC *desapc)
{

  if (desapc==NULL) return;

  assert(desapc->vals);  // Should never be NULL

  free(desapc->vals);

  free(desapc);
}

// Check for equality

int abeq(APC *num1, APC *num2, int ignsign)
{

  int i,m,m1,m2;

  assert(num1->extend==0 && num2->extend==0);  // Never call with 2c

  if (!ignsign) 
    if (num1->signb != num2->signb) return(0);

  m1 = num1->bytesize;
  m2 = num2->bytesize;
  m = max(m1, m2);

  for (i=0; i<m; i++) {
    if (i>=m1 && num2->vals[i]) return(0);
    if (i>=m2 && num1->vals[i]) return(0);
  }
  
  return(1);

}

// Check for magnitude
//
//   if ignsign
//         if abeq(num1,num2) then return 0
//         if num1 > num2 then return 1 else return -1
//   else
//         if num1 is +, num2 is -, return 1
//         if num2 is -, num2 is +, return -1
//         if abeq(num1,num2) return 0
//         if both pos and num1 > num2 then return 1 else -1
//         if both neg and num2 < num1 then return 1 else -1

int abcmp(APC *num1, APC *num2, int ignsign)
{

  int i,m,m1,m2,big;

  assert(num1->extend==0 && num2->extend==0);  // Never call with 2c
  
  if (!ignsign) {
    if (num1->signb==0 && num2->signb==1) return(1);
    else return(-1);
    if (num1->signb==1 && num2->signb==0) return(-1);
    else return(1);
  }

  i = abeq(num1,num2,ignsign);
  if (i) return(0);

  m1 = num1->bytesize;
  m2 = num2->bytesize;
  m = max(m1, m2);

  big = 1;
  for (i=0; i<m; i++) {
    if (i>=m1 && num2->vals[i]) {
      big = 0;
      break;
    }
    if (i>=m2 && num1->vals[i]) {
      big = 1;
      break;
    }
  }

  if (!ignsign && (num1->signb && num2->signb)) big = !big;
 
  if (big)
    return(1);
  else
    return(-1);

}

