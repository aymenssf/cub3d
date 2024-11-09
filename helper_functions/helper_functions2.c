#include "../cub3d.h"

void	store_to_textures(myvar *var, char *s)
{
	int	i;

	i = 0;
	if (var->textures[3] != NULL)
		return ;
	while (var->textures[i])
		i++;
	var->textures[i] = s;
}

int	check_len(char **s)
{
	int	i;
	int	j;
	int	check;

	i = -1;
	j = -1;
	check = 0;
	while (s[++i])
	{
		j = -1;
		check = 0;
		while (s[i][++j])
		{
			if (s[i][j] != ' ')
				check = 1;
		}
		if (check == 0)
			break ;
	}
	return (i);
}

int	check_map2(char **s)
{
	int	i;
	int	j;
	int	check;

	i = -1;
	j = -1;
	check = 0;
	check = check_len(s) - 1;
	while (s[++i])
	{
		j = -1;
		while (s[i][++j])
		{
			if (simple_check(i, j, s, check))
				return (1);
		}
		if (i == check)
			return (0);
	}
	return (0);
}

void	add_nodee(char *name, list **listo, listt **liste)
{
	list	*test;
	list	*head;

	test = malloc(sizeof(list));
	if (!test)
		return ;
	if (!(*listo))
	{
		mylist(test, liste);
		test->name = name;
		test->next = NULL;
		test->value = 0;
		(*listo) = test;
	}
	else
	{
		head = *listo;
		while (head->next)
			head = head->next;
		mylist(test, liste);
		test->name = name;
		test->next = NULL;
		test->value = 0;
		head->next = test;
	}
}

int	check_ss(char *line, listt **node)
{
	int	check;

	line = ft_strtrim(line, " ");
	mylist(line, node);
	check = 0;
	while (*line)
	{
		if (*line == ' ')
			check = 1;
		if ((check == 1 && *line != ' ') || !ft_isdigit(*line))
			return (1);
		line++;
	}
	return (0);
}
