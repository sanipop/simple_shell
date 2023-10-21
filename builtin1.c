#include "shell.h"

/**
 * _amyhistory - shows the histroy and the number count.
 * @info: the information of the history passed to the shell.
 *  Return: no status report 0 is sent regardless
 */
int _amyhistory(info_t *info)
{
	myprint_list(info->history);
	return (0);
}

/**
 * unset_alias - unassign the alias in respect tio the alias information
 * @info: the information passed to the shell
 * @str: the variable information used by the alias
 *
 * Return: Binary status of the function
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _stringchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = mydelete_node_at_index(&(info->alias),
		myget_node_index(info->alias, mynode_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - assign various variable to the information
 * @info: the information that is passed through the shell
 * @str: the name the information is set as
 *
 * Return: binnary status of the operation
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _stringchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (myadd_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - output the name of the alias
 * @node: the information that is passed
 *
 * Return: Binary status of the operation
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _stringchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _amyalias - similar to the built in function of the shell
 * @info: the information passe through out the shell.
 *  Return: a uniary status report hence output 1
 */
int _amyalias(info_t *info)
{
	int d = 0;
	char *h = NULL;
	list_t *nex = NULL;

	if (info->argc == 1)
	{
		nex = info->alias;
		while (nex)
		{
			print_alias(nex);
			nex = nex->next;
		}
		return (0);
	}
	for (d = 1; info->argv[d]; d++)
	{
		h = _stringchr(info->argv[d], '=');
		if (h)
			set_alias(info, info->argv[d]);
		else
			print_alias(mynode_starts_with(info->alias, info->argv[d], '='));
	}

	return (0);
}
