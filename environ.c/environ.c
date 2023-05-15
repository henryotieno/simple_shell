#include "shell.h"

/**
 * _theenv displays the current environment
 * Always returns a 0 value
 */
int _theenv(info_x *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv – fetches the value of the variable from the environment
 */
char *_getenv(info_x *info, const char *name)
{
	list_t *node = info->env;
	char *w;

	while (node)
	{
		w = starts_with(node->str, name);
		if (w && *w)
			return (w);
		node = node->next;
	}
	return (NULL);
}

/**
 * _thesetenv - Initialize a a variable in an environment
 *  Always returns a 0 when compiled
 */
int _thesetenv(info_x *info)
{
	if (info->argc != 3)
	{
		_eputs("Unsupported value\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _theunsetenv ensure environment variable is removed
 * Always returns  0 when compiled
 */
int _theunsetenv(info_x *info)
{
	int m;

	if (info->argc == 1)
	{
		_eputs("Little arguements.\n");
		return (1);
	}
	for (m = 1; m <= info->argc; m++)
		_unsetenv(info, info->argv[m]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * Always returns a 0 when compiled.
 */
int populate_env_list(info_x *info)
{
	list_t *node = NULL;
	size_t m;

	for (m = 0; environ[m]; m++)
		add_node_end(&node, environ[m], 0);
	info->env = node;
	return (0);
}

