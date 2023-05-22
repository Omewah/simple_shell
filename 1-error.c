#include "shell.h"

/**
 * _atoierr_pfunc - prints error if convert string to integer function fails
 * @stingIN: the string input to be atoi'd
 * Return: if string has no numbers 0, if error -1, else atoi of string
 */
int _atoierr_pfunc(char *stingIN)
{
	int a = 0;
	unsigned long int display = 0;

	if (*stingIN == '+')
		stingIN++;
	for (a = 0;  stingIN[a] != '\0'; a++)
	{
		if (stingIN[a] >= '0' && stingIN[a] <= '9')
		{
			display *= 10;
			display += (stingIN[a] - '0');
			if (display > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (display);
}

/**
 * _prterror_pfunc - prints a message for function errors
 * @intel: the structure containing arguments
 * @errstr: the error string
 * Return: the error string
 */
void _prterror_pfunc(intel_t *intel, char *errstr)
{
	_errputs_pfunc(intel->MYfilename);
	_errputs_pfunc(": ");
	ddprint_pfunc(intel->linecounterIN, STDERR_FILENO);
	_errputs_pfunc(": ");
	_errputs_pfunc(intel->strargvIN[0]);
	_errputs_pfunc(": ");
	_errputs_pfunc(errstr);
}

/**
 * ddprint_pfunc - function that prints a decimal digit
 * @nnum: the nth number input
 * @filedes: the file descriptor
 * Return: the decimal digit to print
 */
int ddprint_pfunc(int nnum, int filedes)
{
	int (*__ddchar)(char) = _putchar_pfunc;
	int a;
	int cont = 0;
	unsigned int _cbs_, curr;

	if (filedes == STDERR_FILENO)
		__ddchar = _errputchar_pfunc;
	if (nnum < 0)
	{
		_cbs_ = -nnum;
		__ddchar('-');
		cont++;
	}
	else
		_cbs_ = nnum;
	curr = _cbs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_cbs_ / a)
		{
			__ddchar('0' + curr / a);
			cont++;
		}
		curr %= a;
	}
	__ddchar('0' + curr);
	cont++;

	return (cont);
}

/**
 * ddconvert_pfunc - a converter function for decimal digits
 * @nnum: the decimal digit to be converted
 * @nbase: the nth base to convert to
 * @argf: the function argument flags
 * Return: the converted string of @nnum
 */
char *ddconvert_pfunc(long int nnum, int nbase, int argf)
{
	static char *list;
	static char buffer[50];
	char sin = 0;
	char *ptr;
	unsigned long a = nnum;

	if (!(argf & CONVERT_UNSIGNED) && nnum < 0)
	{
		a = -nnum;
		sin = '-';

	}
	list = argf & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = list[a % nbase];
		a /= nbase;
	} while (a != 0);

	if (sin)
		*--ptr = sin;
	return (ptr);
}

/**
 * hashdel_pfunc - changes the comment symbol '#' to '\0'
 * @buffer: the string buffer address
 * Return: 0 (Success)
 */
void hashdel_pfunc(char *buffer)
{
	int hd;

	for (hd = 0; buffer[hd] != '\0'; hd++)
		if (buffer[hd] == '#' && (!hd || buffer[hd - 1] == ' '))
		{
			buffer[hd] = '\0';
			break;
		}
}
