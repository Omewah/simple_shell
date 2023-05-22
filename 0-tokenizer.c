#include "shell.h"

/**
 * **splitstr_pfunc - splits a string without repeat delimiters
 * @stringIN: the string input to be split
 * @del: the string variable delimiter
 * Return: NULL (failed), Else pointer to the string array
 */

char **splitstr_pfunc(char *stringIN, char *del)
{
	int a, b;
	int c, d;
	int num = 0;
	char **sp;

	if (stringIN == NULL || stringIN[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (a = 0; stringIN[a] != '\0'; a++)
		if (!_defchar_pfunc(stringIN[a], del) && (_defchar_pfunc(stringIN[a + 1], del) || !stringIN[a + 1]))
			num++;

	if (num == 0)
		return (NULL);
	sp = malloc((1 + num) * sizeof(char *));
	if (!sp)
		return (NULL);
	for (a = 0, b = 0; b < num; b++)
	{
		while (_defchar_pfunc(stringIN[a], del))
			a++;
		c = 0;
		while (!_defchar_pfunc(stringIN[a + c], del) && stringIN[a + c])
			c++;
		sp[b] = malloc((c + 1) * sizeof(char));
		if (!sp[b])
		{
			for (c = 0; c < b; c++)
				free(sp[c]);
			free(sp);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			sp[b][d] = stringIN[a++];
		sp[b][d] = 0;
	}
	sp[b] = NULL;
	return (sp);
}

/**
 * **splitstrn_pfunc - seperates a string using repeat delimiters
 * @stringIN: the string input to be split
 * @del: the string variable delimiter
 * Return: NULL (failed), Else pointer to the string array
 */
char **splitstrn_pfunc(char *stringIN, char del)
{
	int a, b;
	int c, d;
	int num = 0;
	char **sp;

	if (stringIN == NULL || stringIN[0] == 0)
		return (NULL);
	for (a = 0; stringIN[a] != '\0'; a++)
		if ((stringIN[a] != del && stringIN[a + 1] == del) ||
		    (stringIN[a] != del && !stringIN[a + 1]) || stringIN[a + 1] == del)
			num++;
	if (num == 0)
		return (NULL);
	sp = malloc((1 + num) * sizeof(char *));
	if (!sp)
		return (NULL);
	for (a = 0, b = 0; b < num; b++)
	{
		while (stringIN[a] == del && stringIN[a] != del)
			a++;
		c = 0;
		while (stringIN[a + c] != del && stringIN[a + c] && stringIN[a + c] != del)
			c++;
		sp[b] = malloc((c + 1) * sizeof(char));
		if (!sp[b])
		{
			for (c = 0; c < b; c++)
				free(sp[c]);
			free(sp);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			sp[b][d] = stringIN[a++];
		sp[b][d] = 0;
	}
	sp[b] = NULL;
	return (sp);
}
