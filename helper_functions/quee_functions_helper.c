/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quee_functions_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 04:55:03 by yaboulan          #+#    #+#             */
/*   Updated: 2024/11/16 04:57:09 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	store_to_error(char **s, char *error)
{
	if(*s[0] == 0)
		*s = error;
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
