#include "shell.h"

/**
 * myadd_node - Append element a the begining of a list
 * @head: Location to the first element in the structure
 * @str: the variable for storing the string
 * @num: thecount that marks the history
 *
 * Return: the new size of the node
 */
list_t *myadd_node(list_t **head, const char *str, int num)
{
	list_t *first_loc;

	if (!head)
		return (NULL);
	first_loc = malloc(sizeof(list_t));
	if (!first_loc)
		return (NULL);
	_memoryset((void *)first_loc, 0, sizeof(list_t));
	first_loc->num = num;
	if (str)
	{
		first_loc->str = _stringdupper(str);
		if (!first_loc->str)
		{
			free(first_loc);
			return (NULL);
		}
	}
	first_loc->next = *head;
	*head = first_loc;
	return (first_loc);
}

/**
 * myadd_node_end - Append element to the tail of  a list
 * @head: The begining position of the list
 * @str: the variables of the structure
 * @num: Location counter of the information
 *
 * Return: count of the structure
 */
list_t *myadd_node_end(list_t **head, const char *str, int num)
{
	list_t *n_node, *nex;

	if (!head)
		return (NULL);

	nex = *head;
	n_node = malloc(sizeof(list_t));
	if (!n_node)
		return (NULL);
	_memoryset((void *)n_node, 0, sizeof(list_t));
	n_node->num = num;
	if (str)
	{
		n_node->str = _stringdupper(str);
		if (!n_node->str)
		{
			free(n_node);
			return (NULL);
		}
	}
	if (nex)
	{
		while (nex->next)
			nex = nex->next;
		nex->next = n_node;
	}
	else
		*head = n_node;
	return (n_node);
}

/**
 * myprint_list_str - output the string in the structure
 * @h: the index at the beginning of the list
 *
 * Return: total count of the structure
 */
size_t myprint_list_str(const list_t *h)
{
	size_t b = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		b++;
	}
	return (b);
}

/**
 * mydelete_node_at_index - remove a variable at a specific position
 * @head: the beginning location or position of the node
 * @index: the location of the element to be removed
 *
 * Return: binary status of the structure
 */
int mydelete_node_at_index(list_t **head, unsigned int index)
{
	list_t *nex, *p_node;
	unsigned int c = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nex = *head;
		*head = (*head)->next;
		free(nex->str);
		free(nex);
		return (1);
	}
	nex = *head;
	while (nex)
	{
		if (c == index)
		{
			p_node->next = nex->next;
			free(nex->str);
			free(nex);
			return (1);
		}
		c++;
		p_node = nex;
		nex = nex->next;
	}
	return (0);
}

/**
 * free_list - Release all the memory associated to the list
 * @head_ptr: The beginning of the list
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *nex, *n_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	nex = head;
	while (nex)
	{
		n_node = nex->next;
		free(nex->str);
		free(nex);
		nex = n_node;
	}
	*head_ptr = NULL;
}
