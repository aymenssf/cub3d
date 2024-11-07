/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:40:26 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/07 03:21:51 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/cub3d.h"
const int wall_colors[5] = {0x000000, 0x00FF00, 0xFF0000, 0x0000FF, 0xFFFF00};
int map2d[21][21] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,1},
    {1,0,3,3,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,1},
    {1,0,0,3,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,0,2,2,0,0,0,0,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,1,1,1,0,1},
    {1,1,1,1,0,3,3,3,3,3,3,3,3,3,0,1,1,1,0,1},
    {1,1,1,1,0,3,3,3,3,3,3,3,3,3,0,1,1,1,0,1},
    {1,1,0,0,0,0,0,0,3,3,0,2,0,2,0,3,3,3,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,1},
    {1,1,0,0,0,0,0,0,3,3,0,2,0,2,3,3,3,3,3,3},
    {1,1,1,1,0,3,3,3,3,3,0,2,0,2,3,3,3,3,3,3},
    {1,1,1,1,0,4,4,4,4,4,0,4,0,4,4,4,4,4,4,4},
    {1,1,1,1,0,4,4,4,4,4,0,4,0,4,4,4,4,4,4,4},
    {1,1,1,1,0,4,4,4,4,4,0,4,0,4,4,4,4,4,4,4},
    {1,1,1,1,0,4,4,4,4,4,0,4,0,4,4,4,4,4,4,4},
    {1,1,1,1,0,4,4,4,4,4,0,4,0,4,4,4,4,4,4,4},
    {1,1,1,1,0,4,4,4,4,4,0,4,0,4,4,4,4,4,4,4},
    {1,1,1,1,0,4,4,4,4,4,0,4,0,4,4,4,4,4,4,4},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double get_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (double)tv.tv_sec * 1000.0 + (double)tv.tv_usec / 1000.0;
}

int is_wall(myvar *var, int x, int y)
{
	(void)var;
	if (x < 0 || x >= 20 || y < 0 || y >= 14)
		return (1);
	return (map2d[y][x] != 0);
}

int get_wall_color(int type_wall)
{
	if(type_wall < 0 || type_wall > 4)
		return (0xFFFFFF);
	return (wall_colors[type_wall]);
}


int is_valid_position(myvar *var, double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;

    return !is_wall(var, map_x, map_y);
}


void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;
    if (x >= 0 && x < screen_width && y >= 0 && y < screen_height)
    {
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
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

void read_keys(myvar *var)
{

	t_data *data = var->data;
	// print_map(var->s);
    double moveStep = data->move_speed * 3.0;
	double strafeStep = data->move_speed * 3.0;
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
	if(keyDown(data, KEY_D))
	{
		newPosX -= data->plane_x * strafeStep;
		newPosY -= data->plane_y * strafeStep;
	}
	if(keyDown(data, KEY_A))
	{
		newPosX += data->plane_x * strafeStep;
		newPosY += data->plane_y * strafeStep;
	}
    if (is_valid_position(var, newPosX, data->pos_y))
        data->pos_x = newPosX;
    if (is_valid_position(var, data->pos_x, newPosY))
        data->pos_y = newPosY;
    if (keyDown(data, KEY_RIGHT))
    {
        double oldDirX = data->dir_x;
        data->dir_x = data->dir_x * cos(-data->rot_speed) - data->dir_y * sin(-data->rot_speed);
        data->dir_y = oldDirX * sin(-data->rot_speed) + data->dir_y * cos(-data->rot_speed);
        double oldPlaneX = data->plane_x;
        data->plane_x = data->plane_x * cos(-data->rot_speed) - data->plane_y * sin(-data->rot_speed);
        data->plane_y = oldPlaneX * sin(-data->rot_speed) + data->plane_y * cos(-data->rot_speed);
    }
    if (keyDown(data, KEY_LEFT))
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

void dda_algo(t_ray *ray, myvar *var)
{
    while (!ray->hit)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
            if (ray->step_x == -1)
                ray->wall_orientation = 2; // W
            else
                ray->wall_orientation = 3; // E
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
            if (ray->step_y == -1)
                ray->wall_orientation = 1; // N
            else
                ray->wall_orientation = 0; // S
        }
        if (is_wall(var, ray->map_x, ray->map_y))
            ray->hit = 1;
    }
}

void	calcul_wall_dist(t_data *data, t_ray *ray, double ray_dir_x, double ray_dir_y)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->pos_x + (1 - ray->step_x) / 2) / ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->pos_y + (1 - ray->step_y) / 2) / ray_dir_y;
    double scaling_factor = 2.5;

    ray->line_height = (int)(screen_height / ray->perp_wall_dist / scaling_factor);
    ray->draw_start = -ray->line_height / 2 + screen_height / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + screen_height / 2;
    if (ray->draw_end >= screen_height)
		ray->draw_end = screen_height - 1;

}
void print_map(char **s)
{
	int i = 0;
	while (s[i])
	{
		printf("%s\n", s[i]);
		i++;
	}
}

void detect_direc_player(myvar *var)
{
    int i = 0;
    int j = 0;
    while (var->s[i])
    {
        j = 0;
        while (var->s[i][j])
        {
            if (var->s[i][j] == 'N' || var->s[i][j] == 'S' || var->s[i][j] == 'E' || var->s[i][j] == 'W')
            {
                var->player.x = j;
                var->player.y = i;
                if (var->s[i][j] == 'N')
                {
                	printf("Found player at (%d,  %d): %c\n", i, j, var->s[i][j]);
                    var->data->dir_x = 0;
                    var->data->dir_y = -1;
                    var->data->plane_x = 0.66;
                    var->data->plane_y = 0;
                }
                else if (var->s[i][j] == 'S')
                {
                    var->data->dir_x = 0;
                    var->data->dir_y = 1;
                    var->data->plane_x = -0.66;
                    var->data->plane_y = 0;
                }
                else if (var->s[i][j] == 'E')
                {
                    var->data->dir_x = 1;
                    var->data->dir_y = 0;
                    var->data->plane_x = 0;
                    var->data->plane_y = 0.66;
                }
                else if (var->s[i][j] == 'W')
                {
                    var->data->dir_x = -1;
                    var->data->dir_y = 0;
                    var->data->plane_x = 0;
                    var->data->plane_y = -0.66;
                }
                var->s[i][j] = '0';
                return;
            }
            j++;
        }
        i++;
    }
}

void draw_v_line(t_data *data, int x, t_ray *ray, myvar *var)
{
    int y = ray->draw_start;
    int color;

    if (ray->map_y >= 0 && ray->map_y < var->data->map_rows && ray->map_x >= 0 && ray->map_x < var->data->map_cols && (size_t)ray->map_x < ft_strlen(var->s[ray->map_y]))
	{
        if (ray->wall_orientation == 0)
            color = 0xFF0000; // South wall - Red
        else if (ray->wall_orientation == 1)
            color = 0x00FF00; // North wall - Green
        else if (ray->wall_orientation == 2)
            color = 0x0000FF; // West wall - Blue
        else if (ray->wall_orientation == 3)
            color = 0xFFFF00; // East wall - Yellow
        else
            color = 0xFFFFFF; // Default - White

        while (y < ray->draw_end)
		{
            my_mlx_pixel_put(data, x, y, color);
            y++;
        }
    }
}

// void print_player_position(t_data *data)
// {
//     printf("Player position: (%f, %f)\n", data->pos_x, data->pos_y);
//     printf("Player map position: (%d, %d)\n", (int)data->pos_x, (int)data->pos_y);
//     printf("Is wall at player position: %d\n", is_wall((int)data->pos_x, (int)data->pos_y));
// }

int get_2d_map_color(int wall_type, int orientation)
{
    if (wall_type == 1)
    {
        if (orientation == 0)
            return 0xFF0000;      // S - Red
        else if (orientation == 1)
            return 0x00FF00;      // N - Green
        else if (orientation == 2)
            return 0x0000FF;      // W- Blue
        else if (orientation == 3)
            return 0xFFFF00;      // E- Yellow
        return 0xFFFFFF;          // default- White
    }
    return 0x000000;             // Ground - Black
}

void draw_2d_map(myvar *var)
{
    t_data *data = var->data;
    int x, y;
    int mini_size = MAP_WIDTH / 20;
    int map_offset = 10;
    y = 0;
    while (y < var->data->map_rows)
    {
        x = 0;
        while (x < var->data->map_cols)
        {
            if ((size_t)x < ft_strlen(var->s[y]))
            {
                int wall_type = var->s[y][x] - '0';
                int orientation = -1;
                if (wall_type == 1)
                {
                    if (y > 0 && (size_t)x < ft_strlen(var->s[y-1]) && var->s[y-1][x] == '0')
                        orientation = 1;
                    else if (y < var->data->map_rows - 1 && (size_t)x < ft_strlen(var->s[y+1]) && var->s[y+1][x] == '0')
                        orientation = 0;
                    else if (x > 0 && var->s[y][x-1] == '0')
                        orientation = 2;
                    else if (x < var->data->map_cols - 1 && var->s[y][x+1] == '0')
                        orientation = 3;
                }

                int color = get_2d_map_color(wall_type, orientation);

                int py = 0;
                while (py < mini_size)
                {
                    int px = 0;
                    while (px < mini_size)
                    {
                        my_mlx_pixel_put(data,
                                        map_offset + x * mini_size + px,
                                        map_offset + y * mini_size + py,
                                        color);
                        px++;
                    }
                    py++;
                }
            }
            x++;
        }
        y++;
    }
    int player_x = (int)(data->pos_x * mini_size);
    int player_y = (int)(data->pos_y * mini_size);
    int px = -2;
    while (px <= 2)
    {
        int py = -2;
        while (py <= 2)
        {
            my_mlx_pixel_put(data, player_x + px, player_y + py, 0xFF0000);
            py++;
        }
        px++;
    }
}

void draw_ray(myvar *var, t_data *data, double ray_dir_x, double ray_dir_y, int color)
{
	int tile_size = MAP_WIDTH / 20;
	double ray_pos_x = data->pos_x;
	double ray_pos_y = data->pos_y;

	double delta_dist_x = fabs(1 / ray_dir_x);
	double delta_dist_y = fabs(1 / ray_dir_y);

	int step_x = (ray_dir_x < 0) ? -1 : 1;
	int step_y = (ray_dir_y < 0) ? -1 : 1;

	double side_dist_x = (step_x < 0) ? (ray_pos_x - floor(ray_pos_x)) * delta_dist_x : (ceil(ray_pos_x) - ray_pos_x) * delta_dist_x;
	double side_dist_y = (step_y < 0) ? (ray_pos_y - floor(ray_pos_y)) * delta_dist_y : (ceil(ray_pos_y) - ray_pos_y) * delta_dist_y;

	int hit = 0;
	while (!hit)
	{
		int pixel_x = (int)(ray_pos_x * tile_size);
		int pixel_y = (int)(ray_pos_y * tile_size);

		if (pixel_x >= 0 && pixel_x < MAP_WIDTH && pixel_y >= 0 && pixel_y < MAP_WIDTH)
			my_mlx_pixel_put(data, pixel_x, pixel_y, color);
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			ray_pos_x += step_x;
		}
		else
		{
			side_dist_y += delta_dist_y;
			ray_pos_y += step_y;
		}
		if (is_wall(var, (int)ray_pos_x, (int)ray_pos_y))
			hit = 1;
	}
}

void calcul_map_dimens(myvar *var)
{
	int row = 0;
	int col = 0;

	while (var->s[row])
		row++;
	if(row > 0)
		col = ft_strlen(var->s[0]);
	var->data->map_rows = row;
	var->data->map_cols = col;
	printf("rows %d cols %d\n",var->data->map_rows,var->data->map_cols);
}
int raycasting_loop(myvar *var)
{
	t_data *data = var->data;
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
	read_keys(var);
	// print_player_position(data);
	memset(data->addr, 0, screen_width * screen_height * (data->bits_per_pixel / 8));
	x = 0;
	while (x < screen_width)
	{
		init_ray(data, x, &ray);
		ray_dir_x = data->dir_x + data->plane_x * ray.camera_x;
		ray_dir_y = data->dir_y + data->plane_y * ray.camera_x;
		calculate_dist(data, &ray, ray_dir_x, ray_dir_y);
		dda_algo(&ray, var);
		calcul_wall_dist(data, &ray, ray_dir_x, ray_dir_y);
		// var->s[var->player.x][var->player.y] = '0';
		draw_v_line(data, x, &ray, var);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	draw_2d_map(var);
	if ((x - MAP_WIDTH) % 20 == 0)
		draw_ray(var, data, ray_dir_x, ray_dir_y, 0x2000FF00);
	mlx_do_sync(data->mlx);
	return (0);
}

void execute(myvar *var)
{
	t_data *data = var->data;
	data->pos_x = var->player.x + 0.5;
	data->pos_y = var->player.y + 0.5;
	memset(data->keys, 0, sizeof(data->keys));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, screen_width, screen_height, "CUB3D");
	data->img = mlx_new_image(data->mlx, screen_width, screen_height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	mlx_hook(data->win, 2, 1L<<0, key_press, data);
	mlx_hook(data->win, 3, 1L<<1, key_release, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, raycasting_loop, var);
	mlx_loop(data->mlx);
	// print_player_position(data);
}
