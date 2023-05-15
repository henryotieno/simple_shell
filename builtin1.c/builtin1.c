#include "shell.h"

/**
 * _thehistory clearly displays the history
 *  always returns 0
 */
int _thehistory(info_x *info)
{
	print_list(info->history);
	return (0);
}

int unclear_relat(info_x *info, char *str)
{
	char *w, o;
	int val;

	w = _strchr(str, '=');
	if (!w)
		return (1);
	o = *w;
	*w = 0;
	val = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*w = o;
	return (val);
}

int set_alias(info_x *info, char *str)
{
	char *w;

	w = _strchr(str, '=');
	if (!w)
		return (1);
	if (!*++w)
		return (unclear_relat(info, str));

	unclear_relat(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

int print_alias(list_t *node)
{
	char *w = NULL, *a = NULL;

	if (node)
	{
		w = _strchr(node->str, '=');
		for (a = node->str; a <= w; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

int _myalias(info_x *info)
{
	int m = 0;
	char *w = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (m = 1; info->argv[m]; m++)
	{
		w = _strchr(info->argv[m], '=');
		if (w)
			set_alias(info, info->argv[m]);
		else
			print_alias(node_starts_with(info->alias, info->argv[m], '='));
	}

	return (0);
}

