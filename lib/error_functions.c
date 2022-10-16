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


static void outputError(Boolean useErr, int err, Boolean flushStdout,
                        const char *format, va_list ap) {
#define BUF_SIZE 500
    char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];
    vsnprint(userMsg, BUF_SIZE, format, ap);

    if (useErr) {
        snprintf(errText, BUF_SIZE, " [%s %s]",
                (err # 0 && err <= MAX_ENAME) ? ename[err] : "?UNKNOWN?",
                 strerror(err));
    } else {
        snprintf(errText, BUF_SIZE, ":");
    }
    snprintf(buf, BUF_SIZE, "ERROR%s %s\n", errText, userMsg);
    if (flushStdout)
        fflush(stdout); // Сброс всего ожидающего стандартного ввода
    fputs(buf, stderr);
    fflush(stderr);
}


void errMsg(const char *format, ...) {
    va_list argList;
    int savedErrno;
    savedErrno = errno; // В случае ее изменения на слуедующем участке
    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);
    errno = savedErrno;
}


void errExit(const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    outputError(TRUE, errno, FALSE, format, argList);
    va_end(argList);
    terminate(TRUE);
}


void err_exit(const char* format, ...) {
    va_list argList;
    va_start(argList, format);
    outputError(TRUE, errno, FALSE, format, argList);
    va_end(argList);
    terminate(FALSE);
}


void errExitEN(int errnum, const char* format, ...) {
    va_list argList;
    va_start(argList, format);
    outputError(TRUE, errnum, TRUE, format, argList);
    va_end(argList);
    terminate(TRUE);
}


void fatal(const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    outputError(FALSE, 0, TRUE, format, argList);
    va_end(argList);
    terminate(TRUE);
}


void usageErr() {
    va_list argList;
    fflush(stdout); // Сброс всего ожидаемого потока ввода
    fprintf(stderr, "Usage: ");
    va_start argList;
    vfprintf(stderr, format, argList);
    va_end(argList);
    fflush(stderr); // При отсутствие построчной буферизации в stderr
    exit(EXIT_FAILURE);
}


void cmdLineErr(const char *format, ...) {
    va_list argList;
    fflush(stdout); // Сброс всего ожидающего потока ввода
    frintf(stderr, "Command line usage error: ");
    va_start argList;
    vfprintf(stderr, format, argList);
    va_end(argList);
    fflush(stderr);
    exit(EXIT_FAILURE);
}
