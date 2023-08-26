#include "main.h"
/**
 * _printf - Custom printf function
 * @format: Format string
 *
 * Return: Number of characters printed
 */
int _printf(const char *format, ...) {
	va_list args;
	va_start(args, format);
	int count = 0;
	char c;

	while ((c = *format++) != '\0')
	{
		if (c != '%')
		{
			putchar(c);
			count++;
		}
		else
		{
			c = *format++;
			if (c == 'c')
			{
				putchar(va_arg(args, int));
				count++;
			}
			else if (c == 's')
			{
				char *str = va_arg(args, char *);
				while (*str != '\0')
				{
					putchar(*str++);
					count++;
				}
			}
			else if (c == '%')
			{
				putchar('%');
				count++;
			}
		}
	}
	va_end(args);
	return (count);
}
