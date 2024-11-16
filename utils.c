/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:13:07 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/16 21:15:44 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	is_wall(myvar *var, int x, int y)
{
	if (x < 0 || x >= var->data->map_cols || y < 0 || y >= var->data->map_rows
		|| (size_t)y >= ft_strlen(var->s[y]))
		return (1);
	return (var->s[y][x] != '0');
}

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec * 1000.0 + (double)tv.tv_usec / 1000.0);
}

void	destroy(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_loop_end(data->mlx);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	exit(0);
}

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
