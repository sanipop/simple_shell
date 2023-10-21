#include "shell.h"

/**
 * myget_environ - Make a copy of the built in enviroment
 * @info: the parameter that carrie the information of the shell.
 * Return: does not have a failure status
 */
char **myget_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = mylist_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _myunsetenv - Clear a content of the enviroment
 * @info: Information that carries the information of the shell .
 *  Return: with success 1 and failure 0
 * @var: the information passed in the shell
 */
int _myunsetenv(info_t *info, char *var)
{
	list_t *nex = info->env;
	size_t q = 0;
	char *r;

	if (!nex || !var)
		return (0);

	while (nex)
	{
		r = st_with(nex->str, var);
		if (r && *r == '=')
		{
			info->env_changed = mydelete_node_at_index(&(info->env), q);
			q = 0;
			nex = info->env;
			continue;
		}
		nex = nex->next;
		q++;
	}
	return (info->env_changed);
}

/**
 * _mysetenv - Manupulate the enviroment variable
 * @info: The information passed to the shell.
 * @var: the enviromental argument for the function
 * @value: the enviroment value or variable passed
 *  Return: No failure check for function
 */
int _mysetenv(info_t *info, char *var, char *value)
{
	char *hist = NULL;
	list_t *nex;
	char *d;

	if (!var || !value)
		return (0);

	hist = malloc(_stringlength(var) + _stringlength(value) + 2);
	if (!hist)
		return (1);
	_stringcopy(hist, var);
	_stringcat(hist, "=");
	_stringcat(hist, value);
	nex = info->env;
	while (nex)
	{
		d = st_with(nex->str, var);
		if (d && *d == '=')
		{
			free(nex->str);
			nex->str = hist;
			info->env_changed = 1;
			return (0);
		}
		nex = nex->next;
	}
	myadd_node_end(&(info->env), hist, 0);
	free(hist);
	info->env_changed = 1;
	return (0);
}
