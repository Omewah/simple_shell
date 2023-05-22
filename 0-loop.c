#include "shell.h"

/**
 * _shell_pfunc - the main shell infinite loop
 * @intel: struct containing atguments
 * @av: my first argument vector
 * Return: 0 (Success), Else 1
 */
int _shell_pfunc(intel_t *intel, char **av)
{
	ssize_t i = 0;
	int result = 0;

	while (i != -1 && result != -2)
	{
		_intel_clear(intel);
		if (_shellact_pfunc(intel))
			_puts_pfunc("CJ$ ");
		_errputchar_pfunc(BUF_FLUSH);
		i = _getIN_pfunc(intel);
		if (i != -1)
		{
			_intel_set(intel, av);
			result = locate_builtin_pfunc(intel);
			if (result == -1)
				locate_cmd_pfunc(intel);
		}
		else if (_shellact_pfunc(intel))
			_putchar_pfunc('\n');
		_intel_free(intel, 0);
	}
	_histw_pfunc(intel);
	_intel_free(intel, 1);
	if (!_shellact_pfunc(intel) && intel->MYcmd_status)
		exit(intel->MYcmd_status);
	if (result == -2)
	{
		if (intel->_errnum == -1)
			exit(intel->MYcmd_status);
		exit(intel->_errnum);
	}
	return (result);
}

/**
 * locate_builtin_pfunc - searches for the builtin command
 * @intel: struct containing arguments
 * Return: 0 (Success), -1 (Failed)
 * 1 (found but failed exec), -2 (Signal lost)
 */
int locate_builtin_pfunc(intel_t *intel)
{
	int a;
	int builtIN_cmd = -1;
	built_in_tables tableIN[] = {
		{"exit", _shellexit_pfunc},
		{"env", _currenv},
		{"help", _procdir_pfunc},
		{"history", _shellhist_pfunc},
		{"setenv", _envset_pfunc},
		{"unsetenv", _envunset_pfunc},
		{"cd", _changedir_pfunc},
		{"alias", _alias_pfunc},
		{NULL, NULL}
	};

	for (a = 0; tableIN[a].MYtypes_IN; a++)
		if (_comparestr_pfunc(intel->strargvIN[0], tableIN[a].MYtypes_IN) == 0)
		{
			intel->linecounterIN++;
			builtIN_cmd = tableIN[a].MYfunctionIN(intel);
			break;
		}
	return (builtIN_cmd);
}

/**
 * locate_cmd_pfunc - locates the command PATH
 * @intel: struct containing arguments
 * Return: void
 */
void locate_cmd_pfunc(intel_t *intel)
{
	char *pFIND = NULL;
	int a;
	int b;

	intel->strpathIN = intel->strargvIN[0];
	if (intel->MYlinecount_flagIN == 1)
	{
		intel->linecounterIN++;
		intel->MYlinecount_flagIN = 0;
	}
	for (a = 0, b = 0; intel->strargIN[a]; a++)
		if (!_defchar_pfunc(intel->strargIN[a], " \t\n"))
			b++;
	if (!b)
		return;

	pFIND = locate_path_pfunc(intel, getenvIN(intel, "PATH="),
			intel->strargvIN[0]);
	if (pFIND)
	{
		intel->strpathIN = pFIND;
		fork_cmd_pfunc(intel);
	}
	else
	{
		if ((_shellact_pfunc(intel) || getenvIN(intel, "PATH=")
			|| intel->strargvIN[0][0] == '/') && _cmdexe_pfunc(intel,
				intel->strargvIN[0]))
			fork_cmd_pfunc(intel);
		else if (*(intel->strargIN) != '\n')
		{
			intel->MYcmd_status = 127;
			_prterror_pfunc(intel, "command not found\n");
		}
	}
}

/**
 * fork_cmd_pfunc - calls an executor to process a command input
 * @intel: struct containing arguments
 * Return: void
 */
void fork_cmd_pfunc(intel_t *intel)
{
	pid_t bby_pid;

	bby_pid = fork();
	if (bby_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (bby_pid == 0)
	{
		if (execve(intel->strpathIN, intel->strargvIN, environcp_pfunc(intel)) == -1)
		{
			_intel_free(intel, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(intel->MYcmd_status));
		if (WIFEXITED(intel->MYcmd_status))
		{
			intel->MYcmd_status = WEXITSTATUS(intel->MYcmd_status);
			if (intel->MYcmd_status == 126)
				_prterror_pfunc(intel, "Permission not granted\n");
		}
	}
}
