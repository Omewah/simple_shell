#include "shell.h"

/**
 *_errputs_pfunc - puts an input string error
 * @s: string error to be put
 * Return: void
 */
void _errputs_pfunc(char *s)
{
	int a = 0;

	if (!s)
		return;
	while (s[a] != '\0')
	{
		_errputchar_pfunc(s[a]);
		a++;
	}
}

/**
 * _errputchar_pfunc - puts the character error of a string
 * @b: The character error to put
 * Return: 1 (Success), Else -1
 */
int _errputchar_pfunc(char b)
{
	static int a;
	static char buffer_size[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(STDERR_FILENO, buffer_size, a);
		a = 0;
	}
	if (b != BUF_FLUSH)
		buffer_size[a++] = b;
	return (1);
}

/**
 * _putfiledes_pfunc - puts the character error to given file descriptor
 * @b: The character error to put
 * @filedes: The file descriptor to put error to
 * Return: 1 (Success), Else -1
 */
int _putfiledes_pfunc(char b, int filedes)
{
	static int a;
	static char buffer_size[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(filedes, buffer_size, a);
		a = 0;
	}
	if (b != BUF_FLUSH)
		buffer_size[a++] = b;
	return (1);
}

/**
 *_putsfiledes_pfunc - returns an input string error
 * @s: the string error to be returned
 * @filedes: the file descriptor for the error to return
 * Return: the nth number of character error
 */
int _putsfiledes_pfunc(char *s, int filedes)
{
	int a = 0;

	if (!s)
		return (0);
	while (*s)
	{
		a += _putfiledes_pfunc(*s++, filedes);
	}
	return (a);
}
