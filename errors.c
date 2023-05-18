#include "shell.h"

/**
 * _eputs – input string will be displayed
 * Always returns nothing
 */
void _eputs(char *str)
{
	int m = 0;

	if (!str)
		return;
	while (str[m] != '\0')
	{
		_eputchar(str[m]);
		m++;
	}
}

/**
 * _eputchar – outputs character o.
 * 1 is returned upon success
 */
int _eputchar(char o)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (o == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(2, buf, m);
		m = 0;
	}
	if (o != BUF_FLUSH)
		buf[m++] = o;
	return (1);
}

/**
 * _putfd writes character o to fd
 * 1 is returned when it is success
 */
int _putfd(char o, int fd)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (o == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(fd, buf, m);
		m = 0;
	}
	if (o != BUF_FLUSH)
		buf[m++] = o;
	return (1);
}

/**
 * _putsfd -input string is printed
 *the number of chars put is returned
 */
int _putsfd(char *str, int fd)
{
	int m = 0;

	if (!str)
		return (0);
	while (*str)
	{
		m += _putfd(*str++, fd);
	}
	return (m);
}

