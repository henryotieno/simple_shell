#include "shell.h"

/**
 * theexit prompts and exit from the shell
 * Return: exits the shell with a given exit status
 */
int _theexit(info_x *info)
{
	int exitstatus;

	if (info->argv[1]) 
	{
		exitstatus = _erratoi(info->argv[1]);
		if (exitstatus == -1)
		{
			info->status = 2;
			print_error(info, "Wrong Value: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _thecd is helpful in changing the current directory of the process
 * It is a constant function prototype.
 */
int _thecd(info_x *info)
{
	char *b, *dir, buffer[1024];
	int chdir_ret;

	b = getcwd(buffer, 1024);
	if (!b)
		_puts("TODO: >>getcwd failure message appears here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = 
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(b);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = 
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "cannot change directory to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _thehelp -when applied changes the process directory
 * will always return 0
 */
int _thehelp(info_x *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("function calling help works and yet to be implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

