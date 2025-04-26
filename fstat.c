// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <errno.h>

int fstat(int fd, struct stat *st)
{
    int r = syscall(__NR_fstat, fd, st);
    if (r < 0) {
        errno = -r;
        return -1;
    }
    return 0;
}
