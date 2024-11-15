/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:50:05 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/15 21:50:24 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	update_frame_data(t_data *data)
{
	double	time;

	time = get_time();
	data->move_speed = ((time - data->old_time) / 1000.0) * 1.5;
	data->rot_speed = data->move_speed;
	data->old_time = time;
}

void	update_display(t_data *data, myvar *var)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	draw_hands(data, var);
	ft_draw_mini_map(var);
	handle_mouse(var);
	mlx_do_sync(data->mlx);
}


