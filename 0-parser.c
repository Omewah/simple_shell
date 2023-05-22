#include "shell.h"

/**
 * _cmdexe_pfunc - opts if a file command can be executed
 * @intel: struct containing arguments
 * @f_path: the file command path
 * Return: 1 (Success), Else 0
 */
int _cmdexe_pfunc(intel_t *intel, char *f_path)
{
	struct stat cmd;

	(void)intel;
	if (!f_path || stat(f_path, &cmd))
		return (0);

	if (cmd.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _dupchars_pfunc - create a duplicate of characters
 * @pathstrIN: the strings PATH to duplicate
 * @first: the first index starting point
 * @last: the last index stopping point
 * Return: pointer to new buffer
 */
char *_dupchars_pfunc(char *pathstrIN, int first, int last)
{
	static char buff_size[1024];
	int a = 0;
	int b = 0;

	for (b = 0, a = first; a < last; a++)
		if (pathstrIN[a] != ':')
			buff_size[b++] = pathstrIN[a];
	buff_size[b] = 0;
	return (buff_size);
}

/**
 * locate_path_pfunc - locates command input in the PATH
 * @intel: struct containing arguments
 * @pathstrIN: the string PATH to search in
 * @com: the command to be located
 * Return: @com_path, Else NULL
 */
char *locate_path_pfunc(intel_t *intel, char *pathstrIN, char *com)
{
	int a = 0;
	int current = 0;
	char *com_path;

	if (!pathstrIN)
		return (NULL);
	if ((_lenstrn_pfunc(com) > 2) && checkpoint_pfunc(com, "./"))
	{
		if (_cmdexe_pfunc(intel, com))
			return (com);
	}
	while (1)
	{
		if (!pathstrIN[a] || pathstrIN[a] == ':')
		{
			com_path = _dupchars_pfunc(pathstrIN, current, a);
			if (!*com_path)
				_concatstr_pfunc(com_path, com);
			else
			{
				_concatstr_pfunc(com_path, "/");
				_concatstr_pfunc(com_path, com);
			}
			if (_cmdexe_pfunc(intel, com_path))
				return (com_path);
			if (!pathstrIN[a])
				break;
			current = a;
		}
		a++;
	}
	return (NULL);
}
