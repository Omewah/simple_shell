#include "shell.h"

/**
 **_copystrn_pfunc - copies a string to the nth number
 *@strdes: the result destination of the copied string
 *@strsrc: the source string to copy
 *@nth: the nth value of strings to copy
 *Return: the copied string
 */
char *_copystrn_pfunc(char *strdes, char *strsrc, int nth)
{
	int a;
	int b;
	char *str = strdes;

	a = 0;
	while (strsrc[a] != '\0' && a < nth - 1)
	{
		strdes[a] = strsrc[a];
		a++;
	}
	if (a < nth)
	{
		b = a;
		while (b < nth)
		{
			strdes[b] = '\0';
			b++;
		}
	}
	return (str);
}

/**
 **_concatstrn_pfunc - concatenates two strings to the nth byte
 *@strdes: the result destination of string concatenation
 *@strsrc: the source string to concatenate
 *@nth: the nth value of bytes to be used
 *Return: concatenated string pointer
 */
char *_concatstrn_pfunc(char *strdes, char *strsrc, int nth)
{
	int a;
	int b;
	char *str = strdes;

	a = 0;
	b = 0;
	while (strdes[a] != '\0')
		a++;
	while (strsrc[b] != '\0' && b < nth)
	{
		strdes[a] = strsrc[b];
		a++;
		b++;
	}
	if (b < nth)
		strdes[a] = '\0';
	return (str);
}

/**
 **_findstrchar_pfunc - finds the character in a string
 *@stringIN: the string to be searched in
 *@ch: the character to find in @stringIN
 *Return: the pointer to the character found
 */
char *_findstrchar_pfunc(char *stringIN, char ch)
{
	do {
		if (*stringIN == ch)
			return (stringIN);
	} while (*stringIN++ != '\0');

	return (NULL);
}
