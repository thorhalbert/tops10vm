// Tops-10 I/O Drivers

// Simple File Handling (INIT,OPEN,ENTER,LOOKUP,ENTER (non FILOP.))

#define T10SFH_MAXCHAN 020   // Number of channels 

#define SFHCHAN(a) ((a) & 017)

#define SFH_STATE_CLOSED 0   // Nothing
#define SFH_STATE_OPEN 10    // Device Opened - needs file (no unix file open yet)
#define SFH_STATE_DEVICE 15  // Device doesn't need file - ready for I/O (TTY, LPT, etc)
#define SFH_STATE_FILE 20    // File opened on Device (ENTER or LOOKUP)

#define SFH_DEVICE_UNKNOWN 0 // Unknown device
#define SFH_DEVICE_TTY 1     // Terminal device - may open STDIN/OUT
#define SFH_DEVICE_DSK 2     // Disk device - no device open till file
#define SFH_DEVICE_LPT 3     // Line printer
#define SFH_DEVICE_MTA 4     // Mag Tape
#define SFH_DEVICE_PTY 5     // PTY - Pseudo Terminal
#define SFH_DEVICE_PLT 6     // Plotter

#define SFH_FLAG_STDOUT 00001 // File is STDOUT - no need to actually close it
#define SFH_FLAG_IOSAME 00002 // iv and ov are same, just close one of them

typedef struct t10sfh_chans {
  char state;         // What state is the channel in
  char devtype;       // What device type is it?  Need driver for each
  int flags;          // Special status flags for channel
  int filemode;       // Tops-10 file open mode
  BIGV dOPMOD;        // Copy of Open Mode bits
  BIGV dOPDEV;        // Copy of Open Device Spec (sixbit)
  BIGV dOPBUF;        // Pointer to device buffer in userspace (optional)
  char devnam[7];     // ASCII version of device name
  BIGV RIBBLK[050];   // Copy of extended open RIB block (ENTER, LOOKUP, RENAME)
  int inbufs;         // Number of input buffers (INBUF)
  int outbufs;        // Number of output buffers (OUTBUF)
  //----------
  int proj,prog;      // PPN
  char *pathspec;     // A possible path
  char file[7];       // Filename
  char ext[4];        // Extension
  int creation;       // Creation date
  int createtime;     // Creation time
  int access;         // Access date
  int errorcode;      // The resulting error
  int protection;     // File protection
  int createmode;     // Mode file created in
  int filesize;       // In words
  int preallocate;    // In 128W blocks
  char lun[7];        // Logical unit name of device
  //----------
  char *actfile;      // Actual file
  FILE *ov;           // The actual opened file (output channel)
  FILE *iv;           // Input channel (may be same as out)
  
} T10SFH;

#define T10SFH_SIZE (sizeof(T10SFH))

struct devhandler {
  char *devfrc;    /* Canonical Name */
  char *shtname;   /* Short name */
  int iomod[020];  /* IO modes permitted */
};

#ifdef DEFCONSTANTS
struct devhandler devlist[] = {
  //              0   1   2   3   4   5   6   7  10  11  12  13  14  15  16  17
  //            ASC ASL PIM BYT AS8             IMG         IBN BIN IDP DPR DMP
  { "TTY", "TT",  1,  1,  1,  0,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0 },
  { "DSK", "DS",  1,  1,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  1,  0,  1,  1 },
  { "LPT", "LP",  1,  1,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0 },
  { "MTA", "MT",  1,  1,  0,  1,  0,  0,  0,  0,  1,  0,  0,  1,  1,  0,  1,  1 },
  { "PTY", "  ",  1,  1,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
  { "PLT", "  ",  1,  1,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  1,  0,  0,  0 },
  { NULL },
};

// FILOP. File Handling

