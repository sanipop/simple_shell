#include "shell.h"

/**
 * _stringcopy - A function to copy a string
 * @dest: the location of the output copied
 * @src: the string to be copied
 *
 * Return: pointer to destination
 */
char *_stringcopy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}

/**
 * _stringdupper - a function for copying a string
 * @str: the string to be copied by the function
 * Return: return the adress of the memory
 */
char *_stringdupper(const char *str)
{
	int x = 0;
	char *output;

	if (str == NULL)
		return (NULL);
	while (*str++)
		x++;
	output = malloc(sizeof(char) * (x + 1));
	if (!output)
		return (NULL);
	for (x++; x--;)
		output[x] = *--str;
	return (output);
}

/**
 * _puts - a function to display character to the string
 * @str: the character to be outputted
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar - a function to display a character to std out
 * @c: the input to be sent to the output
 *
 * Return: 1is returned on sussess and -1 when the function fails
 */
int _putchar(char c)
{
	static int x;
	static char arr[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, arr, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		arr[x++] = c;
	return (1);
}
