#include "shell.h"

/**
 * myget_history_file - it checks the previous commands infp
 * @info: information passed through the shell
 *
 * Return: the information on previous shell
 */

char *myget_history_file(info_t *info)
{
	char *hist, *loc;
	int hist_length;

	loc = _mygetenv(info, "HOME=");
	hist_length = _stringlength(loc) + _stringlength(HIST_FILE) + 2;
	if (!loc)
		return (NULL);
	hist = malloc(sizeof(char) * hist_length);
	if (!hist)
		return (NULL);
	hist[0] = 0;
	_stringcopy(hist, loc);
	_stringcat(hist, "/");
	_stringcat(hist, HIST_FILE);
	return (hist);
}

/**
 * mywrite_history - Add or build the history file
 * @info: the information passed to the shell
 *
 * Return: Binary status of the operation
 */
int mywrite_history(info_t *info)
{
	ssize_t filedescriptor;
	char *fname = myget_history_file(info);
	list_t *nex = NULL;

	if (!fname)
		return (-1);

	filedescriptor = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (filedescriptor == -1)
		return (-1);
	for (nex = info->history; nex; nex = nex->next)
	{
		_shellputsfd(nex->str, filedescriptor);
		_shellputfd('\n', filedescriptor);
	}
	_shellputfd(BUF_FLUSH, filedescriptor);
	close(filedescriptor);
	return (1);
}

/**
 * myread_history - open the file of the precious records
 * @info: Records passed to the shell
 *
 * Return: 0 on failure and file length on success
 */
int myread_history(info_t *info)
{
	int k, last = 0, lcount = 0;
	ssize_t filedescriptor, readlen, fsize = 0;
	struct stat st;
	char *hist = NULL, *fname = myget_history_file(info);

	if (!fname)
		return (0);

	filedescriptor = open(fname, O_RDONLY);
	free(fname);
	if (filedescriptor == -1)
		return (0);
	if (!fstat(filedescriptor, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	hist = malloc(sizeof(char) * (fsize + 1));
	if (!hist)
		return (0);
	readlen = read(filedescriptor, hist, fsize);
	hist[fsize] = 0;
	if (readlen <= 0)
		return (free(hist), 0);
	close(filedescriptor);
	for (k = 0; k < fsize; k++)
		if (hist[k] == '\n')
		{
			hist[k] = 0;
			mybuild_history_list(info, hist + last, lcount++);
			last = k + 1;
		}
	if (last != k)
		mybuild_history_list(info, hist + last, lcount++);
	free(hist);
	info->histcount = lcount;
	while (info->histcount-- >= HIST_MAX)
		mydelete_node_at_index(&(info->history), 0);
	myrenumber_history(info);
	return (info->histcount);
}

/**
 * mybuild_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int mybuild_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nex = NULL;

	if (info->history)
		nex = info->history;
	myadd_node_end(&nex, buf, linecount);

	if (!info->history)
		info->history = nex;
	return (0);
}

/**
 * myrenumber_history - Resort the history
 * @info: information passed to the shell
 *
 * Return: Resorted history number
 */
int myrenumber_history(info_t *info)
{
	list_t *nex = info->history;
	int j = 0;

	while (nex)
	{
		nex->num = j++;
		nex = nex->next;
	}
	return (info->histcount = j);
}
