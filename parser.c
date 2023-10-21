#include "shell.h"

/**
 * is_inputcmd - it check if a command is an executable
 * @info: the information passed to the shell
 * @path: the directory of the executable
 *
 * Return: binary representation of the success
 */
int is_inputcmd(info_t *info, char *path)
{
	struct stat input;

	(void)info;
	if (!path || stat(path, &input))
		return (0);

	if (input.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupp_chars - a function for making a function of a character
 * @pathstr: the string that ids for the path
 * @start: the beginning position of the new string
 * @stop: the end location of the new string
 *
 * Return: pointer to the newly formed string
 */
char *dupp_chars(char *pathstr, int start, int stop)
{
	static char arr[1024];
	int c = 0, e = 0;

	for (e = 0, c = start; c < stop; c++)
		if (pathstr[c] != ':')
			arr[e++] = pathstr[c];
	arr[e] = 0;
	return (arr);
}

/**
 * find_shellpath - a function for finding  directory in path
 * @info: the information to be passed to the shell
 * @cmd: the name of directory to find
 * @pathstr: the descriptor for path str
 * Return: the path of the directory or else return null
 */
char *find_shellpath(info_t *info, char *pathstr, char *cmd)
{
	int x = 0, locatio = 0;
	char *direc;

	if (!pathstr)
		return (NULL);
	if ((_stringlength(cmd) > 2) && st_with(cmd, "./"))
	{
		if (is_inputcmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[x] || pathstr[x] == ':')
		{
			direc = dupp_chars(pathstr, locatio, x);
			if (!*direc)
				_stringcat(direc, cmd);
			else
			{
				_stringcat(direc, "/");
				_stringcat(direc, cmd);
			}
			if (is_inputcmd(info, direc))
				return (direc);
			if (!pathstr[x])
				break;
			locatio = x;
		}
		x++;
	}
	return (NULL);
}
