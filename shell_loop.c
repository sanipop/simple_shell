#include "shell.h"

/**
 * h_shell - the main function that execute the command
 * @info: the information passed to the shell
 * @av: the command line argument
 *
 * Return: 0 on success, 1 on error, or error code
 */
int h_shell(info_t *info, char **av)
{
	ssize_t y = 0;
	int input_cmd = 0;

	while (y != -1 && input_cmd != -2)
	{
		myclear_info(info);
		if (myinteract(info))
			_puts("$ ");
		_shelleputchar(BUF_FLUSH);
		y = myget_input(info);
		if (y != -1)
		{
			set_myinfo(info, av);
			input_cmd = find_bltin(info);
			if (input_cmd == -1)
				find_inputcmd(info);
		}
		else if (myinteract(info))
			_putchar('\n');
		free_myinfo(info, 0);
	}
	mywrite_history(info);
	free_myinfo(info, 1);
	if (!myinteract(info) && info->status)
		exit(info->status);
	if (input_cmd == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (input_cmd);
}

/**
 * find_bltin - function for collecting built in command
 * @info: the information passed to the shell
 *
 * Return:outputs from -1 to 2 depending on the exit status
 */
int find_bltin(info_t *info)
{
	int x, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _amyexit},
		{"env", _amyenv},
		{"help", _amyhelp},
		{"history", _amyhistory},
		{"setenv", _amysetenv},
		{"unsetenv", _amyunsetenv},
		{"cd", _amycd},
		{"alias", _amyalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_stringcmp(info->argv[0], builtintbl[x].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[x].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_inputcmd - a function for finding a specific command in the shell
 * @info: the information passed to the shell
 *
 * Return: does not return any status
 */
void find_inputcmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!myis_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_shellpath(info, _mygetenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_inputcmd(info);
	}
	else
	{
		if ((myinteract(info) || _mygetenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_inputcmd(info, info->argv[0]))
			fork_inputcmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_myerror(info, "not found\n");
		}
	}
}

/**
 * fork_inputcmd - the function that call the execve function
 * @info:the parameter that is used to passed information throughout the shell
 *
 * Return: does not have any return
 */
void fork_inputcmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, myget_environ(info)) == -1)
		{
			free_myinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_myerror(info, "Permission denied\n");
		}
	}
}
