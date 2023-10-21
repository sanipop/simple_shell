#include "shell.h"

/**
 **_stringncopy - function fo creating a copy of a string
 *@dest: the string to be copied
 *@src: the string to be copied
 *@n: the count of number tobe counted
 *Return: the newely creatred string
 */
char *_stringncopy(char *dest, char *src, int n)
{
	int a, b;
	char *f = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (f);
}

/**
 **_stringncat - join the first string with the second
 *@dest: the first part of the string
 *@src: the end part of the string
 *@n: the memory allocated to the output
 *Return: output the completed string
 */
char *_stringncat(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (s);
}

/**
 **_stringchr - function to find a specific string
 *@s: the string to which to workon
 *@c: the string to be searvh for
 *Return: (s) the adress of the character to be found
 */
char *_stringchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
