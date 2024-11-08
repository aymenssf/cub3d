/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:47:36 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/08 11:57:51 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	get_2d_map_color(int wall_type, int orientation)
{
	if (wall_type == 1)
	{
		if (orientation == 0)
			return (0x00FF00);
		else if (orientation == 1)
			return (0xFF0000);
		else if (orientation == 2)
			return (0xFFFF00);
		else if (orientation == 3)
			return (0x0000FF);
		return (0xFFFFFF);
	}
	return (0x000000);
}

static int	get_wall_orientation(myvar *var, int x, int y)
{
	if (y > 0 && (size_t)x < ft_strlen(var->s[y - 1]) && var->s[y
			- 1][x] == '0')
		return (1);
	if (y < var->data->map_rows - 1 && (size_t)x < ft_strlen(var->s[y + 1])
		&& var->s[y + 1][x] == '0')
		return (0);
	if (x > 0 && var->s[y][x - 1] == '0')
		return (2);
	if (x < var->data->map_cols - 1 && var->s[y][x + 1] == '0')
		return (3);
	return (-1);
}

static void	draw_map_tile(myvar *var, int x, int y, int mini_size)
{
	int	wall_type;
	int	orientation;
	int	color;

	int (px), (py);
	if ((size_t)x >= ft_strlen(var->s[y]))
		return ;
	wall_type = var->s[y][x] - '0';
	if (wall_type == 1)
		orientation = get_wall_orientation(var, x, y);
	else
		orientation = -1;
	color = get_2d_map_color(wall_type, orientation);
	py = 0;
	while (py < mini_size)
	{
		px = 0;
		while (px < mini_size)
		{
			my_mlx_pixel_put(var->data, var->map_offset + x * mini_size + px,
				var->map_offset + y * mini_size + py, color);
			px++;
		}
		py++;
	}
}

static void	draw_player_position(t_data *data, int mini_size, int map_offset)
{
	int	player_x;
	int	player_y;
	int	px;
	int	py;

	player_x = (int)(data->pos_x * mini_size);
	player_y = (int)(data->pos_y * mini_size);
	px = -2;
	while (px <= 2)
	{
		py = -2;
		while (py <= 2)
		{
			my_mlx_pixel_put(data, map_offset + player_x + px, map_offset
				+ player_y + py, 0xFF0000);
			py++;
		}
		px++;
	}
}

void	draw_2d_map(myvar *var)
{
	int	mini_size;
	int	y;
	int	x;

	mini_size = MAP_WIDTH / 20;
	var->map_offset = 10;
	y = 0;
	while (y < var->data->map_rows)
	{
		x = 0;
		while (x < var->data->map_cols)
		{
			draw_map_tile(var, x, y, mini_size);
			x++;
		}
		y++;
	}
	draw_player_position(var->data, mini_size, var->map_offset);
}
