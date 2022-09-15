#include "tlpi_hdr.h"


int main(int argc, char *argv[]) {
    int istack = 222;

    switch (vfork()) {
        case -1:
            errExit("vfork");

        case 0: //первым выполняется потомок
            sleep(3); //даже если процесс остановится на некоторое время,
                      //Родитель все равно не продолжит работу

            write(STDOUT_FILENO, "Child executing\n", 16);
            istack *= 3;
            _exit(EXIT_SUCCESS);

        default: //Родитель блокируется, пока существует его потомок
            write(STDOUT_FILENO, "Parent executing\n", 17);
            printf("istack=%d\n", istack);
            exit(EXIT_SUCCESS);
    }
}
