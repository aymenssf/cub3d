/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:13:07 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/15 13:14:00 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	destroy_image(myvar *var)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(var->data->mlx, var->texturess[i].img);
	mlx_destroy_image(var->data->mlx, var->texture_hands.img);
}

int	close_window(myvar *data)
{
	   mlx_clear_window(data->data->mlx, data->data->win);
    destroy_image(data);
    mlx_destroy_image(data->data->mlx, data->data->img);
    mlx_destroy_window(data->data->mlx, data->data->win);
    mlx_destroy_display(data->data->mlx);
    free(data->data->mlx);
    garbage_collector(data, free);
	exit(0);
	return (0);
}
