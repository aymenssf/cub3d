#include "../cub3d.h"

int	check_j(int *check, char *s)
{
	int	i;
	int	len;

	i = 0;
	while (s[i] == ' ')
		i++;
	len = ft_strlen(s) - 1;
	while (s[len] == ' ' && len--)
		;
	if ((s[i] != '1') || (s[len] != '1'))
	{
		*check = -1;
		return (1);
	}
	return (0);
}

int	simple_check(int i, int j, char **s, int check)
{
	if (i == 0 || i == check || check_j(&check, s[i]))
	{
		if (i == check)
		{
			i = check;
			check_j(&check, s[check]);
		}
		if ((s[i][j] != '1' && s[i][j] != ' ') || check == -1)
			return (1);
	}
	else if (s[i][j] == '0')
	{
		if (!(s[i][j + 1]) || s[i][j + 1] == ' ')
			return (1);
		if (!(s[i][j - 1]) || s[i][j - 1] == ' ')
			return (1);
		if (!(s[i - 1][j]) || s[i - 1][j] == ' ')
			return (1);
		if (!(s[i + 1][j]) || s[i + 1][j] == ' ')
			return (1);
	}
	return (0);
}

void	store_line(char **line, myvar *var, char **s)
{
	mylist(*line, &(var->list));
	*s = ft_strjoin(*s, *line);
	mylist(*s, &(var->list));
	*line = get_next_line(var->fd);
}

void	add_node_list(char *name, list **listo, int *countt, listt **node)
{
	list	*head;

	head = *listo;
	while ((head))
	{
		if (!ft_strncmp((head)->name, name, ft_strlen(name)))
		{
			(head)->value++;
			(*countt)++;
			return ;
		}
		head = head->next;
	}
	printf("error");
	garbage_collector(node, free);
	exit(1);
}

int	check_xy(int x, int y, char **s)
{
	if ((s[x - 1][y] == ' ') || (s[x][y - 1] == ' ') || (s[x + 1][y] == ' ')
		|| (s[x][y + 1] == ' '))
		return (1);
	return (0);
}
