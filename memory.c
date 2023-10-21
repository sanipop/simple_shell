#include "shell.h"

/**
 * bytefree - A function that change the index of a pointer to null
 * @ptr:  a pointer to the element to be freed
 *
 * Return: 1 if freed, otherwise 0.
 */
int bytefree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
