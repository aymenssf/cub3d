#include "../cub3d.h"

queue	*add_node(int x, int y)
{
	queue	*queuee;

	queuee = malloc(sizeof(queue));
	queuee->x = x;
	queuee->y = y;
	queuee->visited = 1;
	queuee->next = NULL;
	return (queuee);
}

void	add_quee(queue **queu, int x, int y, listt **node)
{
	queue	*queuee;
	queue	*head;

	queuee = malloc(sizeof(queue));
	queuee->x = x;
	queuee->y = y;
	queuee->visited = 1;
	queuee->next = NULL;
	mylist(queuee, node);
	if (!(*queu))
		*queu = queuee;
	else
	{
		head = *queu;
		while ((head)->next)
			(head) = (head)->next;
		head->next = queuee;
	}
}

void	dequee(queue **queu)
{
	queue *front;

	if (!(*queu))
		return ;
	if (!(*queu)->next)
	{
		*queu = NULL;
	}
	else
	{
		front = *queu;
		*queu = front->next;
		front = NULL;
	}
}

int	check_s(char **s, list **list, myvar *var)
{
	int		i;
	char	**k;

	i = -1;
	while (s[++i] && (k = ft_split(s[i], ' ')))
	{
		add_to_listt(k, &var->list);
		mylist(k, &var->list);
		if (k)
		{
			if (!k[0])
				continue ;
			check_texture_floor(k[0], s[i], var, list);
		}
		if (var->count == 6)
			break ;
	}
	return (0);
}

int	count(char **s)
{
	int	i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}
