#include <stdarg.h>
#include "error_functions.h"
#include "tlpi_hdr.h"
#include "ename.c.inc"

#ifdef __GNUC__
__attribute__ ((__noreturn__))
#endif

static void terminate(Boolean useExit3) {
    char *s;
    /* Сохраняет дамп ядра, если переменная среды EF_DUMPCORE определена
     * и содержит непустую строку; в противном случае вызывается exit(3)
     * или _exit(2), в зависимости от значания useExit3.
     */
    s = getenv("EF_DUMPCORE");
    if (s != NULL && *s != '\0')
        abort();
    else if (useExit3)
        exit(3);
    else
        _exit(2);

}
