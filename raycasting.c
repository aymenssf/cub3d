/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:42:28 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/15 23:12:36 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

static void	calculate_side_distances(t_ray_calc *calc)
{
	if (calc->step_x < 0)
		calc->side_dist_x = (calc->ray_pos_x - floor(calc->ray_pos_x))
			* calc->delta_dist_x;
	else
		calc->side_dist_x = (ceil(calc->ray_pos_x) - calc->ray_pos_x)
			* calc->delta_dist_x;
	if (calc->step_y < 0)
		calc->side_dist_y = (calc->ray_pos_y - floor(calc->ray_pos_y))
			* calc->delta_dist_y;
	else
		calc->side_dist_y = (ceil(calc->ray_pos_y) - calc->ray_pos_y)
			* calc->delta_dist_y;
}

static void	draw_ray_pixel(t_data *data, t_ray_calc *calc, int tile_size,
		int color)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = (int)(calc->ray_pos_x * tile_size);
	pixel_y = (int)(calc->ray_pos_y * tile_size);
	if (pixel_x >= 0 && pixel_x < MAP_WIDTH && pixel_y >= 0
		&& pixel_y < MAP_WIDTH)
		my_mlx_pixel_put(data, pixel_x, pixel_y, color);
}

static void	update_ray_position(t_ray_calc *calc)
{
	if (calc->side_dist_x < calc->side_dist_y)
	{
		calc->side_dist_x += calc->delta_dist_x;
		calc->ray_pos_x += calc->step_x;
	}
	else
	{
		calc->side_dist_y += calc->delta_dist_y;
		calc->ray_pos_y += calc->step_y;
	}
}

void	init_ray_calc(t_ray_calc *calc, t_data *data)
{
	calc->ray_pos_x = data->pos_x;
	calc->ray_pos_y = data->pos_y;
	calc->delta_dist_x = fabs(1 / data->ray_dir_x);
	calc->delta_dist_y = fabs(1 / data->ray_dir_y);
	calculate_step_direction(data->ray_dir_x, data->ray_dir_y, &calc->step_x,
		&calc->step_y);
	calculate_side_distances(calc);
}

void	draw_ray(myvar *var, t_data *data, int color)
{
	t_ray_calc	calc;
	int			hit;
	int			tile_size;

	tile_size = MAP_WIDTH / 20;
	init_ray_calc(&calc, data);
	hit = 0;
	while (!hit)
	{
		draw_ray_pixel(data, &calc, tile_size, color);
		update_ray_position(&calc);
		if (is_wall(var, (int)calc.ray_pos_x, (int)calc.ray_pos_y))
			hit = 1;
	}
}
