#include "shell.h"

/**
 * _memoryset - rewrite the memory content of byte
 * @s: a pointer to the begining of a memory block
 * @b: the memory byte to rewrite
 * @n: the amount of bytes to be filled
 * Return: (s) an adress to the locationof the memory
 */
char *_memoryset(char *s, char b, unsigned int n)
{
	unsigned int t;

	for (t = 0; t < n; t++)
		s[t] = b;
	return (s);
}

/**
 * forcefree - frees a string of strings
 * @pp: string of strings
 */
void forcefree(char **pp)
{
	char **g = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(g);
}

/**
 * _myrealloc - replasce the content of a memory
 * @ptr: index of the previous memory
 * @old_size: the memory capacity of the last block
 * @new_size: the memory capacity of the new block
 *
 * Return: return pointer to the previous position.
 */
void *_myrealloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *u;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	u = malloc(new_size);
	if (!u)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		u[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (u);
}
