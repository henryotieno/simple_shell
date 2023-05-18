#include "shell.h"

/**
 **_cpystrn – ensure the string is copied
 *@e: characters that are to be copied
 *concanated string is returned
 *@dest: string destination is displayed
 *@src: string of the source noted
 */
char *_cpystrn(char *dest, char *src, int e)
{
	int m, f;
	char *b = dest;

	m = 0;
	while (src[m] != '\0' && m < e - 1)
	{
		dest[m] = src[m];
		m++;
	}
	if (m < e)
	{
		f = m;
		while (f < e)
		{
			dest[f] = '\0';
			f++;
		}
	}
	return (b);
}

/**
 **_cattstrn – joins two strings together
 *@dest: string of the first
 *@src: the second string
 *@e: overall amount of bytes used
 *joined string is returned
 */
char *_cattstrn(char *dest, char *src, int e)
{
	int m, f;
	char *b = dest;

	m = 0;
	f = 0;
	while (dest[m] != '\0')
		m++;
	while (src[f] != '\0' && f < e)
	{
		dest[m] = src[f];
		m++;
		f++;
	}
	if (f < e)
		dest[m] = '\0';
	return (b);
}

/**
*@b: the parsed string
 *@o: searched character
 *a pointer is returned
 **_strchr string characters are located
 */
char *_strchr(char *b, char o)
{
	do {
		if (*b == o)
			return (b);
	} while (*b++ != '\0');

	return (NULL);
}

