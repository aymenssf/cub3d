/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:40:26 by aassaf            #+#    #+#             */
/*   Updated: 2024/09/30 04:00:29 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int map2d[21][21] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,1},
    {1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1},
    {1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1},
    {1,1,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1},
    {1,1,0,0,0,0,0,0,1,1,0,1,0,1,1,1,1,1,1,1},
    {1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double get_time() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (double)tv.tv_sec * 1000.0 + (double)tv.tv_usec / 1000.0;
}

int is_wall(int x, int y)
{
	if (x < 0 || x >= 20 || y < 0 || y >= 14)
		return (1);
	return (map2d[y][x]);
}

int is_valid_position(double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;

    return !is_wall(map_x, map_y);
}


void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int close_window(t_data *data)
{
	(void)data;
	// mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

int key_press(int keycode, t_data *data)
{
	if(keycode == KEY_ESC)
		close_window(data);
	// if (keycode < 256)
	data->keys[keycode] = 1;
	return 0;
}

int key_release(int keycode, t_data *data)
{
	// if (keycode < 256)
	data->keys[keycode] = 0;
	return 0;
}

int keyDown(t_data *data, int keycode)
{
	return data->keys[keycode];
}

void read_keys(t_data *data)
{
    double moveStep = data->move_speed * 3.0; // Increased movement speed
    double newPosX = data->pos_x;
    double newPosY = data->pos_y;

    if (keyDown(data, KEY_UP) || keyDown(data, KEY_W))
    {
        newPosX += data->dir_x * moveStep;
        newPosY += data->dir_y * moveStep;
    }
    if (keyDown(data, KEY_DOWN) || keyDown(data, KEY_S))
    {
        newPosX -= data->dir_x * moveStep;
        newPosY -= data->dir_y * moveStep;
    }
    if (is_valid_position(newPosX, data->pos_y))
        data->pos_x = newPosX;
    if (is_valid_position(data->pos_x, newPosY))
        data->pos_y = newPosY;
    if (keyDown(data, KEY_RIGHT) || keyDown(data, KEY_D))
    {
        double oldDirX = data->dir_x;
        data->dir_x = data->dir_x * cos(-data->rot_speed) - data->dir_y * sin(-data->rot_speed);
        data->dir_y = oldDirX * sin(-data->rot_speed) + data->dir_y * cos(-data->rot_speed);
        double oldPlaneX = data->plane_x;
        data->plane_x = data->plane_x * cos(-data->rot_speed) - data->plane_y * sin(-data->rot_speed);
        data->plane_y = oldPlaneX * sin(-data->rot_speed) + data->plane_y * cos(-data->rot_speed);
    }
    if (keyDown(data, KEY_LEFT) || keyDown(data, KEY_A))
    {
        double oldDirX = data->dir_x;
        data->dir_x = data->dir_x * cos(data->rot_speed) - data->dir_y * sin(data->rot_speed);
        data->dir_y = oldDirX * sin(data->rot_speed) + data->dir_y * cos(data->rot_speed);
        double oldPlaneX = data->plane_x;
        data->plane_x = data->plane_x * cos(data->rot_speed) - data->plane_y * sin(data->rot_speed);
        data->plane_y = oldPlaneX * sin(data->rot_speed) + data->plane_y * cos(data->rot_speed);
    }

    if (keyDown(data, KEY_ESC))
    {
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
}

void init_ray(t_data *data, int x, t_ray *ray)
{
	ray->camera_x = 2 * x / (double)screen_width - 1;
	double ray_dir_x = data->dir_x + data->plane_x * ray->camera_x;
	double ray_dir_y = data->dir_y + data->plane_y * ray->camera_x;
	ray->map_x = (int)data->pos_x;
	ray->map_y = (int)data->pos_y;
	if(ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray_dir_x);
	if(ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray_dir_y);
	ray->hit = 0;
}

void	calculate_dist(t_data *data, t_ray *ray, double ray_dir_x, double ray_dir_y)
{
	if (ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->pos_x) * ray->delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->pos_y) * ray->delta_dist_y;
	}
}

void	dda_algo(t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (is_wall(ray->map_x, ray->map_y))
			ray->hit = 1;
	}
}

void	calcul_wall_dist(t_data *data, t_ray *ray, double ray_dir_x, double ray_dir_y)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->pos_x + (1 - ray->step_x) / 2) / ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->pos_y + (1 - ray->step_y) / 2) / ray_dir_y;
	ray->line_height = (int)(screen_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + screen_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + screen_height / 2;
	if (ray->draw_end >= screen_height)
		ray->draw_end = screen_height - 1;
}

void	draw_v_line(t_data *data, int x, t_ray *ray)
{
	int	y;
	int	color;

	if (ray->side == 1)
		color = 0xFF0000;
	else
		color = 0x0000FF;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		my_mlx_pixel_put(data, x, y, color);
		y++;
	}
}

void print_player_position(t_data *data)
{
    printf("Player position: (%f, %f)\n", data->pos_x, data->pos_y);
    printf("Player map position: (%d, %d)\n", (int)data->pos_x, (int)data->pos_y);
    printf("Is wall at player position: %d\n", is_wall((int)data->pos_x, (int)data->pos_y));
}
int raycasting_loop(t_data *data)
{
	double  time;
	double  frame_time;
	int     x;
	t_ray   ray;
	double  ray_dir_x;
	double  ray_dir_y;

	time = get_time();
	frame_time = (time - data->old_time) / 1000.0;
	data->old_time = time;
	data->move_speed = frame_time * 2.0;
	data->rot_speed = frame_time * 3.0;
	read_keys(data);
	print_player_position(data);
	memset(data->addr, 0, screen_width * screen_height * (data->bits_per_pixel / 8));
	x = 0;
	while (x < screen_width)
	{
		init_ray(data, x, &ray);
		ray_dir_x = data->dir_x + data->plane_x * ray.camera_x;
		ray_dir_y = data->dir_y + data->plane_y * ray.camera_x;
		calculate_dist(data, &ray, ray_dir_x, ray_dir_y);
		dda_algo(&ray);
		calcul_wall_dist(data, &ray, ray_dir_x, ray_dir_y);
		draw_v_line(data, x, &ray);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}


int main()
{
	t_data *data;
	data = (t_data *)malloc(sizeof(t_data));
	if	(!data)
		return (1);
	data->pos_x = 2.0;
	data->pos_y = 5.0;
	data->dir_x = -1;
	data->dir_y = 0;
	data->plane_x = 0;
	data->plane_y = 0.66;
	memset(data->keys, 0, sizeof(data->keys));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, screen_width, screen_height, "Raycaster");
	data->img = mlx_new_image(data->mlx, screen_width, screen_height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	mlx_hook(data->win, 2, 1L<<0, key_press, data);
	mlx_hook(data->win, 3, 1L<<1, key_release, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, raycasting_loop, data);
	mlx_loop(data->mlx);
	// print_player_position(data);
	return (0);
}
