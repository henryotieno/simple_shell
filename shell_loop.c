#include "shell.h"

/**
 * hsh - major loop
 * @info: parameter & return info structure
 * @av: argv
 * Return: 0 if right, 1 if wrong
 */
int hsh(info_x *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - locates in-built command
 * @info: par & structure
 * Return: -1 builtin present,
 * 0 builtin success,
 * 1 builtin present but not successful,
 * 2 exit builtin
 */
int find_builtin(info_x *info)
{
	int a, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _theexit},
		{"env", _theenv},
		{"help", _thehelp},
		{"history", _thehistory},
		{"setenv", _thesetenv},
		{"unsetenv", _theunsetenv},
		{"cd", _thecd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(info->argv[0], builtintbl[a].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[a].func(info);
			break;
		}
	return (built_in_ret);
}
/**
 * find_cmd - locates a command
 * @info: parameter and structure
 * Return: void
 */
void find_cmd(info_x *info)
{
	char *path = NULL;
	int a, t;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (a = 0, t = 0; info->arg[a]; a++)
		if (!is_delim(info->arg[a], " \t\n"))
			t++;
	if (!t)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - for forking
 * @info: parameter and structure
 * Return: void
 */
void fork_cmd(info_x *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, fetch_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
