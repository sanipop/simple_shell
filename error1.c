#include "shell.h"

/**
 * _myerratoi - A function that transform a string to number
 * @s: the input to be converted
 * Return: it returns 0 if there is no input received, and -1 with error
 */
int _myerratoi(char *s)
{
	int x = 0;
	unsigned long int answer = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (x = 0;  s[x] != '\0'; x++)
	{
		if (s[x] >= '0' && s[x] <= '9')
		{
			answer *= 10;
			answer += (s[x] - '0');
			if (answer > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (answer);
}

/**
 * print_myerror - function to display an error message
 * @info: the information passed through the shell
 * @estr: the nature of the type of error passed
 * Return: return 0, number converted or -1 with error
 */
void print_myerror(info_t *info, char *estr)
{
	_shellputs(info->fname);
	_shellputs(": ");
	print_myd(info->line_count, STDERR_FILENO);
	_shellputs(": ");
	_shellputs(info->argv[0]);
	_shellputs(": ");
	_shellputs(estr);
}

/**
 * print_myd - a function for printing number of the type int
 * @input: the number to be convert
 * @fd: the name of the file to add string
 *
 * Return: the count of the number written
 */
int print_myd(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int g, numb = 0;
	unsigned int _abs_, initia;

	if (fd == STDERR_FILENO)
		__putchar = _shelleputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		numb++;
	}
	else
		_abs_ = input;
	initia = _abs_;
	for (g = 1000000000; g > 1; g /= 10)
	{
		if (_abs_ / g)
		{
			__putchar('0' + initia / g);
			numb++;
		}
		initia %= g;
	}
	__putchar('0' + initia);
	numb++;

	return (numb);
}

/**
 * convert_mynumber - function to convert various data type
 * @num: the numeral to be converted
 * @base: the index of the number
 * @flags: the option passed to the function
 *
 * Return: string
 */
char *convert_mynumber(long int num, int base, int flags)
{
	static char *input;
	static char storage[50];
	char opp = 0;
	char *pointer;
	unsigned long l = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		l = -num;
		opp = '-';

	}
	input = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &storage[49];
	*pointer = '\0';

	do	{
		*--pointer = input[l % base];
		l /= base;
	} while (l != 0);

	if (opp)
		*--pointer = opp;
	return (pointer);
}

/**
 * remove_mycomments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_mycomments(char *buf)
{
	int x;

	for (x = 0; buf[x] != '\0'; x++)
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
}
