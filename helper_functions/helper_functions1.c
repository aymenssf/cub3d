#include "../cub3d.h"

void	check_s2(char c, int *check, listt **node)
{
	if (c == '\n')
		(*check)++;
	else if (c == ' ')
		return ;
	else if (((c != '\n' && c != ' ') && *check > 1))
	{
		printf("error");
		garbage_collector(node, free);
		exit(1);
	}
	else
		*check = 0;
}

char	**map_to_s(char *s, int count, listt **node)
{
	int		check;
	int		i;
	char	**str;

	check = 0;
	i = -1;
	parse_s(&s, count);

	while (s[++i])
		check_s2(s[i], &check, node);
	str = ft_split(s, '\n');

	add_to_listt(str, node);
	mylist(str, node);
	return (str);
}

void	mylist(void *node, listt **nodee)
{
	listt	*nod;


	if(!node || !nodee)
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
		listt	*head;
		head = *nodee;
		while (head->next)
			head = head->next;
		head->next = nod;
	
}

void	garbage_collector(listt **lst, void (*del)(void *))
{
	listt	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->node);
		del(*lst);
		*lst = temp;
	}
}

void	add_to_listt(char **ss, listt **node)
{
	int i;

	i = -1;

	
	while (ss[++i])
			mylist(ss[i], node);
}