/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 04:53:31 by yaboulan          #+#    #+#             */
/*   Updated: 2024/11/16 04:53:32 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	last_ind(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] == ' ')
		i--;
	return (i);
}

int	first_ind(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	ft_listsize(list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	list_fill(list **listtt, listt **node)
{
	*listtt = malloc(sizeof(list));
	if (!(*listtt))
		return ;
	mylist(*listtt, node);
	fill_listt(listtt, node);
}

void	fill_listt(list **listo, listt **liste)
{
	(*listo) = NULL;
	add_nodee("SO", listo, liste);
	add_nodee("WE", listo, liste);
	add_nodee("EA", listo, liste);
	add_nodee("NO", listo, liste);
	add_nodee("F", listo, liste);
	add_nodee("C", listo, liste);
}
