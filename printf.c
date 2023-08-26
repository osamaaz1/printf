/**
 * _printf - This function produces output according to a format.
 * @format: The format string containing conversion specifiers.
 * Return: The number of characters printed (excluding the null byte).
 */
int _printf(const char *format, ...)
{
		va_list args;
	int count = 0;

	va_start(args, format);

	while (*format)
	{
		if (*format != '%')
			putchar(*format), count++;
		else
		{
			format++;
			if (*format == 'c')
				putchar(va_arg(args, int));
				count++;
			else if (*format == 's')
				for (char *str = va_arg(args, char *); *str; putchar(*str++), count++);
			else if (*format == '%')
				putchar('%'), count++;
		}
		format++;
	}
	va_end(args);
	return count;
}
