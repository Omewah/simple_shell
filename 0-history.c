#include "shell.h"

/**
 * _hist_pfunc - function that returns the history file string
 * @intel: struct containing argument
 * Return: the string that holds the history file
 */

char *_hist_pfunc(intel_t *intel)
{
	char *hist, *z;

	z = getenvIN(intel, "HOME=");
	if (!z)
		return (NULL);
	hist = malloc(sizeof(char) * (_lenstrn_pfunc(z) + _lenstrn_pfunc(HIST_FILE) + 2));
	if (!hist)
		return (NULL);
	hist[0] = 0;
	_copystr_pfunc(hist, z);
	_concatstr_pfunc(hist, "/");
	_concatstr_pfunc(hist, HIST_FILE);
	return (hist);
}

/**
 * _histw_pfunc - initiates HIST and writes into the HIST_FILE
 * @intel: the struct containing argument
 * Return: 1 (success), Else -1
 */
int _histw_pfunc(intel_t *intel)
{
	ssize_t hist;
	char *HF = _hist_pfunc(intel);
	list_t *z = NULL;

	if (!HF)
		return (-1);

	hist = open(HF, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(HF);
	if (hist == -1)
		return (-1);
	for (z = intel->historynodeIN; z; z = z->next_nodeIN)
	{
		_putsfiledes_pfunc(z->stringIN, hist);
		_putfiledes_pfunc('\n', hist);
	}
	_putfiledes_pfunc(BUF_FLUSH, hist);
	close(hist);
	return (1);
}

/**
 * _histr_pfunc - reads the inputs from the HIST_FILE
 * @intel: the struct containing argument
 * Return: inputs from HIST_FILE, Else 0
 */
int _histr_pfunc(intel_t *intel)
{
	int a;
	int z = 0, sum = 0;
	ssize_t hist, lgt_r, size_f = 0;
	struct stat starg;
	char *b = NULL, *HF = _hist_pfunc(intel);

	if (!HF)
		return (0);

	hist = open(HF, O_RDONLY);
	free(HF);
	if (hist == -1)
		return (0);
	if (!fstat(hist, &starg))
		size_f = starg.st_size;
	if (size_f < 2)
		return (0);
	b = malloc(sizeof(char) * (size_f + 1));
	if (!b)
		return (0);
	lgt_r = read(hist, b, size_f);
	b[size_f] = 0;
	if (lgt_r <= 0)
		return (free(b), 0);
	close(hist);
	for (a = 0; a < size_f; a++)
		if (b[a] == '\n')
		{
			b[a] = 0;
			_histlist_pfunc(intel, b + z, sum++);
			z = a + 1;
		}
	if (z != a)
		_histlist_pfunc(intel, b + z, sum++);
	free(b);
	intel->MYhistory_counter = sum;
	while (intel->MYhistory_counter-- >= HIST_MAX)
		del_nodeIN(&(intel->historynodeIN), 0);
	_histlink_pfunc(intel);
	return (intel->MYhistory_counter);
}

/**
 * _histlist_pfunc - append inputs to build HIST_FILE
 * @intel: struct containing argument
 * @b: the pointer to the history buffer
 * @sum: a counter for the history line input
 * Return: 0 (Success)
 */
int _histlist_pfunc(intel_t *intel, char *b, int sum)
{
	list_t *z = NULL;

	if (intel->historynodeIN)
		z = intel->historynodeIN;
	nodeplusE(&z, b, sum);

	if (!intel->historynodeIN)
		intel->historynodeIN = z;
	return (0);
}

/**
 * _histlink_pfunc - links histlist after changes made to HIST_FILE
 * @intel: struct containing argument
 * Return: the new history counter after changes made
 */
int _histlink_pfunc(intel_t *intel)
{
	list_t *z = intel->historynodeIN;
	int a = 0;

	while (z)
	{
		z->nnumIN = a++;
		z = z->next_nodeIN;
	}
	return (intel->MYhistory_counter = a);
}
