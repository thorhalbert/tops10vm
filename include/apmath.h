// Arbitrary precision math routines

#define AP_OVERFLOW 1    // Not enough slots for output
#define AP_DIVZERO 2     // Division divides by zero

typedef struct _apc {
  int bytesize;          // How many 8 bit values
  char signb;            // 0 - Positive, 1 - Negative
  char extend;           // 0 - Not 2c, 1 - 2c
  unsigned char *vals;   // Array of values byte 0 - LSB
} APC;

