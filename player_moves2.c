/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:07:40 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/16 22:15:21 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	key_press(int keycode, t_myvar *var)
{
	if (keycode == KEY_ESC)
		close_window(var);
	var->data->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	data->keys[keycode] = 0;
	return (0);
}

int	key_down(t_data *data, int keycode)
{
	return (data->keys[keycode]);
}
