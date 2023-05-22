#include "shell.h"

/**
 * _intel_clear - the intel_t struct launcher
 * @intel: struct containing arguments
 */
void _intel_clear(intel_t *intel)
{
	intel->strargIN = NULL;
	intel->strargvIN = NULL;
	intel->strpathIN = NULL;
	intel->strarg_counterIN = 0;
}

/**
 * _intel_set - positions the intel_t struct
 * @intel: struct containing arguments
 * @av: the pointer vector to the first argument
 */
void _intel_set(intel_t *intel, char **av)
{
	int a = 0;

	intel->MYfilename = av[0];
	if (intel->strargIN)
	{
		intel->strargvIN = splitstr_pfunc(intel->strargIN, " \t");
		if (!intel->strargvIN)
		{

			intel->strargvIN = malloc(sizeof(char *) * 2);
			if (intel->strargvIN)
			{
				intel->strargvIN[0] = _doublestr_pfunc(intel->strargIN);
				intel->strargvIN[1] = NULL;
			}
		}
		for (a = 0; intel->strargvIN && intel->strargvIN[a]; a++)
			;
		intel->strarg_counterIN = a;

		subalias(intel);
		subvars(intel);
	}
}

/**
 * _intel_free - release intel_t struct memory
 * @intel: struct containing arguments
 * @mem: all struct memory field free'd
 */
void _intel_free(intel_t *intel, int mem)
{
	_strfree_pfunc(intel->strargvIN);
	intel->strargvIN = NULL;
	intel->strpathIN = NULL;
	if (mem)
	{
		if (!intel->MYcmd_buffer)
			free(intel->strargIN);
		if (intel->MYenvIron)
			nodefree_pfunc(&(intel->MYenvIron));
		if (intel->historynodeIN)
			nodefree_pfunc(&(intel->historynodeIN));
		if (intel->alias_nodeIN)
			nodefree_pfunc(&(intel->alias_nodeIN));
		_strfree_pfunc(intel->environ);
			intel->environ = NULL;
		_pmemfree_pfunc((void **)intel->MYcmd_buffer);
		if (intel->MYreadfiledes > 2)
			close(intel->MYreadfiledes);
		_putchar_pfunc(BUF_FLUSH);
	}
}
