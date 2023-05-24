#include "shell.h"

/**
 * return true if it is interactive and false if otherwise
 * return 0 if not interactive and 1 if yes
 */

int interactive(info_x *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim is applied so as to check whether the value is a delimeter
 * char to check is y
 * string delimeter is delim
 * 0 is returned if false and 1 when otherwise
 */
int is_delim(char y, char *delim)
{
	while (*delim)
		if (*delim++ == y)
			return (1);
	return (0);
}

/**
 * _isalpha is used to point out alphabetic character
 * Input character is y
 * 1 is returned  if y is alphabetic and 0 if otherwise
 */

int _isalpha(int y)
{
	if ((y >= 'a' && y <= 'z') || (y >= 'A' && y<= 'Z'))
		return (1);
	else
		return (0);
}


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
