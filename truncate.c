// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int truncate(const char *path, off_t length)
{
	if (length < 0) {
        errno = EINVAL;
        return -1;
    }
    int r = syscall(76, path, length);
    if (r < 0) {
        if (r == -EISDIR) {
            errno = EISDIR;
        } else if (r == -ENOENT) {
            errno = ENOENT;
        } else {
            errno = -r;
        }
        return -1;
    }
    return r;
}
