#include "print_utils.h"

/***** HANDLE AND WRITE CHARACTER ***/
/**
 * handle_and_write_character - Handles and writes a character to the buffer
 * @character: Character to be written
 * @buffer: Buffer array to handle printing
 * @flags: Flag specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed.
 */
int handle_and_write_character(char character, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0;
	char padding_char = ' ';

	UNUSED_VAR(precision);
	UNUSED_VAR(size);

	if (flags & FLAG_ZERO)
		padding_char = '0';

	buffer[i++] = character;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFFER_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFFER_SIZE - i - 2] = padding_char;

		if (flags & FLAG_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFFER_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFFER_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}
/************************* WRITE FORMATTED NUMBER *************************/
/**
 * write_formatted_number - Writes a formatted number to the buffer
 * @is_negative: Indicator if the number is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Buffer array to handle printing
 * @flags: Flag specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed.
 */
int write_formatted_number(int is_negative, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFFER_SIZE - index - 1;
	char padding_char = ' ', extra_char = 0;

	UNUSED_VAR(size);

	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
		padding_char = '0';
	if (is_negative)
		extra_char = '-';
	else if (flags & FLAG_PLUS)
		extra_char = '+';
	else if (flags & FLAG_SPACE)
		extra_char = ' ';

	return (write_formatted_num(index, buffer, flags, width, precision,
		length, padding_char, extra_char));
}

/**
 * write_formatted_number - Writes a number using a buffer
 * @index: Index at which the number starts in the buffer
 * @buffer: Buffer
 * @flags: Flag specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @length: Number length
 * @padding_char: Padding char
 * @extra_char: Extra char
 *
 * Return: Number of printed characters.
 */

int write_formatted_number(int index, char buffer[],
			 int flags, int width, int precision,
			 int length, char padding_char, char extra_char)
{
	int i;

	if (precision == 0 && index == BUFFER_SIZE - 2 && buffer[index] == '0')
	{
		if (width == 0)
			return (0);
		buffer[index] = padding_char = ' ';
	}

	if (precision > 0 && precision < length)
		padding_char = ' ';
	while (precision > length)
		buffer[--index] = '0', length++;
	if (extra_char != 0)
		length++;

	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padding_char;
		buffer[i] = '\0';
		if (flags & FLAG_MINUS)
		{
			if (extra_char)
				buffer[--index] = extra_char;
			return (write(1, &buffer[index], length) + write(1, &buffer[1], i - 1));
		}
		else
		{
		if (extra_char)
			buffer[--index] = extra_char;
		return (write(1, &buffer[1], i) + write(1, &buffer[index], length - 1));
		}
	}
	if (extra_char)
		buffer[--index] = extra_char;
	return (write(1, &buffer[index], length));
}

/**
 * write_unsigned_number - Writes an unsigned number
 * @is_negative: Indicator if the number is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Array of characters
 * @flags: Flag specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written characters.
 */
int write_unsigned_number(int is_negative, int index,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFFER_SIZE - index - 1, i = 0;
	char padding_char = ' ';

	UNUSED_VAR(is_negative);
	UNUSED_VAR(size);

	if (precision == 0 && index == BUFFER_SIZE - 2 && buffer[index] == '0')
		return (0); /* printf(".0d", 0) no characters are printed */

	if (precision > 0 && precision < length)
		padding_char = ' ';

	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
		padding_char = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padding_char;

		buffer[i] = '\0';

		if (flags & FLAG_MINUS)
			/* Assign extra char to the left of buffer [buffer > padding] */
		{
			return (write(1, &buffer[index], length) + write(1, &buffer[0], i));
		}
		else /* Assign extra char to the left of padding [padding > buffer] */
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[index], length));
		}
	}

	return (write(1, &buffer[index], length));
}

/**
 * write_formatted_pointer - Writes a formatted pointer to the buffer
 * @buffer: The buffer to write to
 * @index: Current index in the buffer
 * @length: Length of the content
 * @width: Field width
 * @flags: Flags specifier
 * @padding_char: Char representing the padding
 * @extra_char: Char representing extra char
 * @padding_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_formatted_pointer(char buffer[], int index, int length,
		int width, int flags, char padding_char,
		char extra_char, int padding_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padding_char;
		buffer[i] = '\0';
		if (flags & FLAG_MINUS && padding_char == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_char)
				buffer[--index] = extra_char;
			return (write(1, &buffer[index], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & FLAG_MINUS) && padding_char == ' ')
			/* extra char to left of buffer */
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_char)
				buffer[--index] = extra_char;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[index], length));
		}
		else if (!(flags & FLAG_MINUS) && padding_char == '0')
			/* extra char to left of padding */
		{
			if (extra_char)
				buffer[--padding_start] = extra_char;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padding_start], i - padding_start) +
					write(1, &buffer[index], length - (1 - padding_start) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (extra_char)
		buffer[--index] = extra_char;
	return (write(1, &buffer[index], BUFFER_SIZE - index - 1));
}
