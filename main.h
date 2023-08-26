#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED_VAR(x) (void)(x)
#define BUFFER_SIZE 1024

#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_ZERO 4
#define FLAG_HASH 8
#define FLAG_SPACE 16

#define MOD_LONG 3
#define MOD_SHORT 1

struct format_handler {
    char specifier;
    int (*handler_fn)(va_list, char[], int, int, int, int);
};

typedef struct format_handler format_handler_t;

int custom_printf(const char *format, ...);
int handle_format(const char *fmt, int *i,
    va_list list, char buffer[], int flags, int width, int precision, int size);

/****************** FUNCTION HANDLERS ******************/

int handle_char(va_list args, char buffer[],
    int flags, int width, int precision, int size);
int handle_string(va_list args, char buffer[],
    int flags, int width, int precision, int size);
int handle_percent(va_list args, char buffer[],
    int flags, int width, int precision, int size);
int handle_int(va_list args, char buffer[],
    int flags, int width, int precision, int size);
int handle_binary(va_list args, char buffer[],
    int flags, int width, int precision, int size);
int handle_unsigned(va_list args, char buffer[],
    int flags, int width, int precision, int size);
int handle_octal(va_list args, char buffer[],
    int flags, int width, int precision, int size);
int handle_hexadecimal(va_list args, char buffer[],
    int flags, int width, int precision, int size);
int handle_hexadecimal_upper(va_list args, char buffer[],
    int flags, int width, int precision, int size);
int handle_non_printable(va_list args, char buffer[],
    int flags, int width, int precision, int size);
int handle_pointer(va_list args, char buffer[],
    int flags, int width, int precision, int size);
int handle_reverse(va_list args, char buffer[],
    int flags, int width, int precision, int size);
int handle_rot13(va_list args, char buffer[],
    int flags, int width, int precision, int size);

int get_format_flags(const char *format, int *i);
int get_format_width(const char *format, int *i, va_list list);
int get_format_precision(const char *format, int *i, va_list list);
int get_format_modifier(const char *format, int *i);

int write_formatted_char(char c, char buffer[],
    int flags, int width, int precision, int size);
int write_formatted_number(int is_positive, int ind, char buffer[],
    int flags, int width, int precision, int size);
int write_formatted_num(int ind, char bff[], int flags, int width, int precision,
    int length, char padding_char, char extra_char);
int write_formatted_pointer(char buffer[], int ind, int length,
    int width, int flags, char padding_char, char extra_char, int padding_start);
int write_formatted_unsigned(int is_negative, int ind,
    char buffer[], int flags, int width, int precision, int size);

int is_printable_char(char c);
int append_formatted_hex_code(char value, char buffer[], int index);
int is_digit_char(char c);

long int convert_size_number(long int num, int size);
long int convert_size_unsigned(unsigned long int num, int size);

#endif /* PRINT_UTILS_H */
