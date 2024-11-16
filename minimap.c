/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:48:10 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/16 22:15:21 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put_transparent(t_data *data, int x, int y, float alpha)
{
	unsigned int (*dst), (src_rgb), (dst_rgb), (r), (g), (b);
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		dst = (unsigned int *)(data->addr + (y * data->line_length + x
					* (data->bits_per_pixel / 8)));
		src_rgb = data->color_mini & 0x00FFFFFF;
		dst_rgb = *dst & 0x00FFFFFF;
		r = ((src_rgb >> 16) & 0xFF) * alpha + ((dst_rgb >> 16) & 0xFF) * (1
				- alpha);
		g = ((src_rgb >> 8) & 0xFF) * alpha + ((dst_rgb >> 8) & 0xFF) * (1
				- alpha);
		b = (src_rgb & 0xFF) * alpha + (dst_rgb & 0xFF) * (1 - alpha);
		*dst = (r << 16) | (g << 8) | b;
	}
}

void	draw_mini_square(t_data *data, double x, double y)
{
	int	rounded_x;
	int	rounded_y;
	int	i;
	int	j;

	rounded_x = (int)(x);
	rounded_y = (int)(y);
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if (rounded_x + i < SCREEN_WIDTH && rounded_y + j < SCREEN_HEIGHT
				&& rounded_x + i >= 0 && rounded_y + j >= 0)
				my_mlx_pixel_put_transparent(data, rounded_x + i, rounded_y + j,
					0.65f);
			j++;
		}
		i++;
	}
}

void	draw_mini_player(t_data *data, double x, double y)
{
	int	rounded_x;
	int	rounded_y;
	int	i;
	int	j;
	int	player_size;

	player_size = 6;
	data->color_mini = 0xFF0000;
	rounded_x = (int)(x - player_size / 2);
	rounded_y = (int)(y - player_size / 2);
	i = -1;
	while (++i < player_size)
	{
		j = -1;
		while (++j < player_size)
		{
			if (rounded_x + i < SCREEN_WIDTH && rounded_y + j < SCREEN_HEIGHT
				&& rounded_x + i >= 0 && rounded_y + j >= 0)
				my_mlx_pixel_put_transparent(data, rounded_x + i, rounded_y + j,
					0.9f);
		}
	}
}

void	draw_map_row(t_myvar *var, int y)
{
	double	screen_pos[2];

	int (x), (map_pos[2]);
	x = 0;
	while (x <= MINI_MAP_SIZE * 2)
	{
		map_pos[0] = var->base_x + x;
		map_pos[1] = var->base_y + y;
		screen_pos[0] = x * TILE_SIZE - var->offset_x;
		screen_pos[1] = y * TILE_SIZE - var->offset_y;
		if (map_pos[1] >= 0 && map_pos[1] < var->data->map_rows
			&& map_pos[0] >= 0 && map_pos[0] < var->data->map_cols
			&& (size_t)map_pos[0] < ft_strlen(var->s[map_pos[1]]))
		{
			var->data->color_mini
				= get_map_color(var->s[map_pos[1]][map_pos[0]]);
			draw_mini_square(var->data, screen_pos[0], screen_pos[1]);
		}
		else
		{
			var->data->color_mini = get_map_color('1');
			draw_mini_square(var->data, screen_pos[0], screen_pos[1]);
		}
		x++;
	}
}

void	ft_draw_mini_map(t_myvar *var)
{
	double	center_pos[2];
	int		y;

	var->offset_x = (var->data->pos_x - floor(var->data->pos_x)) * TILE_SIZE;
	var->offset_y = (var->data->pos_y - floor(var->data->pos_y)) * TILE_SIZE;
	var->base_x = (int)floor(var->data->pos_x) - MINI_MAP_SIZE;
	var->base_y = (int)floor(var->data->pos_y) - MINI_MAP_SIZE;
	y = 0;
	while (y <= MINI_MAP_SIZE * 2)
	{
		draw_map_row(var, y);
		y++;
	}
	center_pos[0] = MINI_MAP_SIZE * TILE_SIZE;
	center_pos[1] = MINI_MAP_SIZE * TILE_SIZE;
	draw_filled_fov(var, center_pos);
	draw_mini_player(var->data, center_pos[0], center_pos[1]);
}
