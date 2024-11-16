/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 04:50:01 by yaboulan          #+#    #+#             */
/*   Updated: 2024/11/16 22:25:43 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_s2(char c, int *check, t_myvar *var)
{
	if (c == '\n')
		(*check)++;
	else if (c == ' ')
		return ;
	else if (((c != '\n' && c != ' ') && *check > 1))
	{
		printf("Error On Formula Of Textures \n");
		garbage_collector(var, free);
		exit(1);
	}
	else
		*check = 0;
}

char	**map_to_s(char *s, int count, t_myvar *var)
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
	if (!str)
	{
		printf("Error Missed CUB \n");
		garbage_collector(var, free);
		exit(1);
	}
	add_to_listt(str, &var->list);
	mylist(str, &var->list);
	return (str);
}

void	mylist(void *node, t_listt **nodee)
{
	t_listt	*nod;
	t_listt	*head;

	if (!node || !nodee)
		return ;
	nod = malloc(sizeof(t_listt));
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

void	garbage_collector(t_myvar *var, void (*del)(void *))
{
	t_listt	*temp;
	t_listt	**lst;

	lst = &var->list;
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

void	add_to_listt(char **ss, t_listt **node)
{
	int	i;

	i = -1;
	while (ss[++i])
		mylist(ss[i], node);
}
