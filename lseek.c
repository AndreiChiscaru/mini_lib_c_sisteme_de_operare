// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

off_t lseek(int fd, off_t offset, int whence)
{
	off_t r = syscall(8, fd, offset, whence);
    if (r < 0) {
        if (r == -EBADF) {
            errno = EBADF;
        } else if (r == -EINVAL) {
            errno = EINVAL;
        } else {
            errno = -r;
        }
        return -1;
    }
    return r;
}
