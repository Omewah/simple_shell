#include "shell.h"

/**
 * defchain_pfunc - defines a chain delimeter character
 * @intel: strcture containing arguments
 * @charb: the character type buffer
 * @ptr: the pointer address of @charb
 * Return: 1 for a chain delimeter character, Else 0
 */
int defchain_pfunc(intel_t *intel, char *charb, size_t *ptr)
{
	size_t a = *ptr;

	if (charb[a] == '|' && charb[a + 1] == '|')
	{
		charb[a] = 0;
		a++;
		intel->MYcmd_buffer_types = CMD_OR;
	}
	else if (charb[a] == '&' && charb[a + 1] == '&')
	{
		charb[a] = 0;
		a++;
		intel->MYcmd_buffer_types = CMD_AND;
	}
	else if (charb[a] == ';')
	{
		charb[a] = 0;
		intel->MYcmd_buffer_types = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = a;
	return (1);
}

/**
 * extchain_pfunc - continues chaining after definition
 * @intel: strcture containing arguments
 * @charb: the character type buffer
 * @ptr: the pointer address of @charb
 * @s: buffer size to continue chaining
 * @lg: length of buffer char to continue chaining
 * Return: Void
 */
void extchain_pfunc(intel_t *intel, char *charb, size_t *ptr, size_t s, size_t lg)
{
	size_t a = *ptr;

	if (intel->MYcmd_buffer_types == CMD_AND)
	{
		if (intel->MYcmd_status)
		{
			charb[s] = 0;
			a = lg;
		}
	}
	if (intel->MYcmd_buffer_types == CMD_OR)
	{
		if (!intel->MYcmd_status)
		{
			charb[s] = 0;
			a = lg;
		}
	}

	*ptr = a;
}

/**
 * subalias - alias substitution
 * @intel: strcture containing arguments
 * Return: 1 (Success), Else 0
 */
int subalias(intel_t *intel)
{
	int a;
	list_t *z;
	char *sub;

	for (a = 0; a < 10; a++)
	{
		z = nodeST_pfunc(intel->alias_nodeIN, intel->strargvIN[0], '=');
		if (!z)
			return (0);
		free(intel->strargvIN[0]);
		sub = _findstrchar_pfunc(z->stringIN, '=');
		if (!sub)
			return (0);
		sub = _doublestr_pfunc(sub + 1);
		if (!sub)
			return (0);
		intel->strargvIN[0] = sub;
	}
	return (1);
}

/**
 * subvars - substitutes variabless in a string
 * @intel: strcture containing arguments
 * Return: 1 (Success), Else 0
 */
int subvars(intel_t *intel)
{
	int a = 0;
	list_t *z;

	for (a = 0; intel->strargvIN[a]; a++)
	{
		if (intel->strargvIN[a][0] != '$' || !intel->strargvIN[a][1])
			continue;

		if (!_comparestr_pfunc(intel->strargvIN[a], "$?"))
		{
			substringIN(&(intel->strargvIN[a]),
				_doublestr_pfunc(ddconvert_pfunc(intel->MYcmd_status, 10, 0)));
			continue;
		}
		if (!_comparestr_pfunc(intel->strargvIN[a], "$$"))
		{
			substringIN(&(intel->strargvIN[a]),
				_doublestr_pfunc(ddconvert_pfunc(getpid(), 10, 0)));
			continue;
		}
		z = nodeST_pfunc(intel->MYenvIron, &intel->strargvIN[a][1], '=');
		if (z)
		{
			substringIN(&(intel->strargvIN[a]),
				_doublestr_pfunc(_findstrchar_pfunc(z->stringIN, '=') + 1));
			continue;
		}
		substringIN(&intel->strargvIN[a], _doublestr_pfunc(""));

	}
	return (0);
}

/**
 * substringIN - string input substitution
 * @os: old string to be substituted
 * @ns: the new string after substituting @os
 * Return: 1 (Success), Else 0
 */
int substringIN(char **os, char *ns)
{
	free(*os);
	*os = ns;
	return (1);
}