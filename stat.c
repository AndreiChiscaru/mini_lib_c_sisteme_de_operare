// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/syscall.h>
#include <fcntl.h>
#include <errno.h>

int stat(const char *restrict path, struct stat *restrict buf)
{
	int r = syscall(__NR_stat, path, buf);
    if (r < 0) {
        errno = -r;
        return -1;
    }
    return 0;
}
