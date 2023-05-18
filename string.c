#include "shell.h"

/**
 * _strlen - come back to string length
 * @s: strlen to be checked
 * Return: strlen integer
 */
int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}

/**
 * _strcmp - compares two strings
 * @s1: initial string
 * @s2: preceding string
 * Return: if s1 < s2 (-), if s1 > s2 (+), if s1 == s2 (0)
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * starts_with - start checker
 * @haystack: string to be looked into
 * @needle: ministring for searching
 * Return: address or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - focuses two strings
 * @src: origin buffer
 * @dest: positional buffer
 * Return: pointer to buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
