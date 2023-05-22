#include "shell.h"

/**
 * main - the function entry point
 * @ac: my first argument
 * @av: the pointer vector to the first argument
 * Return: 0 (success), Else 1
 */
int main(int ac, char **av)
{
	intel_t intel[] = { INTEL_INIT };
	int filedes = STDERR_FILENO;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (filedes)
		: "r" (filedes));

	if (ac == 2)
	{
		filedes = open(av[1], O_RDONLY);
		if (filedes == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_errputs_pfunc(av[0]);
				_errputs_pfunc(": 0: Cannot be opened ");
				_errputs_pfunc(av[1]);
				_errputchar_pfunc('\n');
				_errputchar_pfunc(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		intel->MYreadfiledes = filedes;
	}
	load_list_pfunc(intel);
	_histr_pfunc(intel);
	_shell_pfunc(intel, av);
	return (EXIT_SUCCESS);
}
