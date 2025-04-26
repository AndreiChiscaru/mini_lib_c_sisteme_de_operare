// SPDX-License-Identifier: BSD-3-Clause

#include <internal/io.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>

ssize_t write(int fd, const void *buf, size_t len)
{
	int r = syscall(__NR_write, fd, buf, len);
	if (r < 0) {
		errno = -r;
		return -1;
	}
	return r;
}

ssize_t read(int fd, void *buf, size_t len)
{
	int r =  syscall(__NR_read, fd, buf, len);
	if (r < 0) {
		errno = -r;
		return -1;
	}
	return r;
}
