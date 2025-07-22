// syscalls.c
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int _close(int fd) { (void)fd; errno = ENOSYS; return -1; }
int _lseek(int fd, int ptr, int dir) { (void)fd; (void)ptr; (void)dir; errno = ENOSYS; return -1; }
int _read(int fd, void *ptr, size_t len) { (void)fd; (void)ptr; (void)len; errno = ENOSYS; return -1; }
int _write(int fd, const void *ptr, size_t len) { (void)fd; (void)ptr; (void)len; errno = ENOSYS; return -1; }
int _fstat(int fd, struct stat *st) { (void)fd; st->st_mode = S_IFCHR; return 0; }
int _isatty(int fd) { (void)fd; return 1; }
int _open(const char *name, int flags, int mode) { (void)name; (void)flags; (void)mode; errno = ENOSYS; return -1; }