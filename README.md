# printf

A simple implementation of the printf function in C.

## Requirements

* C compiler
* Standard C library

## Features

* Supports the following conversion specifiers:
    * c: Prints a single character.
    * s: Prints a string.
    * %: Prints a literal percent sign.

## Installation

1. Clone the repository.
2. Compile the code:

gcc -Wall -Werror -o printf printf.c


## Usage

printf("Hello, world!\n");


## Examples

printf("The character is: %c\n", 'a');
printf("The string is: %s\n", "Hello, world!");


## Bugs and limitations

* Does not support flag characters, field width, or precision.
* Does not support length modifiers.
