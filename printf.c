#include "main.h"
/**
 * _printf - Custom printf function
 * @format: Format string
 *
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
	int i, count = 0;
	va_list args;

	va_start(args, format);
	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{
			i++;
			switch (format[i])
			{
				case 'c':
				{
					char c = va_arg(args, int);

					count += write(1, &c, 1);
					break;
				}
				case 's':
				{
					char *s = va_arg(args, char *);

					count += write(1, s, strlen(s));
					break;
				}
				case '%':
				{
					count += write(1, "%", 1);
					break;
				}
				default:
				break;
			}
		}
		else
			count += write(1, &format[i], 1);
	}
	va_end(args);
	return (count);
}
