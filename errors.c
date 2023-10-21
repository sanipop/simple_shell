#include "shell.h"

/**
* _shellputs - outputs a string to the standsrd display
* @str: the information that is to be outputted
*
* Return: Nothing
*/
void _shellputs(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_shelleputchar(str[x]);
		x++;
	}
}

/**
*_shelleputchar - a function to write to the standard display
* @c: a character to be send to the standard output
*
* Return: A sign value of the correspond to the success.
*/
int _shelleputchar(char c)
{
	static int x;

	static char arr[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, arr, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		arr[x++] = c;
	return (1);
}

/**
* _shellputfd - A function to write a character to a file
* @c: the character to write
* @fd: the file to be written to
*
* Return: returns 1 on success and does a complete errono check.
*/
int _shellputfd(char c, int fd)
{
	static int x;

	static char arr[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fd, arr, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		arr[x++] = c;
	return (1);
}

/**
* _shellputsfd - prints an input string
* @str: the array of character to send to standard output
* @fd: a file that the information is to be stored
*
* Return: the output is with the character written
*/
int _shellputsfd(char *str, int fd)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
	{
		x += _shellputfd(*str++, fd);
	}
	return (x);
}
