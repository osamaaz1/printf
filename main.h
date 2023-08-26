#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
typedef struct format
{
	char *id;
	int (*f)();
} convert_match;


int printf_37(void);
int printf_char(va_list val);
int printf_string(va_list val);
int _putchar(char c);
int _printf(const char *format, ...);

#endif /* MAIN_H */

