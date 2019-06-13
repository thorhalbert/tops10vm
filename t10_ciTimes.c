#include "op.h"

#include <time.h>
#include <sys/time.h>

static time_t lmid = 0;

void setmid()
{

  struct tm loc;
  time_t lt;

  lt = time(NULL);
  (void) localtime_r(&lt, &loc);
  loc.tm_sec = 0;
  loc.tm_min = 0;
  loc.tm_hour = 0;
  
  lmid = mktime(&loc);

}

// Number of milliseconds since midnight (local time)
// No error return

// gettimeofday may be only high-resolution time for cygwin

_SUB int t10_CALLI_MSTIME(PCTX *ctx)
{

  struct timeval tp;
  struct timezone tzp;
  BIGV rval;

  (void) gettimeofday(&tp,&tzp);

  if (tp.tv_sec - lmid > 86400) setmid(); // Set midnight if needed

  rval = tp.tv_sec - lmid;
  rval *= 1000;
  rval += tp.tv_usec / 1000;

  WRITEMEM(jctx, ctx->AC, rval);
  CHKERROR(jctx);
  
  return(OK_EXIT);
}

// Return date
//        code = 31[12(year-1964)+(month-1)]+(day-1)
//        day    =  mod(code,31)+1
//        month  =  mod(code/31,12)+1
//        year   =  (code/372)+1964
//   No error return

_SUB int t10_CALLI_DATE(PCTX *ctx)
{

  struct tm intm;
  time_t it;
  int rtim;

  it = time(NULL);
  (void) localtime_r(&it, &intm);

  rtim = (31*((12*(intm.tm_year-64)) + (intm.tm_mon))) + (intm.tm_mday-1);

  WRITEMEM(jctx, ctx->AC, rtim);
  CHKERROR(jctx);

  return(OK_EXIT);

}

// Return time since midnight in jiffies (1/60 sec)

_SUB int t10_CALLI_TIMER(PCTX *ctx)
{

  struct timeval tp;
  struct timezone tzp;
  BIGV rval;

  (void) gettimeofday(&tp,&tzp);

  if (tp.tv_sec - lmid > 86400) setmid(); // Set midnight if needed

  rval = tp.tv_sec - lmid;
  rval *= 60;
  rval += tp.tv_usec / 16667;

  WRITEMEM(jctx, ctx->AC, rval);
  CHKERROR(jctx);
  
  return(OK_EXIT);

}

