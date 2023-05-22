#include "shell.h"

/**
 * _shellact_pfunc - checks if the shell is responsive
 * @intel: struct containing arguments
 * Return: 1 if shell is responsive, Else 0
 */

int _shellact_pfunc(intel_t *intel)
{
	return (isatty(STDIN_FILENO) && intel->MYreadfiledes <= 2);
}

/**
 * _defchar_pfunc - defines a character to be a delimiter
 * @chr: the character to be defined as a delimiter
 * @del: the pointer string to the delimiter
 * Return: 1 (Success), Else 0.
 */

int _defchar_pfunc(char chr, char *del)
{
	while (*del)
		if (*del++ == chr)
			return (1);
	return (0);
}

/**
 *_syllab_pfunc - defines if the input character is an alphabet
 *@sy: The character input to be defined
 *Return: 1 (Success), Else 0
 */

int _syllab_pfunc(int sy)
{
	if ((sy >= 'a' && sy <= 'z') || (sy >= 'A' && sy <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi_pfunc - a function that transforms a string to integer
 *@stringIN: the string input to be atoi'd
 *Return: if string has no number 0, Else the atoi of a string
 */

int _atoi_pfunc(char *stringIN)
{
	int a;
	int logo = 1, z = 0;
	int out;
	unsigned int display = 0;

	for (a = 0;  stringIN[a] != '\0' && z != 2; a++)
	{
		if (stringIN[a] == '-')
			logo *= -1;

		if (stringIN[a] >= '0' && stringIN[a] <= '9')
		{
			z = 1;
			display *= 10;
			display += (stringIN[a] - '0');
		}
		else if (z == 1)
			z = 2;
	}

	if (logo == -1)
		out = -display;
	else
		out = display;

	return (out);
}