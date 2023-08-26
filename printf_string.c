#include "main.h"
/**
 * printf_string - print a string.
 * @val: argumen t.
 * Return: the length of the string.
 */

int printf_string(va_list val)
{
	char *sa;
	int i, len;

	sa = va_arg(val, char *);
	if (sa == NULL)
	{
		sa = "(null)";
		len = _strlen(sa);
		for (i = 0; i < len; i++)
			_putchar(sa[i]);
		return (len);
	}
	else
	{
		len = _strlen(sa);
		for (i = 0; i < len; i++)
			_putchar(sa[i]);
		return (len);
	}
}
