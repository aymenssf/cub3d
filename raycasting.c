/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:42:28 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/15 17:45:12 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

static void	calculate_side_distances(double ray_pos_x, double ray_pos_y,
		double delta_dist_x, double delta_dist_y, int step_x, int step_y,
		double *side_dist_x, double *side_dist_y)
{
	if (step_x < 0)
		*side_dist_x = (ray_pos_x - floor(ray_pos_x)) * delta_dist_x;
	else
		*side_dist_x = (ceil(ray_pos_x) - ray_pos_x) * delta_dist_x;
	if (step_y < 0)
		*side_dist_y = (ray_pos_y - floor(ray_pos_y)) * delta_dist_y;
	else
		*side_dist_y = (ceil(ray_pos_y) - ray_pos_y) * delta_dist_y;
}

static void	draw_ray_pixel(t_data *data, double ray_pos_x, double ray_pos_y,
		int tile_size, int color)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = (int)(ray_pos_x * tile_size);
	pixel_y = (int)(ray_pos_y * tile_size);
	if (pixel_x >= 0 && pixel_x < MAP_WIDTH && pixel_y >= 0
		&& pixel_y < MAP_WIDTH)
		my_mlx_pixel_put(data, pixel_x, pixel_y, color);
}

static void	update_ray_position(double *ray_pos_x, double *ray_pos_y,
		double *side_dist_x, double *side_dist_y, double delta_dist_x,
		double delta_dist_y, int step_x, int step_y)
{
	if (*side_dist_x < *side_dist_y)
	{
		*side_dist_x += delta_dist_x;
		*ray_pos_x += step_x;
	}
	else
	{
		*side_dist_y += delta_dist_y;
		*ray_pos_y += step_y;
	}
}

void	draw_ray(myvar *var, t_data *data, double ray_dir_x, double ray_dir_y,
		int color)
{
	double	ray_pos_x;
	double	ray_pos_y;
	double	delta_dist_x;
	double	delta_dist_y;

	int (hit), (tile_size);
	int (step_x), (step_y);
	double (side_dist_x), (side_dist_y);
	tile_size = MAP_WIDTH / 20;
	ray_pos_x = data->pos_x;
	ray_pos_y = data->pos_y;
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	calculate_step_direction(ray_dir_x, ray_dir_y, &step_x, &step_y);
	calculate_side_distances(ray_pos_x, ray_pos_y, delta_dist_x, delta_dist_y,
		step_x, step_y, &side_dist_x, &side_dist_y);
	hit = 0;
	while (!hit)
	{
		draw_ray_pixel(data, ray_pos_x, ray_pos_y, tile_size, color);
		update_ray_position(&ray_pos_x, &ray_pos_y, &side_dist_x, &side_dist_y,
			delta_dist_x, delta_dist_y, step_x, step_y);
		if (is_wall(var, (int)ray_pos_x, (int)ray_pos_y))
			hit = 1;
	}
}

void	calcul_map_dimens(myvar *var)
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
