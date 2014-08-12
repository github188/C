#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * To change the process title in Linux and Solaris we have to set argv[1]
 * to NULL and to copy the title to the same place where the argv[0] points to.
 * However, argv[0] may be too small to hold a new title.  Fortunately, Linux
 * and Solaris store argv[] and environ[] one after another.  So we should
 * ensure that is the continuous memory and then we allocate the new memory
 * for environ[] and copy it.  After this we could use the memory starting
 * from argv[0] for our process title.
 *
 * The Solaris's standard /bin/ps does not show the changed process title.
 * You have to use "/usr/ucb/ps -w" instead.  Besides, the UCB ps does not
 * show a new title if its length less than the origin command line length.
 * To avoid it we append to a new title the origin command line in the
 * parenthesis.
 */

extern char **environ;

/* XXX: User should defined and initial this variable */
extern char **os_argv;

static char *_os_argv_last;

static u_char * _cpystrn(u_char *dst, u_char *src, size_t n)
{
    if (n == 0) {
        return dst;
    }

    while (--n) {
        *dst = *src;

        if (*dst == '\0') {
            return dst;
        }

        dst++;
        src++;
    }

    *dst = '\0';

    return dst;
}

int init_setproctitle()
{
    u_char *p;
    size_t size;
    int    i;

    size = 0;

    for (i = 0; environ[i]; i++) {
        size += strlen(environ[i]) + 1;
    }

	p = malloc(size);
    if (p == NULL) {
        return 1;
    }

    _os_argv_last = os_argv[0];

    for (i = 0; os_argv[i]; i++) {
        if (_os_argv_last == os_argv[i]) {
            _os_argv_last = os_argv[i] + strlen(os_argv[i]) + 1;
        }
    }

    for (i = 0; environ[i]; i++) {
        if (_os_argv_last == environ[i]) {

            size = strlen(environ[i]) + 1;
            _os_argv_last = environ[i] + size;

            _cpystrn(p, (u_char *) environ[i], size);
            environ[i] = (char *) p;
            p += size;
        }
    }

    _os_argv_last--;

    return 0;
}

void setproctitle(char *title)
{
    u_char     *p;

    os_argv[1] = NULL;

    p = _cpystrn((u_char *) os_argv[0], (u_char *) title,
                    _os_argv_last - os_argv[0]);

    if (_os_argv_last - (char *) p) {
        memset(p, '\0', _os_argv_last - (char *) p);
    }

}

