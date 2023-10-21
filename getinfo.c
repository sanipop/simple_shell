#include "shell.h"

/**
 * myclear_info - A function tha restart the parameter
 * @info: the information passed to the shell
 */
void myclear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_myinfo - assign a value to through function
 * @info: the information passed through the shell
 * @av: the command line argument
 */
void set_myinfo(info_t *info, char **av)
{
	int x = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = stringtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _stringdupper(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (x = 0; info->argv && info->argv[x]; x++)
			;
		info->argc = x;

		replace_myalias(info);
		replace_myvars(info);
	}
}

/**
 * free_myinfo - free the structure fields
 * @info: the information passed through the shell
 * @all: a specifier of all variable
 */
void free_myinfo(info_t *info, int all)
{
	forcefree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		forcefree(info->environ);
			info->environ = NULL;
		bytefree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
