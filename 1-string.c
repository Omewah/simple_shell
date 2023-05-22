#include "shell.h"

/**
 * _copystr_pfunc - a function that copies a string
 * @strdest: the copied string destination
 * @strsrc: the source string to be copied
 * Return: a pointer to the copied string
 */
char *_copystr_pfunc(char *strdest, char *strsrc)
{
	int a = 0;

	if (strdest == strsrc || strsrc == 0)
		return (strdest);
	while (strsrc[a])
	{
		strdest[a] = strsrc[a];
		a++;
	}
	strdest[a] = 0;
	return (strdest);
}

/**
 * _doublestr_pfunc - creates an identical copy of a string
 * @stringIN: the string to be replecated
 * Return: the replecated string pointer
 */
char *_doublestr_pfunc(const char *stringIN)
{
	int lgofstr = 0;
	char *repstr;

	if (stringIN == NULL)
		return (NULL);
	while (*stringIN++)
		lgofstr++;
	repstr = malloc(sizeof(char) * (lgofstr + 1));
	if (!repstr)
		return (NULL);
	for (lgofstr++; lgofstr--;)
		repstr[lgofstr] = *--stringIN;
	return (repstr);
}

/**
 * _puts_pfunc - a function that prints a string input
 * @stringIN: the string input to print
 * Return: Void
 */
void _puts_pfunc(char *stringIN)
{
	int a = 0;

	if (!stringIN)
		return;
	while (stringIN[a] != '\0')
	{
		_putchar_pfunc(stringIN[a]);
		a++;
	}
}

/**
 * _putchar_pfunc - writes the character to STDOUT
 * @b: The character to write
 * Return: 1 (Success), Else -1
 */
int _putchar_pfunc(char b)
{
	static int a;
	static char buff_size[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(STDOUT_FILENO, buff_size, a);
		a = 0;
	}
	if (b != BUF_FLUSH)
		buff_size[a++] = b;
	return (1);
}
