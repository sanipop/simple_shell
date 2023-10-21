#include "shell.h"

/**
 * _amyexit - dunction to terminate the shell
 * @info: The informaiton passed to the shell and inheritance.
 * Return: shows the exit status of the shell.
 */
int _amyexit(info_t *info)
{
	int term;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		term = _myerratoi(info->argv[1]);
		if (term == -1)
		{
			info->status = 2;
			print_myerror(info, "Illegal number: ");
			_shellputs(info->argv[1]);
			_shelleputchar('\n');
			return (1);
		}
		info->err_num = _myerratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _amycd - the function used in the reallocating the current working dir
 * @info: The information passd through the various process in  the shell.
 * Return: it does not have a status check and always return 0
 */
int _amycd(info_t *info)
{
	char *cmd, *addr, histor[1024];
	int chdir_ret;

	cmd = getcwd(histor, 1024);
	if (!cmd)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		addr = _mygetenv(info, "HOME=");
		if (!addr)
			chdir_ret = /* TODO: what should this be? */
				chdir((addr = _mygetenv(info, "PWD=")) ? addr : "/");
		else
			chdir_ret = chdir(addr);
	}
	else if (_stringcmp(info->argv[1], "-") == 0)
	{
		if (!_mygetenv(info, "OLDPWD="))
		{
			_puts(cmd);
			_putchar('\n');
			return (1);
		}
		_puts(_mygetenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((addr = _mygetenv(info, "OLDPWD=")) ? addr : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_myerror(info, "can't cd to ");
		_shellputs(info->argv[1]), _shelleputchar('\n');
	}
	else
	{
		_mysetenv(info, "OLDPWD", _mygetenv(info, "PWD="));
		_mysetenv(info, "PWD", getcwd(histor, 1024));
	}
	return (0);
}

/**
 * _amyhelp - provide the information about the current working directory
 * @info: The information used to provide additional details to the shell.
 * Return: Do not check the status, return 0
 */
int _amyhelp(info_t *info)
{
	char **see;

	see = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*see); /* temp att_unused workaround */
	return (0);
}
