#ifndef TLPI_HDR_H
#define TLPI_HDR_H      // предотвращает случайное двойное включение

#include <sys/types.h>  // определения типов, используемых многими программами

#include <stdio.h>      /* стандартные функии ввода-вывода */
#include <stdlib.h>     /* прототипы наиболее востребованных библиотечных
                         функций и констант */
#include <unistd.h>     /* прототипы многих системных вызовов */
#include <errno.h>      /* Объявление errno и определение констант ошибок */ 
#include <string.h>     /* Наиболее используемые функции обработки строк */
#include "get_num.h"    /* Объявление нашей функции для обработки чисел */

#include "error_functions.h" // Функции обработки ошибок
typedef enum{FALSE, TRUE} Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

#endif
