#include "shell.h"

/**
 * _amyenv - Output the details of the enviroment
 * @info: the information passed to the shell.
 * Return: The status report is not based on success
 */
int _amyenv(info_t *info)
{
	myprint_list_str(info->env);
	return (0);
}

/**
 * _mygetenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_mygetenv(info_t *info, const char *name)
{
	list_t *nex = info->env;
	char *c;

	while (nex)
	{
		c = st_with(nex->str, name);
		if (c && *c)
			return (c);
		nex = nex->next;
	}
	return (NULL);
}

/**
 * _amysetenv - Modifier to the enviromental details of the shell program
 * @info: The details passed to the shell program.
 *  Return: it has no status report of the program
 */
int _amysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_shellputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_mysetenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _amyunsetenv - a modifier of the previous enviromental variabe it cut it out
 * @info: the information passed to the shell through the parameter.
 * Return: Does not have a status output it is always 0
 */
int _amyunsetenv(info_t *info)
{
	int k;

	if (info->argc == 1)
	{
		_shellputs("Too few arguements.\n");
		return (1);
	}
	for (k = 1; k <= info->argc; k++)
		_myunsetenv(info, info->argv[k]);

	return (0);
}

/**
 * mypopulate_env_list - it details to shell in the enviromental information
 * @info: it holds the information passed in the shell.
 * Return: it does not have status report, but always return 0
 */
int mypopulate_env_list(info_t *info)
{
	list_t *nex = NULL;
	size_t k;

	for (k = 0; environ[k]; k++)
		myadd_node_end(&nex, environ[k], 0);
	info->env = nex;
	return (0);
}
