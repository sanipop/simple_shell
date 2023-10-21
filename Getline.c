#include "shell.h"

/**
 * input_mybuf -a function that works as a buffer
 * @info: the information passed to the shell
 * @buf: a pointer to the buffer
 * @len: a pointr to the size of the buffer
 *
 * Return: the size of the data read
 */
ssize_t input_mybuf(info_t *info, char **buf, size_t *len)
{
	ssize_t a = 0;
	size_t breath = 0;

	if (!*len) /* a check for the length */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, mysigintHandler);
#if USE_GETLINE
		a = getline(buf, &breath, stdin);
#else
		a = _mygetline(info, buf, &breath);
#endif
		if (a > 0)
		{
			if ((*buf)[a - 1] == '\n')
			{
				(*buf)[a - 1] = '\0'; /* remove trailing newline */
				a--;
			}
			info->linecount_flag = 1;
			remove_mycomments(*buf);
			mybuild_history_list(info, *buf, info->histcount++);
			/* a functio to chain the buffer*/
			{
				*len = a;
				info->cmd_buf = buf;
			}
		}
	}
	return (a);
}

/**
 * myget_input - the function rewmoves the end of line and copies the line
 * @info: the information passed to the shell
 *
 * Return: the sinzed of byte used
 */
ssize_t myget_input(info_t *info)
{
	static char *hist; /* for ';' concatinating command */
	static size_t d, f, size;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_mybuf(info, &hist, &size);
	if (r == -1) /* a function to mark end of file */
		return (-1);
	if (size) /* inspect for undone operation */
	{
		f = d; /*create a temp new variable  */
		p = hist + d; /* the value passed from the function*/

		check_mychain(info, hist, &f, d, size);
		while (f < size) /* transverse throung the string */
		{
			if (is_mychain(info, hist, &f))
				break;
			f++;
		}

		d = f + 1; /* to exit the bound ';'' */
		if (d >= size) /* check if their are still remaing char ? */
		{
			d = size = 0; /* reset the tracking */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* to the start of the loop */
		return (_stringlength(p)); /* to the determine the size of command */
	}

	*buf_p = hist; /* a call back to the array */
	return (r); /* it output the value to the caller */
}

/**
 * read_mybuf - function for reading the character stored in the array
 * @info: the information passed on the sheell
 * @buf:the array for storing the characters
 * @i:the size of the character
 *
 * Return: r
 */
ssize_t read_mybuf(info_t *info, char *buf, size_t *i)
{
	ssize_t x = 0;

	if (*i)
		return (0);
	x = read(info->readfd, buf, READ_BUF_SIZE);
	if (x >= 0)
		*i = x;
	return (x);
}

/**
 * _mygetline - a function for rerading characters inthe stdin
 * @info: the name of the information passed to the shell
 * @ptr: the location of the first value to be copied by the pointer
 * @length: the size of space kept for the wriite
 *
 * Return: the size of the line read
 */
int _mygetline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_mybuf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _stringchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _myrealloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_stringncat(new_p, buf + i, k - i);
	else
		_stringncopy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * mysigintHandler - the function prevent the EOF
 * @sig_num: the type of signal passes
 *
 * Return: doe not have a return
 */
void mysigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_shelleputchar(BUF_FLUSH);
}
