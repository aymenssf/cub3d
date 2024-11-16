/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdl_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:40:14 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/16 22:15:21 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

static void	handle_mouse_position(t_data *data)
{
	if (data->mouse_x < 50)
	{
		data->mouse_x = 50;
		mlx_mouse_move(data->mlx, data->win, data->mouse_x, data->mouse_y);
	}
	else if (data->mouse_x > SCREEN_WIDTH - 50)
	{
		data->mouse_x = SCREEN_WIDTH - 50;
		mlx_mouse_move(data->mlx, data->win, data->mouse_x, data->mouse_y);
	}
	if (data->mouse_x < 50 || data->mouse_x > SCREEN_WIDTH - 50)
	{
		mlx_mouse_move(data->mlx, data->win, SCREEN_WIDTH / 2, data->mouse_y);
		data->mouse_x = SCREEN_WIDTH / 2;
	}
}

static void	update_view(t_data *data, int hold)
{
	double (old_dir_x), (old_plane_x), (rotation_speed);
	if (hold == 0 || !(data->mouse_x > 0 && data->mouse_x < SCREEN_WIDTH
			&& data->mouse_y > 0 && data->mouse_y < SCREEN_HEIGHT))
		return ;
	rotation_speed = (double)(abs(hold))*0.002;
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

int	handle_mouse(t_myvar *var)
{
	t_data		*data;
	static int	first_time = 1;
	static int	prev_x = -1;
	int			hold;

	if (!var || !var->data || !var->data->mlx || !var->data->win)
		return (garbage_collector(var, free), 1);
	data = var->data;
	if (first_time)
	{
		mlx_mouse_move(data->mlx, data->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT
			/ 2);
		data->mouse_x = SCREEN_WIDTH / 2;
		data->mouse_y = SCREEN_HEIGHT / 2;
		first_time = 0;
		return (0);
	}
	prev_x = data->mouse_x;
	if (mlx_mouse_get_pos(data->mlx, data->win, &data->mouse_x,
			&data->mouse_y) == -1)
		return (1);
	hold = data->mouse_x - prev_x;
	handle_mouse_position(data);
	update_view(data, hold);
	return (0);
}
