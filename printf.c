#include "main.h"

/**
 * _printf - This function selects the correct conversion function to print
 *           based on the provided format.
 * @format: The format string containing conversion specifiers.
 * Return: The total number of characters printed.
 */
int _printf(const char * const format, ...)
{
	convert_match conversion_funcs[] = {
	{"%s", printf_string}, {"%c", printf_char},
	{"%%", printf_percent},
	{"%i", printf_int}, {"%d", printf_decimal}, {"%r", printf_reverse},
	{"%R", printf_rot13}, {"%b", printf_binary}, {"%u", printf_unsigned},
	{"%o", printf_octal}, {"%x", printf_hex}, {"%X", printf_HEX},
	{"%S", printf_exclusive_string}, {"%p", printf_pointer}
	};

	va_list args;
	int i = 0, j, total_chars_printed = 0;

	va_start(args, format);
	while (format[i] != '\0')
	{
		j = 13;
		while (j >= 0)
		{
			if (conversion_funcs[j].specifier[0] == format[i] &&
			conversion_funcs[j].specifier[1] == format[i + 1])
			{
			total_chars_printed += conversion_funcs[j].function(args);
			i = i + 2;
			goto Continue;
			}
			j--;
		}

		_putchar(format[i]);
		total_chars_printed++;
		i++;

Continue:
	continue;
	}

	va_end(args);
	return (total_chars_printed);
}
