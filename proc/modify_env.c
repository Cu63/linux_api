#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>


extern char **environ;


int main(int argc, char *argv[]) {
    int j;
    char **ep;

    clearenv();

    for (j = 1; j < argc; j++)
        if (putenv(argv[j]) != 0)
            printf("error in putenv\n");
            return -1;
    if (setenv("GREET", "Hello world", 0) == -1) {
        printf("error in setenv\n");
        return -1;
    }
    unsetenv("BYE");
    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);
    exit(EXIT_SUCCESS);
}
