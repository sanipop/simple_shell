#include "shell.h"
/**
* wem - Write an error message to a file descriptor.
*
* @filedescriptor: The file descriptor to write to.
* @prog_name: The program name.
* @filename: The name of the file that couldn't be opened.
*/
void wem(int filedescriptor, const char *prog_name, const char *filename)
{

	const char *error_msg = prog_name;

	char buf_flush, newline;

	write(filedescriptor, error_msg, strlen(error_msg));
	error_msg = ": 0: Can't open ";
	write(filedescriptor, error_msg, strlen(error_msg));
	error_msg = filename;
	write(filedescriptor, error_msg, strlen(error_msg));
	newline = '\n';

	write(filedescriptor, &newline, 1);
	buf_flush = BUF_FLUSH;
	write(filedescriptor, &buf_flush, 1);
}

/**
* main - entry point
* @ac: the command line argument count
* @av: the argument vector array
* Return: 0 on success, 1 on error
*/

int main(int ac, char **av)
{

	info_t info[] = { INFO_INIT };
	int filedescriptor = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (filedescriptor)
		: "r" (filedescriptor));

	if (ac == 2)
	{
		filedescriptor = open(av[1], O_RDONLY);
		if (filedescriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				wem(filedescriptor, av[0], av[1]);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = filedescriptor;
	}
	mypopulate_env_list(info);
	myread_history(info);
	h_shell(info, av);
	return (EXIT_SUCCESS);
}
