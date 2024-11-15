/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdl_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:40:14 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/15 16:57:01 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	handle_mouse(myvar *var)
{
	t_data		*data;
	static int	first_time = 1;
	static int	prev_x = -1;
	int			hold;
	double		rotation_speed;
	double		old_dir_x;
	double		old_plane_x;

	if (!var || !var->data || !var->data->mlx || !var->data->win)
		return (garbage_collector(var, free), 1);
	data = var->data;
	if (first_time)
	{
		mlx_mouse_move(data->mlx, data->win, screen_width / 2, screen_height
			/ 2);
		data->mouse_x = screen_width / 2;
		data->mouse_y = screen_height / 2;
		first_time = 0;
		return (0);
	}
	prev_x = data->mouse_x;
	if (mlx_mouse_get_pos(data->mlx, data->win, &data->mouse_x,
			&data->mouse_y) == -1)
		return (1);
	hold = data->mouse_x - prev_x;
	if (data->mouse_x < 50)
	{
		data->mouse_x = 50;
		mlx_mouse_move(data->mlx, data->win, data->mouse_x, data->mouse_y);
	}
	else if (data->mouse_x > screen_width - 50)
	{
		data->mouse_x = screen_width - 50;
		mlx_mouse_move(data->mlx, data->win, data->mouse_x, data->mouse_y);
	}
	if (data->mouse_x > 0 && data->mouse_x < screen_width && data->mouse_y > 0
		&& data->mouse_y < screen_height)
	{
		if (hold != 0)
		{
			rotation_speed = (double)(abs(hold)) *0.002;
			if (hold < 0)
				rotation_speed = -rotation_speed;
			old_dir_x = data->dir_x;
			data->dir_x = data->dir_x * cos(rotation_speed) - data->dir_y
				* sin(rotation_speed);
			data->dir_y = old_dir_x * sin(rotation_speed) + data->dir_y
				* cos(rotation_speed);
			old_plane_x = data->plane_x;
			data->plane_x = data->plane_x * cos(rotation_speed) - data->plane_y
				* sin(rotation_speed);
			data->plane_y = old_plane_x * sin(rotation_speed) + data->plane_y
				* cos(rotation_speed);
		}
		if (data->mouse_x < 50 || data->mouse_x > screen_width - 50)
		{
			mlx_mouse_move(data->mlx, data->win, screen_width / 2,
				data->mouse_y);
			data->mouse_x = screen_width / 2;
		}
	}
	return (0);
}
