#include "../cub3d.h"

void	check_s2(char c, int *check, myvar *var)
{
	if (c == '\n')
		(*check)++;
	else if (c == ' ')
		return ;
	else if (((c != '\n' && c != ' ') && *check > 1))
	{
		printf("error");
		garbage_collector(var, free);
		exit(1);
	}
	else
		*check = 0;
}

char	**map_to_s(char *s, int count, myvar *var)
{
	int		check;
	int		i;
	char	**str;

	check = 0;
	i = -1;
	parse_s(&s, count);
	while (s[++i])
		check_s2(s[i], &check, var);
	str = ft_split(s, '\n');
	add_to_listt(str, &var->list);
	mylist(str, &var->list);
	return (str);
}

void	mylist(void *node, listt **nodee)
{
	listt	*nod;
	listt	*head;

	if (!node || !nodee)
		return ;
	nod = malloc(sizeof(listt));
	if (!nod)
		return ;
	nod->node = node;
	nod->next = NULL;
	if (!*nodee)
	{
		*nodee = nod;
		return ;
	}
	head = *nodee;
	while (head->next)
		head = head->next;
	head->next = nod;
}

void	garbage_collector(myvar *var, void (*del)(void *))
{
	listt	*temp;
	listt **lst = &var->list;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->node);
		del(*lst);
		*lst = temp;
	}
	free(var->data);
}

void	add_to_listt(char **ss, listt **node)
{
	int	i;

	i = -1;
	while (ss[++i])
		mylist(ss[i], node);
}
