#include <linux/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
/* Special value used to indicate openat should use the current working
 * directory. */
#define AT_FDCWD -100

#define AT_STATX_SYNC_TYPE 0x6000
#define AT_STATX_SYNC_AS_STAT 0x0000
#define AT_STATX_FORCE_SYNC 0x2000
#define AT_STATX_DONT_SYNC 0x4000
#define AT_STATX_SYNC_TYPE_MASK 0x6000
#define AT_STATX_MTIME 0x00000040U
#define AT_STATX_BTIME 0x00000800U

#ifndef __NR_statx
#define __NR_statx -1
#endif

extern ssize_t mstatx(int dfd, const char *filename,
                                             unsigned flags, unsigned int mask,
                                             struct statx *buffer);