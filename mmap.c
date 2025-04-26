// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	if ((flags & MAP_ANONYMOUS) == 0 && fd < 0) {
        errno = EBADF;
        return MAP_FAILED;
    }
    if ((flags & MAP_ANONYMOUS) && (flags & MAP_SHARED)) {
        errno = EINVAL;
        return MAP_FAILED;
    }
    void *r = (void *)syscall(9, addr, length, prot, flags, fd, offset);
    if (r == (void *)-1) {
        switch (errno) {
            case EACCES:
            case EAGAIN:
            case EBADF:
            case EINVAL:
            case ENOMEM:
            case EPERM:
                break;
            default:
                errno = EIO;
                break;
        }
        return MAP_FAILED;
    }
    return r;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	void *r = (void *)syscall(__NR_mremap, old_address, old_size, new_size, flags);
	if (r == MAP_FAILED) {
		switch (errno) {
			case EAGAIN:
				errno = EAGAIN;
				break;
			case EFAULT:
				errno = EFAULT;
				break;
			case EINVAL:
				errno = EINVAL;
				break;
			case ENOMEM:
				errno = ENOMEM;
				break;
			default:
				errno = EIO;
				break;
		}
		return MAP_FAILED;
	}
	return r;
}

int munmap(void *addr, size_t length)
{
	int r = syscall(__NR_munmap, addr, length);
	if (r == -1) {
		switch (errno) {
			case EINVAL:
				errno = EINVAL;
				break;
			case ENOMEM:
				errno = ENOMEM;
				break;
			default:
				errno = EIO;
				break;
		}
		return -1;
	}
	return 0;
}