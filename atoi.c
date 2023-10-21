#include "shell.h"

/**
 * myinteract - function that check the interactive naturre of the shell
 * @info: parameter for passing information to tje shell
 *
 * Return: 1, 0 binary infomation status of the interaction
 */
int myinteract(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * myis_delim - Function to check the seprator of the shell
 * @c: the current chatacter being checked
 * @delim:the string of which to check for
 * Return: Binary status of the operation
 */
int myis_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _myisalpha - it check the input string if it is an alphabet
 * @c: the input passed to the shell
 * Return: binary status of the alphabet check
 */

int _myisalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _myatoi - function to convert the input string passed to integer
 * @s: the inputut string passed to the function
 * Return: return 0 for an empty string and the count otherwise
 */

int _myatoi(char *s)
{
	int x, opp = 1, select = 0, passed;
	unsigned int res = 0;

	for (x = 0; s[x] != '\0' && select != 2; x++)
	{
		if (s[x] == '-')
			opp *= -1;

		if (s[x] >= '0' && s[x] <= '9')
		{
			select = 1;
			res *= 10;
			res += (s[x] - '0');
		}
		else if (select == 1)
			select = 2;
	}

	if (opp == -1)
		passed = -res;
	else
		passed = res;

	return (passed);
}

