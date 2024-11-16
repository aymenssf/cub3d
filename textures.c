/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:59:05 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/16 22:15:21 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	load_textures_hands(void *mlx, t_myvar *var)
{
	var->texture_hands.img = mlx_xpm_file_to_image(mlx, "file.xpm",
			&var->texture_hands.width, &var->texture_hands.height);
	var->texture_hands.addr = mlx_get_data_addr(var->texture_hands.img,
			&var->texture_hands.bits_per_pixel, &var->texture_hands.line_length,
			&var->texture_hands.endian);
}

void	load_textures(void *mlx, t_myvar *var)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		var->texturess[i].img = mlx_xpm_file_to_image(mlx, var->textures[i],
				&var->texturess[i].width, &var->texturess[i].height);
		var->texturess[i].addr = mlx_get_data_addr(var->texturess[i].img,
				&var->texturess[i].bits_per_pixel,
				&var->texturess[i].line_length, &var->texturess[i].endian);
	}
}

void	draw_hands(t_data *data, t_myvar *var)
{
	int				vertical_offset;
	int				y;
	int				x;
	unsigned int	color;

	vertical_offset = 0;
	if (1)
		vertical_offset = sin(get_time() * 0.01) * 10.0;
	y = 0;
	while (y < 630)
	{
		x = 0;
		while (x < 630)
		{
			color = (unsigned int)get_texture_hands_color(var, x, y);
			if (color != 0xFF000000)
			{
				my_mlx_pixel_put(data, (SCREEN_WIDTH - 650 + vertical_offset)
					/ 2 + x, (SCREEN_HEIGHT - 370 + vertical_offset) + y,
					color);
			}
			x++;
		}
		y++;
	}
}

int	get_texture_color(t_myvar *var, int type_wall, int x, int y)
{
	char	*pixel;

	pixel = var->texturess[type_wall].addr + (y
			* var->texturess[type_wall].line_length + x * 4);
	return (*(unsigned int *)pixel);
}

int	get_texture_hands_color(t_myvar *var, int x, int y)
{
	int	offset;

	if (x >= 0 && x < var->texture_hands.width && y >= 0
		&& y < var->texture_hands.height)
	{
		offset = (y * var->texture_hands.line_length) + (x
				* (var->texture_hands.bits_per_pixel / 8));
		return (*(unsigned int *)(var->texture_hands.addr + offset));
	}
	else
	{
		return (0xFF000000);
	}
}
