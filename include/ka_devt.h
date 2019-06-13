struct {
  int dev;
  char *code;
} ka_io_devices[]= {
  { 00,"APR" },    /* Arithmetic Processor */
  { 00,"CPA" },    /* Arithmetic Processor */
  { 04,"PI" },     /* Priority Interrupt System */
  { 010,"PAG" },   /* Pager */
  { 014,"CCI" },   /* DA10 pdp8/9 int */
  { 020,"CCI2"},   /* DA10 pdp8/9 int */
  { 024,"ADC" },   /* AD10 ADC */
  { 030,"ADC2" },  /* AD10 ADC */
  { 060,"DLB" },   /* DL10 pdp-11 int */
  { 064,"DLC" },   /* DL10 pdp-11 int */
  { 070,"CLK" },   /* DK10 rtc */
  { 074,"CLK2" },  /* DK10 rtc */
  { 0100,"PTP" },  /* PT Punch */
  { 0104,"PTR" },  /* PT Reader */
  { 0110,"CDP" },  /* CP10 Card punch */
  { 0114,"CDR" },  /* 461 Card reader */
  { 0120,"TTY" },  /* Console tty */
  { 0124,"LPT" },  /* Line Printer */
  { 0130,"DIS" },  /* VB10 Display */
  { 0134,"DIS2" }, /* VB10 Display */
  { 0140,"PLT" },  /* XY10 Plotter */
  { 0144,"PLT2" }, /* XY10 Plotter */
  { 0150,"CR" },   /* CR10 Card Reader */
  { 0154,"CR2" },  /* CR10 Card Reader */
  { 0160,"DLB2" }, /* DL10 pdp-11 int */
  { 0164,"DLC2" }, /* DL10 pdp-11 int */
  { 0170,"DSK" },  /* RC10 Small Disk */
  { 0174,"DSK2" }, /* RC10 Small Disk */
  { 0200,"DC" },   /* PDP6 Data Control Channel */
  { 0204,"DC2" },  /* PDP6 Data Control Channel */
  { 0210,"UTC" },  /* PDP6 Dectape Control */
  { 0214,"UTS" },  /* PDP6 Dectape Status */
  { 0220,"MTC" },  /* DX10 Magtape Controller */
  { 0224,"MTS" },  /* DX10 Magtape #2 */
  { 0230,"MTM" },  /* DX10 Magtape #3 */
  { 0234,"LPT2" }, /* LP10 Printer */
  { 0240,"DLS" },  /* DC10 Data Line Scanner */
  { 0244,"DLS2" }, /* DC10 Data Line Scanner */
  { 0250,"DPC" },  /* RP10 Disk Pack */
  { 0254,"DPC2" }, /* RP10 Disk Pack */
  { 0260,"MDF" },  /* RA10 Mask Disk File */
  { 0260,"DPC3" }, /* RP10 Disk Pack */
  { 0264,"MDF2" }, /* RA10 Mass Disk File */
  { 0264,"DPC4" }, /* RP10 Disk Pack */
  { 0270,"DDC" },  
  { 0270,"DF" },
  { 0274,"DDC2" },
  { 0300,"DCSA" },
  { 0304,"DCSB" },
  { 0320,"DTC" },  /* TD10 Dectape Control */
  { 0324,"DTS" },  /* TD10 Dectape Status */
  { 0330,"DTC2" }, /* TD10 Dectape Control */
  { 0334,"DTS2" }, /* TD10 Dectape Status */
  { 0340,"TMC" },  /* TM10 Mag Tape Control */
  { 0344,"TMS" },  /* TM10 Mag Tape Status */
  { 0350,"TMC2" }, /* TM10 Mag Tape Control */
  { 0354,"TMS2" }, /* TM10 Mag Tape Status */
  { 0460,"DSS" },  /* DS10 Single Sync Line Unit */
  { 0464,"DSI" },  /* DS10 Single Sync Line Unit */
  { 0470,"DSS2" }, /* DS10 Single Sync Line Unit */
  { 0474,"DSI2" }, /* DS10 Single Sync Line Unit */
  { 01000, 0 },
};
