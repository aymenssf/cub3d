/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 23:08:54 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/16 22:15:21 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	init_ray(t_data *data, int x, t_ray *ray)
{
	ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	data->ray_dir_x = data->dir_x + data->plane_x * ray->camera_x;
	data->ray_dir_y = data->dir_y + data->plane_y * ray->camera_x;
	ray->map_x = (int)data->pos_x;
	ray->map_y = (int)data->pos_y;
	if (data->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / data->ray_dir_x);
	if (data->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / data->ray_dir_y);
	ray->hit = 0;
}

void	calculate_step_direction(double ray_dir_x, double ray_dir_y,
		int *step_x, int *step_y)
{
	if (ray_dir_x < 0)
		*step_x = -1;
	else
		*step_x = 1;
	if (ray_dir_y < 0)
		*step_y = -1;
	else
		*step_y = 1;
}

void	calcul_map_dimens(t_myvar *var)
{
	int	row;
	int	col;
	int	i;
	int	line_length;

	row = 0;
	col = 0;
	while (var->s[row])
		row++;
	i = 0;
	while (i < row)
	{
		line_length = ft_strlen(var->s[i]);
		if (line_length > col)
			col = line_length;
		i++;
	}
	var->data->map_rows = row;
	var->data->map_cols = col;
}
