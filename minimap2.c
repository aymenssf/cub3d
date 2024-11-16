/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:37:50 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/16 21:38:14 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_fov_ray(myvar *var, double angle, double start_pos[2])
{
	double	r;
	double	coord[2];
	int		map_pos[2];

	r = 0;
	var->data->color_mini = 0x00FF00;
	while (r <= var->radius)
	{
		coord[0] = start_pos[0] + (cos(angle) * r);
		coord[1] = start_pos[1] + (sin(angle) * r);
		map_pos[0] = (int)((var->data->pos_x + (coord[0] - start_pos[0])
					/ TILE_SIZE));
		map_pos[1] = (int)((var->data->pos_y + (coord[1] - start_pos[1])
					/ TILE_SIZE));
		if ((int)coord[0] < screen_width && (int)coord[1] < screen_height
			&& (int)coord[0] >= 0 && (int)coord[1] >= 0)
			my_mlx_pixel_put_transparent(var->data, (int)coord[0],
				(int)coord[1], 0.1f);
		if (is_wall(var, map_pos[0], map_pos[1]))
			break ;
		r += 1.0;
	}
}

void	draw_filled_fov(myvar *var, double center_pos[2])
{
	double	angle;
	double	fov;
	double	start_angle;
	double	end_angle;

	fov = 60 * (M_PI / 180.0);
	start_angle = atan2(var->data->dir_y, var->data->dir_x) - fov / 2;
	end_angle = start_angle + fov;
	angle = start_angle;
	var->radius = 3 * TILE_SIZE;
	while (angle <= end_angle)
	{
		cast_fov_ray(var, angle, center_pos);
		angle += 0.02;
	}
}

int	get_map_color(char tile)
{
	if (tile == '1')
		return (0x808080);
	else if (tile == '0')
		return (0xFFFFFF);
	else
		return (0x808080);
}
