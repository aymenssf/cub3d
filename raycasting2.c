/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:58:26 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/17 13:26:03 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

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

void	dda_algo(t_ray *ray, t_myvar *var)
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

void	draw_floor_ceiling(t_data *data, int x, t_ray *ray, t_myvar *var)
{
	int	i;

	i = -1;
	while (++i < ray->draw_start)
		my_mlx_pixel_put(data, x, i, var->floor);
	i = ray->draw_end;
	while (i < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(data, x, i, var->cel);
		i++;
	}
}

void	draw_wall_texture(t_data *data, int x, t_ray *ray, t_myvar *var)
{
	int (tex_x), (tex_y), (y), (color);
	double (step), (tex_pos), (wall_x);
	if (ray->side == 0)
		wall_x = data->pos_y + ray->perp_wall_dist * data->ray_dir_y;
	else
		wall_x = data->pos_x + ray->perp_wall_dist * data->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * var->texturess[ray->wall_orientation].width);
	step = 1.0 * var->texturess[ray->wall_orientation].height
		/ ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2)
		* step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (var->texturess[ray->wall_orientation].height
				- 1);
		tex_pos += step;
		color = get_texture_color(var, ray->wall_orientation, tex_x, tex_y);
		my_mlx_pixel_put(data, x, y, color);
		y++;
	}
}

void	draw_v_line(t_data *data, int x, t_ray *ray, t_myvar *var)
{
	draw_floor_ceiling(data, x, ray, var);
	if (ray->map_y < 0 || ray->map_y >= var->data->map_rows || ray->map_x < 0
		|| ray->map_x >= var->data->map_cols
		|| (size_t)ray->map_x >= ft_strlen(var->s[ray->map_y]))
		return ;
	draw_wall_texture(data, x, ray, var);
}
