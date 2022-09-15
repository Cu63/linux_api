#include <stdio.h>
#include <stdlib.h>


char globBuf[65536]; // Сегмент неициализированных данных
int primes[] = {2, 3, 5, 7}; // Сегмент инициализированных данных


static int square(int x) { //размещает в фрейме для square()
    int result;
    result = x * x;
    return result; // возвращает данных через регистр
}


static void doCalc(int val) { // Размещает во фрейме для doCalc()
    printf("The square of %d is %d\n", val, square(val));
    if (val < 1000) {
        int t;
        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}


int main(int argc, char *argv[]) { // frame main()
    static int key = 9973; // segment init
    static char mbuf[10240000]; // segment not init
    char *p; //frame main

    p = malloc(1024); //heap
    doCalc(key);
    exit(EXIT_SUCCESS);
}
