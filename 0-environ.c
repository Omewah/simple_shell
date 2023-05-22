#include "shell.h"

/**
 * _currenv - a function that prints the ongoing environment
 * @intel: structure containing arguments
 * Return: 0 (Success)
 */
int _currenv(intel_t *intel)
{
	_printL_pfunc(intel->MYenvIron);
	return (0);
}

/**
 * getenvIN - a function that prints the environ variable value
 * @intel: structure containing arguments
 * @tag: the environ variable designation
 * Return: the value of environ variable to print
 */
char *getenvIN(intel_t *intel, const char *tag)
{
	list_t *env_tag = intel->MYenvIron;
	char *a;

	while (env_tag)
	{
		a = checkpoint_pfunc(env_tag->stringIN, tag);
		if (a && *a)
			return (a);
		env_tag = env_tag->next_nodeIN;
	}
	return (NULL);
}

/**
 * _envset_pfunc - positions the new environment
 * @intel: structure containing arguments
 * Return: 0 (Success)
 */
int _envset_pfunc(intel_t *intel)
{
	if (intel->strarg_counterIN != 3)
	{
		_errputs_pfunc("The number of arguements is incorrect\n");
		return (1);
	}
	if (envset_pfunc(intel, intel->strargvIN[1], intel->strargvIN[2]))
		return (0);
	return (1);
}

/**
 * _envunset_pfunc - releases an environment variable
 * @intel: structire containing arguments
 * Return: 0 (Success)
 */
int _envunset_pfunc(intel_t *intel)
{
	int a;

	if (intel->strarg_counterIN == 1)
	{
		_errputs_pfunc("Sorry, arguements are too few.\n");
		return (1);
	}
	for (a = 1; a <= intel->strarg_counterIN; a++)
		envunset_pfunc(intel, intel->strargvIN[a]);

	return (0);
}

/**
 * load_list_pfunc - displays an enviroment linked list
 * @intel: structire containing arguments
 * Return: 0 (Success)
 */
int load_list_pfunc(intel_t *intel)
{
	list_t *env_tag = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		nodeplusE(&env_tag, environ[a], 0);
	intel->MYenvIron = env_tag;
	return (0);
}
