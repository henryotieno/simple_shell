#include "shell.h"

/**
 * av - in interactive mode the shell returns true
 * @info: address at the struct
 *
 * Return: interactive mode shows 1, 0 otherwise
 */

int interactive(info_x *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - character is checked if it is a delimeter
 * @y: the char we want
 * @delim: is delimeter string
 * Return: true if 1, 0 if false
 */

int is_delim(char y, char *delim)
{
	while (*delim)
		if (*delim++ == y)
			return (1);
	return (0);
}

/**
 * _isalpha - alphabetic character is searched
 * @y: what to input
 * Return: if c is alphabetic show 1, 0 otherwise
 */

int _isalpha(int y)
{
	if ((y >= 'a' && y <= 'z') || (y >= 'A' && y <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - changes the string to an integer
 * @b: a string that is to be manipulated
 * Return: 0 if no string, 1 if true
 */

int _atoi(char *b)
{
	int m, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (m = 0; b[m] != '\0' && flag != 2; m++)
	{
		if (b[m] == '-')
			sign *= -1;

		if (b[m] >= '0' && b[m] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (b[m] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
