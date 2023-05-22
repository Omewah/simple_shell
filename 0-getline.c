#include "shell.h"

/**
 * sigintH_pfunc - continues shell after ctrl+C input
 * @signalnum: the shell signal
 * Return: void
 */
void sigintH_pfunc(__attribute__((unused))int signalnum)
{
	_puts_pfunc("\n");
	_puts_pfunc("CJ$ ");
	_putchar_pfunc(BUF_FLUSH);
}

/**
 * chain_buf_pfunc - the buffer containing chained commands
 * @intel: struct containing argument
 * @b: the buffer address of the chained command
 * @lgthb: the pointer to the length of the buffer
 * Return: the byte of chained command to be read
 */
ssize_t chain_buf_pfunc(intel_t *intel, char **b, size_t *lgthb)
{
	ssize_t i = 0;
	size_t chcom = 0;

	if (!*lgthb)
	{
		free(*b);
		*b = NULL;
		signal(SIGINT, sigintH_pfunc);
#if USE_GETLINE
		i = getline(b, &chcom, stdin);
#else
		i = _lineIN_pfunc(intel, b, &chcom);
#endif
		if (i > 0)
		{
			if ((*b)[i - 1] == '\n')
			{
				(*b)[i - 1] = '\0';
				i--;
			}
			intel->MYlinecount_flagIN = 1;
			hashdel_pfunc(*b);
			_histlist_pfunc(intel, *b, intel->MYhistory_counter++);
			{
				*lgthb = i;
				intel->MYcmd_buffer = b;
			}
		}
	}
	return (i);
}

/**
 * _getIN_pfunc - only gets a command line input
 * @intel: struct containing argument
 * Return: bytes of the command to read at input
 */
ssize_t _getIN_pfunc(intel_t *intel)
{
	static char *b;
	static size_t a, z;
	static size_t lgthb;
	ssize_t i = 0;
	char **bptr = &(intel->strargIN), *ptr;

	_putchar_pfunc(BUF_FLUSH);
	i = chain_buf_pfunc(intel, &b, &lgthb);
	if (i == -1) /* EOF */
		return (-1);
	if (lgthb)
	{
		z = a;
		ptr = b + a;

		extchain_pfunc(intel, b, &z, a, lgthb);
		while (z < lgthb)
		{
			if (defchain_pfunc(intel, b, &z))
				break;
			z++;
		}

		a = z + 1;
		if (a >= lgthb)
		{
			a = lgthb = 0;
			intel->MYcmd_buffer_types = CMD_NORM;
		}

		*bptr = ptr;
		return (_lenstrn_pfunc(ptr));
	}

	*bptr = b;
	return (i);
}

/**
 * scan_pfunc - scans and interpret/read a buffer input
 * @intel: struct containing argument
 * @bufferIN: the buffer to interpret/read
 * @sz: size of buffer to interpret/read
 * Return: the buffer read successfully
 */
ssize_t scan_pfunc(intel_t *intel, char *bufferIN, size_t *sz)
{
	ssize_t r_buf = 0;

	if (*sz)
		return (0);
	r_buf = read(intel->MYreadfiledes, bufferIN, READ_BUF_SIZE);
	if (r_buf >= 0)
		*sz = r_buf;
	return (r_buf);
}

/**
 * _lineIN_pfunc - gets a command line input with the next line
 * @intel: struct containing argument
 * @bptr: the buffer pointer address to the next line input
 * @lgthb: the pointer to the length of buffer
 * Return: length of new line
 */
int _lineIN_pfunc(intel_t *intel, char **bptr, size_t *lgthb)
{
	static char bufferIN[READ_BUF_SIZE];
	static size_t a, lh;
	size_t b;
	ssize_t i = 0, n = 0;
	char *ptr = NULL;
	char *p_next = NULL, *t;

	ptr = *bptr;
	if (ptr && lgthb)
		n = *lgthb;
	if (a == lh)
		a = lh = 0;

	i = scan_pfunc(intel, bufferIN, &lh);
	if (i == -1 || (i == 0 && lh == 0))
		return (-1);

	t = _findstrchar_pfunc(bufferIN + a, '\n');
	b = t ? 1 + (unsigned int)(t - bufferIN) : lh;
	p_next = _memredis_pfunc(ptr, n, n ? n + b : b + 1);
	if (!p_next)
		return (ptr ? free(ptr), -1 : -1);

	if (n)
		_concatstrn_pfunc(p_next, bufferIN + a, b - a);
	else
		_copystrn_pfunc(p_next, bufferIN + a, b - a + 1);

	n += b - a;
	a = b;
	ptr = p_next;

	if (lgthb)
		*lgthb = n;
	*bptr = ptr;
	return (n);
}
