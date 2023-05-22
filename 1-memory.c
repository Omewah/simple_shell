#include "shell.h"

/**
 **_set_constmem_pfunc - adds constant bytes to a memory set
 *@sp: the memory set pointer
 *@byte: the byte to be added to the memory set
 *@nnum: the nth number of bytes to assign to the memory set
 *Return: memory set pointer with constant bytes
 */
char *_set_constmem_pfunc(char *sp, char byte, unsigned int nnum)
{
	unsigned int a;

	for (a = 0; a < nnum; a++)
		sp[a] = byte;
	return (sp);
}

/**
 * _strfree_pfunc - frees a string memory set pointer
 * @ss: the set of strings to be freed
 */
void _strfree_pfunc(char **ss)
{
	char **p = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(p);
}

/**
 * _memredis_pfunc - redistrubutes a memory block
 * @pmb: pointer to memory block to redistrubute
 * @new: the new memory block size
 * @old: the old memory block size
 * Return: a pointer to @old.
 */
void *_memredis_pfunc(void *pmb, unsigned int old, unsigned int new)
{
	char *b;

	if (!pmb)
		return (malloc(new));
	if (!new)
		return (free(pmb), NULL);
	if (new == old)
		return (pmb);

	b = malloc(new);
	if (!b)
		return (NULL);

	old = old < new ? old : new;
	while (old--)
		b[old] = ((char *)pmb)[old];
	free(pmb);
	return (b);
}
