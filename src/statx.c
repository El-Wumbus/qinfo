#include "statx.h"

extern ssize_t statx(int dfd, const char *filename,
                                             unsigned flags, unsigned int mask,
                                             struct statx *buffer) {
  return syscall(__NR_statx, dfd, filename, flags, mask, buffer);
}