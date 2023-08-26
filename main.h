#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
typedef struct format
{
	char *id;
	int (*f)();
} convert_match;


int _printf(const char *format, ...);
int _putchar(char c);

#endif /* MAIN_H */

