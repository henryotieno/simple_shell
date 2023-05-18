#include "shell.h"

/**
 * fetch_environ – environment copy of string of array is returned.
 * always returned zero
 */
char **fetch_environ(info_x *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv – variable environment are removed
 *  once deleted it returns 1 and 0 on otherwise
 */
int _unsetenv(info_x *info, char *var)
{
	list_t *node = info->env;
	size_t m = 0;
	char *w;

	if (!node || !var)
		return (0);

	while (node)
	{
		w = starts_with(node->str, var);
		if (w && *w == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), m);
			m = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		m++;
	}
	return (info->env_changed);
}

/**
 * _setenv – new environment vaiable is initialized,
 *             and change the present
*0 is returned oftenly
 */
int _setenv(info_x *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *w;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		w = starts_with(node->str, var);
		if (w && *w == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

