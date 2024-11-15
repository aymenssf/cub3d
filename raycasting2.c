/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:58:26 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/15 17:46:27 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	init_ray(t_data *data, int x, t_ray *ray)
{
	double	ray_dir_x;
	double	ray_dir_y;

	ray->camera_x = 2 * x / (double)screen_width - 1;
	ray_dir_x = data->dir_x + data->plane_x * ray->camera_x;
	ray_dir_y = data->dir_y + data->plane_y * ray->camera_x;
	ray->map_x = (int)data->pos_x;
	ray->map_y = (int)data->pos_y;
	if (ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray_dir_x);
	if (ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray_dir_y);
	ray->hit = 0;
}

void	calculate_dist(t_data *data, t_ray *ray, double ray_dir_x,
		double ray_dir_y)
{
	if (ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->pos_x) * ray->delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->pos_y) * ray->delta_dist_y;
	}
}

void	dda_algo(t_ray *ray, myvar *var)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
			if (ray->step_x == -1)
				ray->wall_orientation = 2;
			else
				ray->wall_orientation = 3;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
			if (ray->step_y == -1)
				ray->wall_orientation = 1;
			else
				ray->wall_orientation = 0;
		}
		if (is_wall(var, ray->map_x, ray->map_y))
			ray->hit = 1;
	}
}

void	draw_v_line(t_data *data, int x, t_ray *ray, myvar *var,
		double ray_dir_x, double ray_dir_y)
{
	int		color;
	double	wall_x;

	int (y), (i);
	int (tex_x), (tex_y);
	y = ray->draw_start;
	i = -1;
	while (++i < y)
		my_mlx_pixel_put(data, x, i, var->floor);
	i = ray->draw_end;
	while (i < screen_height)
	{
		my_mlx_pixel_put(data, x, i, var->cel);
		i++;
	}
	wall_x = 0;
	if (ray->map_y >= 0 && ray->map_y < var->data->map_rows && ray->map_x >= 0
		&& ray->map_x < var->data->map_cols
		&& (size_t)ray->map_x < ft_strlen(var->s[ray->map_y]))
	{
		if (ray->side == 0)
			wall_x = data->pos_y + ray->perp_wall_dist * ray_dir_y;
		else
			wall_x = data->pos_x + ray->perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * var->texturess[ray->wall_orientation].width);
		while (y < ray->draw_end)
		{
			tex_y = ((y - ray->draw_start)
					* var->texturess[ray->wall_orientation].height)
				/ ray->line_height;
			color = get_texture_color(var, ray->wall_orientation, tex_x, tex_y);
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
	}
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
