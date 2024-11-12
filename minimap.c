/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:48:10 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/12 22:48:12 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put_transparent(t_data *data, int x, int y, int color,
		float alpha)
{
	unsigned int	*dst;
	unsigned int	src_rgb;
	unsigned int	dst_rgb;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (x >= 0 && x < screen_width && y >= 0 && y < screen_height)
	{
		dst = (unsigned int *)(data->addr + (y * data->line_length + x
					* (data->bits_per_pixel / 8)));
		src_rgb = color & 0x00FFFFFF;
		dst_rgb = *dst & 0x00FFFFFF;
		r = ((src_rgb >> 16) & 0xFF) * alpha + ((dst_rgb >> 16) & 0xFF) * (1
				- alpha);
		g = ((src_rgb >> 8) & 0xFF) * alpha + ((dst_rgb >> 8) & 0xFF) * (1
				- alpha);
		b = (src_rgb & 0xFF) * alpha + (dst_rgb & 0xFF) * (1 - alpha);
		*dst = (r << 16) | (g << 8) | b;
	}
}

void	draw_mini_square(t_data *data, double x, double y, int color)
{
	float	alpha;
	int		rounded_x;
	int		rounded_y;

	alpha = 0.65f;
	rounded_x = (int)(x);
	rounded_y = (int)(y);
	int i = 0;
	while (i < TILE_SIZE)
	{
		int j = 0;
		while (j < TILE_SIZE)
		{
			if (rounded_x + i < screen_width && rounded_y + j < screen_height
				&& rounded_x + i >= 0 && rounded_y + j >= 0)
				my_mlx_pixel_put_transparent(data, rounded_x + i, rounded_y + j,
					color, alpha);
			j++;
		}
		i++;
	}
}

void	draw_mini_player(t_data *data, double x, double y)
{
	int		player_size;
	float	alpha;
	int		color;
	int		rounded_x;
	int		rounded_y;

	player_size = 6;
	alpha = 0.9f;
	color = 0xFF0000;
	rounded_x = (int)(x - player_size / 2);
	rounded_y = (int)(y - player_size / 2);
	int i = 0;
	while (i < player_size)
	{
		int j = 0;
		while (j < player_size)
		{
			if (rounded_x + i < screen_width && rounded_y + j < screen_height
				&& rounded_x + i >= 0 && rounded_y + j >= 0)
				my_mlx_pixel_put_transparent(data, rounded_x + i, rounded_y + j,
					color, alpha);
			j++;
		}
		i++;
	}
}

void	draw_filled_fov(myvar *var, double start_x, double start_y,
		double start_angle, double end_angle, int radius)
{
	int		color;
	float	alpha;
	double	angle_step;
	int		map_x;
	int		map_y;
	double	x;
	double	y;
	int		rounded_x;
	int		rounded_y;

	color = 0x00FF00;
	alpha = 0.1f;
	angle_step = 0.02;
	double angle = start_angle;
	while (angle <= end_angle)
	{
		double r = 0;
		while (r <= radius)
		{
			x = start_x + (cos(angle) * r);
			y = start_y + (sin(angle) * r);
			map_x = (int)((var->data->pos_x + (x - start_x) / TILE_SIZE));
			map_y = (int)((var->data->pos_y + (y - start_y) / TILE_SIZE));
			rounded_x = (int)(x);
			rounded_y = (int)(y);
			if (rounded_x < screen_width && rounded_y < screen_height
				&& rounded_x >= 0 && rounded_y >= 0)
			{
				my_mlx_pixel_put_transparent(var->data, rounded_x, rounded_y,
					color, alpha);
			}
			if (map_y >= 0 && map_y < var->data->map_rows && map_x >= 0
				&& map_x < var->data->map_cols
				&& (size_t)map_x < ft_strlen(var->s[map_y]))
			{
				if (var->s[map_y][map_x] == '1')
					break ;
			}
			r += 1.0;
		}
		angle += angle_step;
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

void	ft_draw_mini_map(myvar *var)
{
	t_data	*data;
	double	player_x;
	double	player_y;
	double	offset_x;
	double	offset_y;
	int		base_x;
	int		base_y;
	int		map_x;
	int		map_y;
	double	screen_x;
	double	screen_y;
	double	center_x;
	double	center_y;
	double	fov;
	double	player_angle;
	double	start_angle;
	double	end_angle;

	data = var->data;
	player_x = data->pos_x;
	player_y = data->pos_y;
	offset_x = (player_x - floor(player_x)) * TILE_SIZE;
	offset_y = (player_y - floor(player_y)) * TILE_SIZE;
	base_x = (int)floor(player_x) - MINI_MAP_SIZE;
	base_y = (int)floor(player_y) - MINI_MAP_SIZE;
	int y = 0;
	while (y <= MINI_MAP_SIZE * 2)
	{
		int x = 0;
		while (x <= MINI_MAP_SIZE * 2)
		{
			map_x = base_x + x;
			map_y = base_y + y;
			screen_x = x * TILE_SIZE - offset_x;
			screen_y = y * TILE_SIZE - offset_y;
			if (map_y >= 0 && map_y < var->data->map_rows && map_x >= 0
				&& map_x < var->data->map_cols
				&& (size_t)map_x < ft_strlen(var->s[map_y]))
			{
				draw_mini_square(data, screen_x, screen_y,
					get_map_color(var->s[map_y][map_x]));
			}
			else
				draw_mini_square(data, screen_x, screen_y, get_map_color('1'));
			x++;
		}
		y++;
	}
	center_x = MINI_MAP_SIZE * TILE_SIZE;
	center_y = MINI_MAP_SIZE * TILE_SIZE;
	fov = 60 * (M_PI / 180.0);
	player_angle = atan2(data->dir_y, data->dir_x);
	start_angle = player_angle - fov / 2;
	end_angle = player_angle + fov / 2;
	draw_filled_fov(var, center_x, center_y, start_angle, end_angle, 3
		* TILE_SIZE);
	draw_mini_player(data, center_x, center_y);
}
