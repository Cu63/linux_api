#ifndef GET_NUM_H
#define GET_NUM_H
#define GN_NONNEG   01 // Значение должно быть >= 0
#define GN_GT_0     02 // Значение должно быть > 0


#define GN_ANY_BASE 0100 // Основание по умолчанию
#define GN_BASE_8   0200 // Значение выражено в виде восьмеричного числа
#define GN_BASE_16  0400 // Значение выражено в виде шестнадцатиричного числа


long getLong(const char *name, int flags, const char *name);


#endif
