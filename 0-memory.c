#include "shell.h"

/**
 * _pmemfree_pfunc - frees the memory address of a pointer
 * @pmem: the pointer's memory address to free
 * Return: 1 (Success), Else 0.
 */
int _pmemfree_pfunc(void **pmem)
{
	if (pmem && *pmem)
	{
		free(*pmem);
		*pmem = NULL;
		return (1);
	}
	return (0);
}
