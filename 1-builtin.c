#include "shell.h"

/**
 * _shellhist_pfunc - prints the shell history list with its line numbers
 * @intel: structure containing arguments
 * Return: 0 (Success)
 */
int _shellhist_pfunc(intel_t *intel)
{
	printLL_pfunc(intel->historynodeIN);
	return (0);
}

/**
 * remove_alias_pfunc - temporary removes an alias
 * @intel: structure containing arguments
 * @stringIN: the string with an alias added
 * Return: 0 (Success), Else 1
 */
int remove_alias_pfunc(intel_t *intel, char *stringIN)
{
	char *a;
	char d;
	int rem;

	a = _findstrchar_pfunc(stringIN, '=');
	if (!a)
		return (1);
	d = *a;
	*a = 0;
	rem = del_nodeIN(&(intel->alias_nodeIN),
		nodeIX_pfunc(intel->alias_nodeIN,
			nodeST_pfunc(intel->alias_nodeIN, stringIN, -1)));
	*a = d;
	return (rem);
}

/**
 * define_alias_pfunc - defines and adds an alias to a string
 * @intel: structure containing arguments
 * @stringIN: the string to add an alias to
 * Return:  0 (Success), Else 1
 */
int define_alias_pfunc(intel_t *intel, char *stringIN)
{
	char *da;

	da = _findstrchar_pfunc(stringIN, '=');
	if (!da)
		return (1);
	if (!*++da)
		return (remove_alias_pfunc(intel, stringIN));

	remove_alias_pfunc(intel, stringIN);
	return (nodeplusE(&(intel->alias_nodeIN), stringIN, 0) == NULL);
}

/**
 * return_alias_pfunc - prints the string after the alias has been added
 * @nnode: the nth alias node to be printed
 * Return: 0 (Success), Else 1
 */
int return_alias_pfunc(list_t *nnode)
{
	char *pstr = NULL;
	char *b = NULL;

	if (nnode)
	{
		pstr = _findstrchar_pfunc(nnode->stringIN, '=');
		for (b = nnode->stringIN; b <= pstr; b++)
			_putchar_pfunc(*b);
		_putchar_pfunc('\'');
		_puts_pfunc(pstr + 1);
		_puts_pfunc("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias_pfunc - defines a new command by substituting a string input
 * @intel: structure containing arguments
 * Return: 0 (Success)
 */
int _alias_pfunc(intel_t *intel)
{
	int a = 0;
	char *sub = NULL;
	list_t *nnode = NULL;

	if (intel->strarg_counterIN == 1)
	{
		nnode = intel->alias_nodeIN;
		while (nnode)
		{
			(return_alias_pfunc(nnode));
			nnode = nnode->next_nodeIN;
		}
		return (0);
	}
	for (a = 1; intel->strargvIN[a]; a++)
	{
		sub = _findstrchar_pfunc(intel->strargvIN[a], '=');
		if (sub)
			define_alias_pfunc(intel, intel->strargvIN[a]);
		else
			return_alias_pfunc(nodeST_pfunc(intel->alias_nodeIN,
						intel->strargvIN[a], '='));
	}

	return (0);
}
