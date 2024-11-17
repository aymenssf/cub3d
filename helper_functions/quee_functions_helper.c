/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quee_functions_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 04:55:03 by yaboulan          #+#    #+#             */
/*   Updated: 2024/11/17 13:31:59 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	store_to_error(t_myvar *var,char **s, char *error)
{
	if (*s[0] == 0)
		*s = error;
	printf("Error %s\n",error);
	garbage_collector(var,free);
	exit(1);
}

int	check_s(char **s, t_liist **list, t_myvar *var)
{
	int		i;
	char	**k;

	i = 0;
	k = ft_split(s[i], ' ');
	while (s[i] && k)
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
		i++;
		k = ft_split(s[i], ' ');
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
