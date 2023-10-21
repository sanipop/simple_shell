#include "shell.h"

/**
 * _stringlength - a function for calculating the length of a string
 * @s: the string to calculate its length
 *
 * Return: the size of teh input function
 */
int _stringlength(char *s)
{
	int x = 0;

	if (!s)
		return (0);

	while (*s++)
		x++;
	return (x);
}

/**
 * _stringcmp - compare the charracter of a string indedx by index.
 * @s1: one of the characters to be compared
 * @s2: the other of the character to be compared
 *
 * Return: it subttract string one from the other
 */
int _stringcmp(char *s1, char *s2)
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
 * st_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *st_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _stringcat - joins two different strings together
 * @dest: the location to output the the source
 * @src: the string to be copied
 *
 * Return: pointer to destination buffer
 */
char *_stringcat(char *dest, char *src)
{
	char *outp = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (outp);
}
