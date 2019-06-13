#include "op.h"

#include <unistd.h>
#include <sys/types.h>

int t10_CALLI_GETPPN(PCTX *ctx)
{

  uid_t uid;
  gid_t gid;

  BIGV t;

  uid = getuid();   // Map to UID/GID for now
  gid = getgid();

  t = gid;
  t <<= 18;
  t |= uid;

  WRITEMEM(jctx, ctx->AC, t);
  CHKERROR(jctx);

  // Non-Error return

  //  ctx->PC ++;  // JACCT + other user logged in

  return(OK_EXIT);

}

// Return the pid for the job id.  Pretty big, but all the 
// table sizes seem to support a very large jobid (17 bits)

int t10_CALLI_PJOB(PCTX *ctx)
{

  BIGV t;

  t = (BIGV) getpid();

  WRITEMEM(jctx, ctx->AC, t);
  CHKERROR(jctx);
  
  return(OK_EXIT);
}
