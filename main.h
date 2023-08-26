#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>


typedef struct format
{
	char *id;
	int (*f)();
} convert_match;

int _putchar(char c);
int _printf(const char *format, ...);

#endif /* MAIN_H */
