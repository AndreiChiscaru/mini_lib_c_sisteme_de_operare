#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...) {
    va_list args;
    mode_t mode = 0;
    if (flags & O_CREAT) {
        va_start(args, flags);
        mode = va_arg(args, mode_t);
        va_end(args);
    }
    int fd = syscall(2, filename, flags, mode);
    if (fd < 0) {
        errno = -fd;
        fd = -1;
    }
    return fd;
}
