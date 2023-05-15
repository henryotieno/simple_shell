#include "shell.h"

/**
 * variable that changes a string to an integer is erratoi
 */
int _erratoi(char *s)
{
	int m = 0;
	unsigned long int result = 0;

	if (*b == '+')
		b++;  
	for (m = 0;  b[m] != '\0'; m++)
	{
		if (b[m] >= '0' && b[m] <= '9')
		{
			result *= 10;
			result += (b[m] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

void print_error(info_x *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_y(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_y is a function that prints a decimal to base 10
 * printed number of characters is returned 
 */
int print_y(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int m, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (m = 1000000000; m > 1; m /= 10)
	{
		if (_abs_ / m)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= m;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * change_number changes a function
 * @num:  represents number
 * @base: represents base
 * @flags: represents flags
 *
 * string is returned
 */
char *change_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long d = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		d = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[d % base];
		d /= base;
	} while (d != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * @buf: represents address that is to be changed
 *
 * Always returns a value 0;
 */
void remove_comments(char *buf)
{
	int m;

	for (m = 0; buf[m] != '\0'; m++)
		if (buf[m] == '#' && (!m || buf[m - 1] == ' '))
		{
			buf[m] = '\0';
			break;
		}
}

