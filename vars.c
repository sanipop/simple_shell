#include "shell.h"

/**
 * is_mychain - sttus identifier of chain
 * @info: Parameter fo information manupulation in the shell
 * @buf: tempory storage for the command
 * @p: index location of the quee
 *
 * Return: 1 or 0 to indicate status chain
 */

int is_mychain(info_t *info, char *buf, size_t *p)
{
	size_t zee = *p;

	if (buf[zee] == '|' && buf[zee + 1] == '|')
	{
		buf[zee] = 0;
		zee++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[zee] == '&' && buf[zee + 1] == '&')
	{
		buf[zee] = 0;
		zee++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[zee] == ';') /* found end of this command */
	{
		buf[zee] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = zee;
	return (1);
}




/**
 * check_mychain - Functoin to check if function can be merged
 * @info: The structure to store information for shell
 * @buf: the charcter in the quee
 * @p: the current position of the quee
 * @i: Begin position of the quee
 * @len: Total size of the quee
 *
 * Return: Void
 */

void check_mychain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t gee = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			gee = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			gee = len;
		}
	}

	*p = gee;
}



/**
 * replace_myalias - add string to its card position
 * @info: the information stored fo the shell
 *
 * Return:Return 1 on success and 0 on Failure
 */
int replace_myalias(info_t *info)
{
	int kount;
	list_t *node;
	char *qee;

	for (kount = 0; kount < 10; kount++)
	{
		node = mynode_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		qee = _stringchr(node->str, '=');
		if (!qee)
			return (0);
		qee = _stringdupper(qee + 1);
		if (!qee)
			return (0);
		info->argv[0] = qee;
	}
	return (1);
}

/**
 * replace_myvars - Modify the input string
 * @info: the information passed to the shell
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_myvars(info_t *info)
{
	int aa = 0;
	list_t *node;

	for (aa = 0; info->argv[aa]; aa++)
	{
		if (info->argv[aa][0] != '$' || !info->argv[aa][1])
			continue;

		if (!_stringcmp(info->argv[aa], "$?"))
		{
			replace_mystring(&(info->argv[aa]),
					_stringdupper(convert_mynumber(info->status, 10, 0)));
			continue;
		}
		if (!_stringcmp(info->argv[aa], "$$"))
		{
			replace_mystring(&(info->argv[aa]),
					_stringdupper(convert_mynumber(getpid(), 10, 0)));
			continue;
		}
		node = mynode_starts_with(info->env, &info->argv[aa][1], '=');
		if (node)
		{
			replace_mystring(&(info->argv[aa]),
					_stringdupper(_stringchr(node->str, '=') + 1));
			continue;
		}
		replace_mystring(&info->argv[aa], _stringdupper(""));

	}
	return (0);
}


/**
 * replace_mystring - change fiirst string with the second
 * @old: pointer to a pointer to the first
 * @new: the current string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_mystring(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
