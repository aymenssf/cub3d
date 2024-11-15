/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:05:04 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/15 13:18:20 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

static void	hdl_up_down(t_data *data, double *new_pos_x, double *new_pos_y)
{
	double	move_step;

	move_step = data->move_speed * 3.0;
	if (key_down(data, KEY_UP) || key_down(data, KEY_W))
	{
		*new_pos_x += data->dir_x * move_step;
		*new_pos_y += data->dir_y * move_step;
	}
	if (key_down(data, KEY_DOWN) || key_down(data, KEY_S))
	{
		*new_pos_x -= data->dir_x * move_step;
		*new_pos_y -= data->dir_y * move_step;
	}
}

static void	hdl_strafe(t_data *data, double *new_pos_x, double *new_pos_y)
{
	double	strafe_step;

	strafe_step = data->move_speed * 1.5;
	if (key_down(data, KEY_D))
	{
		*new_pos_x -= data->plane_x * strafe_step;
		*new_pos_y -= data->plane_y * strafe_step;
	}
	if (key_down(data, KEY_A))
	{
		*new_pos_x += data->plane_x * strafe_step;
		*new_pos_y += data->plane_y * strafe_step;
	}
}

static void	hdl_r_rot(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(-data->rot_speed) - data->dir_y
		* sin(-data->rot_speed);
	data->dir_y = old_dir_x * sin(-data->rot_speed) + data->dir_y
		* cos(-data->rot_speed);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(-data->rot_speed) - data->plane_y
		* sin(-data->rot_speed);
	data->plane_y = old_plane_x * sin(-data->rot_speed) + data->plane_y
		* cos(-data->rot_speed);
}

static void	hdl_l_rot(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(data->rot_speed) - data->dir_y
		* sin(data->rot_speed);
	data->dir_y = old_dir_x * sin(data->rot_speed) + data->dir_y
		* cos(data->rot_speed);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(data->rot_speed) - data->plane_y
		* sin(data->rot_speed);
	data->plane_y = old_plane_x * sin(data->rot_speed) + data->plane_y
		* cos(data->rot_speed);
}

void	read_keys(myvar *var)
{
	t_data	*data;
	double	new_pos_x;
	double	new_pos_y;

	data = var->data;
	new_pos_x = data->pos_x;
	new_pos_y = data->pos_y;
	hdl_up_down(data, &new_pos_x, &new_pos_y);
	hdl_strafe(data, &new_pos_x, &new_pos_y);
	if (is_valid_position(var, new_pos_x, data->pos_y))
		data->pos_x = new_pos_x;
	if (is_valid_position(var, data->pos_x, new_pos_y))
		data->pos_y = new_pos_y;
	if (key_down(data, KEY_RIGHT))
		hdl_r_rot(data);
	if (key_down(data, KEY_LEFT))
		hdl_l_rot(data);
	if (key_down(data, KEY_ESC))
		// close_window(var);
		destroy(data);
}
