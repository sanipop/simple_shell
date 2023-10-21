#include "shell.h"

/**
 * mylist_len - function that fint the lenght of  a structure list
 * @h: the index to the first structure
 *
 * Return: output the length of the structure
 */
size_t mylist_len(const list_t *h)
{
	size_t o = 0;

	while (h)
	{
		h = h->next;
		o++;
	}
	return (o);
}




/**
 * mylist_to_strings - Outline the string in the double pointer
 * @head: the first element in the structure
 *
 * Return: the list of strings
 */
char **mylist_to_strings(list_t *head)
{
	list_t *node = head;
	size_t f = mylist_len(head), j;
	char **dps;
	char *str;

	if (!head || !f)
		return (NULL);
	dps = malloc(sizeof(char *) * (f + 1));
	if (!dps)
		return (NULL);
	for (f = 0; node; node = node->next, f++)
	{
		str = malloc(_stringlength(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < f; j++)
				free(dps[j]);
			free(dps);
			return (NULL);
		}

		str = _stringcopy(str, node->str);
		dps[f] = str;
	}
	dps[f] = NULL;
	return (dps);
}


/**
 * myprint_list - Outputs the contents of the information
 * @h: The first element of the list
 *
 * Return: lengths of the arrays
 */
size_t myprint_list(const list_t *h)
{
	size_t ee = 0;

	while (h)
	{
		_puts(convert_mynumber(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		ee++;
	}
	return (ee);
}



/**
 * mynode_starts_with - Function to list node that starts with the charcher
 * @node: A node that points to the heads or outputs them
 * @prefix: the input to find in the strings
 * @c: The character that proceeds the node
 *
 * Return: Status of match success or failure
 */
list_t *mynode_starts_with(list_t *node, char *prefix, char c)
{
	char *ant = NULL;

	while (node)
	{
		ant = st_with(node->str, prefix);
		if (ant && ((c == -1) || (*ant == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}



/**
 * myget_node_index - function to determine the index of the node
 * @head: pointer of the start of the node
 * @node: the current node
 *
 * Return: Return the index of the current node and -1 in failure
 */
ssize_t myget_node_index(list_t *head, list_t *node)
{
	size_t ey = 0;

	while (head)
	{
		if (head == node)
			return (ey);
		head = head->next;
		ey++;
	}
	return (-1);
}
