/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 04:53:31 by yaboulan          #+#    #+#             */
/*   Updated: 2024/11/16 22:26:05 by aassaf           ###   ########.fr       */
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

int	ft_listsize(t_liist *lst)
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

void	list_fill(t_liist **listtt, t_listt **node)
{
	*listtt = malloc(sizeof(t_list));
	if (!(*listtt))
		return ;
	mylist(*listtt, node);
	fill_listt(listtt, node);
}

void	fill_listt(t_liist **listo, t_listt **liste)
{
	(*listo) = NULL;
	add_nodee("SO", listo, liste);
	add_nodee("WE", listo, liste);
	add_nodee("EA", listo, liste);
	add_nodee("NO", listo, liste);
	add_nodee("F", listo, liste);
	add_nodee("C", listo, liste);
}
