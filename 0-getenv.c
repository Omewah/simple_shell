#include "shell.h"

/**
 * environcp_pfunc - prints a copy of the environ string
 * @intel: Structure containing arguments
 * Return: 0 (Success)
 */
char **environcp_pfunc(intel_t *intel)
{
	if (!intel->environ || intel->MYenviron_checker)
	{
		intel->environ = _strlist_pfunc(intel->MYenvIron);
		intel->MYenviron_checker = 0;
	}

	return (intel->environ);
}

/**
 * envunset_pfunc - releases an environment variable
 * @intel: Structure containing arguments
 * Return: 1 if released, Else 0
 * @tag: the environ variable designation
 */
int envunset_pfunc(intel_t *intel, char *tag)
{
	list_t *env_tag = intel->MYenvIron;
	size_t a = 0;
	char *b;

	if (!env_tag || !tag)
		return (0);

	while (env_tag)
	{
		b = checkpoint_pfunc(env_tag->stringIN, tag);
		if (b && *b == '=')
		{
			intel->MYenviron_checker = del_nodeIN(&(intel->MYenvIron), a);
			a = 0;
			env_tag = intel->MYenvIron;
			continue;
		}
		env_tag = env_tag->next_nodeIN;
		a++;
	}
	return (intel->MYenviron_checker);
}

/**
 * envset_pfunc - positions an environment or modify exisitng
 * @intel: Structure containing arguments
 * @tag: the environ variable designation
 * @val: the enviroment string value to set
 * Return: 0 (Success)
 */
int envset_pfunc(intel_t *intel, char *tag, char *val)
{
	char *r = NULL;
	list_t *env_tag;
	char *b;

	if (!tag || !val)
		return (0);

	r = malloc(_lenstrn_pfunc(tag) + _lenstrn_pfunc(val) + 2);
	if (!r)
		return (1);
	_copystr_pfunc(r, tag);
	_concatstr_pfunc(r, "=");
	_concatstr_pfunc(r, val);
	env_tag = intel->MYenvIron;
	while (env_tag)
	{
		b = checkpoint_pfunc(env_tag->stringIN, tag);
		if (b && *b == '=')
		{
			free(env_tag->stringIN);
			env_tag->stringIN = r;
			intel->MYenviron_checker = 1;
			return (0);
		}
		env_tag = env_tag->next_nodeIN;
	}
	nodeplusE(&(intel->MYenvIron), r, 0);
	free(r);
	intel->MYenviron_checker = 1;
	return (0);
}
