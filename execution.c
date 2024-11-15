/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:40:26 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/15 16:58:12 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	is_valid_position(myvar *var, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= var->data->map_cols || map_y < 0
		|| map_y >= var->data->map_rows)
		return (0);
	return (var->s[map_y][map_x] == '0');
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < screen_width && y >= 0 && y < screen_height)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}

void	calcul_wall_dist(t_data *data, t_ray *ray, double ray_dir_x,
		double ray_dir_y)
{
	double	scaling_factor;

	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->pos_x + (1 - ray->step_x) / 2)
			/ ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->pos_y + (1 - ray->step_y) / 2)
			/ ray_dir_y;
	scaling_factor = 2.5;
	ray->line_height = (int)(screen_height / ray->perp_wall_dist
			/ scaling_factor);
	ray->draw_start = -ray->line_height / 2 + screen_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + screen_height / 2;
	if (ray->draw_end >= screen_height)
		ray->draw_end = screen_height - 1;
}

int	raycasting_loop(myvar *var)
{
	t_data	*data;
	double	time;
	double	frame_time;
	int		x;
	t_ray	ray;
	double	ray_dir_x;
	double	ray_dir_y;

	data = var->data;
	time = get_time();
	frame_time = (time - data->old_time) / 1000.0;
	data->old_time = time;
	data->move_speed = frame_time * 1.5;
	data->rot_speed = frame_time * 1.5;
	read_keys(var);
	memset(data->addr, 0, screen_width * screen_height * (data->bits_per_pixel
			/ 8));
	x = 0;
	while (x < screen_width)
	{
		init_ray(data, x, &ray);
		ray_dir_x = data->dir_x + data->plane_x * ray.camera_x;
		ray_dir_y = data->dir_y + data->plane_y * ray.camera_x;
		calculate_dist(data, &ray, ray_dir_x, ray_dir_y);
		dda_algo(&ray, var);
		calcul_wall_dist(data, &ray, ray_dir_x, ray_dir_y);
		draw_v_line(data, x, &ray, var, ray_dir_x, ray_dir_y);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	draw_hands(data, var);
	ft_draw_mini_map(var);
	 handle_mouse(var);
	mlx_do_sync(data->mlx);
	return (0);
}

void	execute(myvar *var)
{
	t_data	*data;

	data = var->data;
	data->pos_x = var->player.x + 0.5;
	data->pos_y = var->player.y + 0.5;
	memset(data->keys, 0, sizeof(data->keys));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, screen_width, screen_height, "CUB3D");
	load_textures(data->mlx, var);
	load_textures_hands(data->mlx, var);
	data->img = mlx_new_image(data->mlx, screen_width, screen_height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	mlx_hook(data->win, 2, 1L << 0, key_press, var);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->win, 17, 0, close_window, var);
	mlx_loop_hook(data->mlx, raycasting_loop, var);
	mlx_loop(data->mlx);
}
