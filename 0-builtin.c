#include "shell.h"

/**
 * _shellexit_pfunc - a funtion to exit the shell
 * @intel: Structure containing arguments
 * Return: exits the shell
 */

int _shellexit_pfunc(intel_t *intel)
{
	int sh_exit;

	if (intel->strargvIN[1])
	{
		sh_exit = _atoierr_pfunc(intel->strargvIN[1]);
		if (sh_exit == -1)
		{
			intel->MYcmd_status = 2;
			_prterror_pfunc(intel, "Number not found: ");
			_errputs_pfunc(intel->strargvIN[1]);
			_errputchar_pfunc('\n');
			return (1);
		}
		intel->_errnum = _atoierr_pfunc(intel->strargvIN[1]);
		return (-2);
	}
	intel->_errnum = -1;
	return (-2);
}

/**
 * _changedir_pfunc - a function that changes the current directory
 * @intel: Structure containing arguments
 * Return: 0 (Success)
 */
int _changedir_pfunc(intel_t *intel)
{
	char *str, *z;
	char buff_size[1024];
	int ch_direct;

	str = getcwd(buff_size, 1024);
	if (!str)
		_puts_pfunc("TODO: add error handling for the change directory failure\n");
	if (!intel->strargvIN[1])
	{
		z = getenvIN(intel, "HOME=");
		if (!z)
			ch_direct =
				chdir((z = getenvIN(intel, "PWD=")) ? z : "/");
		else
			ch_direct = chdir(z);
	}
	else if (_comparestr_pfunc(intel->strargvIN[1], "-") == 0)
	{
		if (!getenvIN(intel, "OLDPWD="))
		{
			_puts_pfunc(str);
			_putchar_pfunc('\n');
			return (1);
		}
		_puts_pfunc(getenvIN(intel, "OLDPWD=")), _putchar_pfunc('\n');
		ch_direct =
			chdir((z = getenvIN(intel, "OLDPWD=")) ? z : "/");
	}
	else
		ch_direct = chdir(intel->strargvIN[1]);
	if (ch_direct == -1)
	{
		_prterror_pfunc(intel, "cannot change directory ");
		_errputs_pfunc(intel->strargvIN[1]), _errputchar_pfunc('\n');
	}
	else
	{
		envset_pfunc(intel, "OLDPWD", getenvIN(intel, "PWD="));
		envset_pfunc(intel, "PWD", getcwd(buff_size, 1024));
	} return (0);
}

/**
 * _procdir_pfunc - helps to locate the current change directory process
 * @intel: Structure containing arguments
 * Return: 0 (Success)
 */

int _procdir_pfunc(intel_t *intel)
{
	char **CMD_proc;

	CMD_proc = intel->strargvIN;
	_puts_pfunc("command success. execution is pending \n");
	if (0)
		_puts_pfunc(*CMD_proc);
	return (0);
}
