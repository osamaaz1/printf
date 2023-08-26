#include "print_utils.h"

void print_output_buffer(char output_buffer[], int *output_buffer_index);

/**
 * custom_printf - Custom printf function
 * @format: Format string.
 * Return: Number of printed characters.
 */
int custom_printf(const char *format, ...)
{
	int i, printed_count = 0, total_printed_chars = 0;
	int format_flags = 0, format_width = 0, format_precision = 0;
	int format_modifier = 0, output_buffer_index = 0;
	va_list arguments_list;
	char output_buffer[BUFFER_SIZE];

	if (format == NULL)
		return (-1);
	va_start(arguments_list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			output_buffer[output_buffer_index++] = format[i];
			if (output_buffer_index == BUFFER_SIZE)
				print_output_buffer(output_buffer, &output_buffer_index);
			printed_count++;
		}
		else
		{
			print_output_buffer(output_buffer, &output_buffer_index);
			format_flags = get_format_flags(format, &i);
			format_width = get_format_width(format, &i, arguments_list);
			format_precision = get_format_precision(format, &i, arguments_list);
			format_modifier = get_format_modifier(format, &i);
			++i;
			printed_count = handle_format(format, &i, arguments_list, output_buffer,
				format_flags, format_width, format_precision, format_modifier);
			if (printed_count == -1)
				return (-1);
			total_printed_chars += printed_count;
		}
	}

	print_output_buffer(output_buffer, &output_buffer_index);

	va_end(arguments_list);

	return (total_printed_chars);
}

/**
 * print_output_buffer - Prints the contents of the output buffer if it exists
 * @output_buffer: Array of characters to be printed
 * @output_buffer_index: Index indicating the current length of the buffer
 */
void print_output_buffer(char output_buffer[], int *output_buffer_index)
{
	if (*output_buffer_index > 0)
		write(1, &output_buffer[0], *output_buffer_index);

	*output_buffer_index = 0;
}
