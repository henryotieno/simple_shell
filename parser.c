#include "shell.h"

/**
 * is_cmd - checks if a file is executable
 * @path: pathway
 * @info: information structure
 * Return: 1 right, 0 wrong
 */
int is_cmd(info_x *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - chars duplicator
 * @pathstr: sting pathway
 * @start:commencing index
 * @stop: halting index
 * Return: pointer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int a = 0, c = 0;

	for (c = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buf[c++] = pathstr[a];
	buf[c] = 0;
	return (buf);
}

/**
 * find_path - locates cmd
 * @cmd: cmd to locate
 * @pathstr: string pathway
 * @info: structure of info
 * Return: full path of cmd if right/ null if not
 */
char *find_path(info_x *info, char *pathstr, char *cmd)
{
	int a = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = dup_chars(pathstr, curr_pos, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[a])
				break;
			curr_pos = a;
		}
		a++;
	}
	return (NULL);
}
