/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:44:07 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/16 22:01:54 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

static void	init_n(myvar *var)
{
	var->data->dir_x = 0;
	var->data->dir_y = 1;
	var->data->plane_x = -0.66;
	var->data->plane_y = 0;
}

static void	init_e(myvar *var)
{
	var->data->dir_x = 1;
	var->data->dir_y = 0;
	var->data->plane_x = 0;
	var->data->plane_y = 0.66;
}

static void	init_w(myvar *var)
{
	var->data->dir_x = -1;
	var->data->dir_y = 0;
	var->data->plane_x = 0;
	var->data->plane_y = -0.66;
}

static void	set_direc_player(myvar *var, char direc)
{
	if (direc == 'S')
	{
		var->data->dir_x = 0;
		var->data->dir_y = -1;
		var->data->plane_x = 0.66;
		var->data->plane_y = 0;
	}
	else if (direc == 'N')
		init_n(var);
	else if (direc == 'E')
		init_e(var);
	else if (direc == 'W')
		init_w(var);
}

void	detect_direc_player(myvar *var)
{
	int (i), (j);
	i = 0;
	while (var->s[i])
	{
		j = 0;
		while (var->s[i][j])
		{
			if (strchr("NSEW", var->s[i][j]))
			{
				var->player.x = j;
				var->player.y = i;
				set_direc_player(var, var->s[i][j]);
				var->s[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}
