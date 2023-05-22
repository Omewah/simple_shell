#include "shell.h"

/**
 * _lenstrn_pfunc - prints the string length
 * @lg: the string length to be printed
 * Return: the length of the string
 */
int _lenstrn_pfunc(char *lg)
{
	int a = 0;

	if (!lg)
		return (0);

	while (*lg++)
		a++;
	return (a);
}

/**
 * _comparestr_pfunc - compares two strangs.
 * @sx: the first string to compare
 * @sy: the second string to compare to the first
 * Return: if @sx equal to @sy, 0
 */
int _comparestr_pfunc(char *sx, char *sy)
{
	while (*sx && *sy)
	{
		if (*sx != *sy)
			return (*sx - *sy);
		sx++;
		sy++;
	}
	if (*sx == *sy)
		return (0);
	else
		return (*sx < *sy ? -1 : 1);
}

/**
 * checkpoint_pfunc - a function that finds a point in a point pack
 * @packIN: string to to find the point in
 * @point: the point to be found
 * Return: address of next character
 */
char *checkpoint_pfunc(const char *packIN, const char *point)
{
	while (*point)
		if (*point++ != *packIN++)
			return (NULL);
	return ((char *)packIN);
}

/**
 * _concatstr_pfunc - a function that concatenates two buffer strings
 * @desbuff: the destination buffer string after concatenation
 * @srcbuff: the source buffer string to concatenate
 * Return: a pointer to @desbuff
 */
char *_concatstr_pfunc(char *desbuff, char *srcbuff)
{
	char *desptr = desbuff;

	while (*desbuff)
		desbuff++;
	while (*srcbuff)
		*desbuff++ = *srcbuff++;
	*desbuff = *srcbuff;
	return (desptr);
}
