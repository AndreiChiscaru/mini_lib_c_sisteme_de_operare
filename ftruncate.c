// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int ftruncate(int fd, off_t length)
{
	if (length < 0) {
        errno = EINVAL;
        return -1;
    }

    int result = syscall(77, fd, length);

    if (result < 0) {
        if (result == -EBADF) {
            errno = EBADF;
        } else if (result == -EINVAL) {
            errno = EINVAL;
        } else if (result == -EISDIR) {
            errno = EISDIR;
        } else {
            errno = -result;
        }
        return -1;
    }

    return result;
}
