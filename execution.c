/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:40:26 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/14 14:03:17 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

t_texture textures[4];

t_texture texture_hands;


void load_textures_hands(void *mlx)
{


		texture_hands.img = mlx_xpm_file_to_image(mlx,"file.xpm" , &texture_hands.width, &texture_hands.height);
        texture_hands.addr = mlx_get_data_addr(texture_hands.img, &texture_hands.bits_per_pixel,
                                              &texture_hands.line_length, &texture_hands.endian);


}


void load_textures(void *mlx,myvar *var)
{

	int i = -1;

	while (++i < 4)
	{
		textures[i].img = mlx_xpm_file_to_image(mlx,var->textures[i] , &textures[i].width, &textures[i].height);
        textures[i].addr = mlx_get_data_addr(textures[i].img, &textures[i].bits_per_pixel,
                                              &textures[i].line_length, &textures[i].endian);
	}


}
double get_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (double)tv.tv_sec * 1000.0 + (double)tv.tv_usec / 1000.0;
}

int is_wall(myvar *var, int x, int y)
{
	if (x < 0 || x >= var->data->map_cols|| y < 0 || y >= var->data->map_rows)
		return (1);
    return (var->s[y][x] != '0'); }

int is_valid_position(myvar *var, double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;
    if (map_x < 0 || map_x >= var->data->map_cols ||
         map_y < 0 || map_y >= var->data->map_rows)
        return 0;
    return (var->s[map_y][map_x] == '0');
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

static void hdl_up_down(t_data *data, double *newPosX, double *newPosY)
{
    double moveStep = data->move_speed * 3.0;

    if (keyDown(data, KEY_UP) || keyDown(data, KEY_W))
	{
        *newPosX += data->dir_x * moveStep;
        *newPosY += data->dir_y * moveStep;
    }
    if (keyDown(data, KEY_DOWN) || keyDown(data, KEY_S))
	{
        *newPosX -= data->dir_x * moveStep;
        *newPosY -= data->dir_y * moveStep;
    }
}

static void hdl_strafe(t_data *data, double *newPosX, double *newPosY)
{
    double strafeStep;
	strafeStep = data->move_speed * 3.0;

    if (keyDown(data, KEY_D))
	{
        *newPosX -= data->plane_x * strafeStep;
        *newPosY -= data->plane_y * strafeStep;
    }
    if (keyDown(data, KEY_A))
	{
        *newPosX += data->plane_x * strafeStep;
        *newPosY += data->plane_y * strafeStep;
    }
}

static void hdl_r_rot(t_data *data)
{
    double oldDirX = data->dir_x;
    data->dir_x = data->dir_x * cos(-data->rot_speed) - data->dir_y * sin(-data->rot_speed);
    data->dir_y = oldDirX * sin(-data->rot_speed) + data->dir_y * cos(-data->rot_speed);
    double oldPlaneX = data->plane_x;
    data->plane_x = data->plane_x * cos(-data->rot_speed) - data->plane_y * sin(-data->rot_speed);
    data->plane_y = oldPlaneX * sin(-data->rot_speed) + data->plane_y * cos(-data->rot_speed);
}

static void hdl_l_rot(t_data *data)
{
    double oldDirX = data->dir_x;
    data->dir_x = data->dir_x * cos(data->rot_speed) - data->dir_y * sin(data->rot_speed);
    data->dir_y = oldDirX * sin(data->rot_speed) + data->dir_y * cos(data->rot_speed);
    double oldPlaneX = data->plane_x;
    data->plane_x = data->plane_x * cos(data->rot_speed) - data->plane_y * sin(data->rot_speed);
    data->plane_y = oldPlaneX * sin(data->rot_speed) + data->plane_y * cos(data->rot_speed);
}

void read_keys(myvar *var)
{
    t_data *data = var->data;
    double newPosX = data->pos_x;
    double newPosY = data->pos_y;

    hdl_up_down(data, &newPosX, &newPosY);
    hdl_strafe(data, &newPosX, &newPosY);
    if (is_valid_position(var, newPosX, data->pos_y))
        data->pos_x = newPosX;
    if (is_valid_position(var, data->pos_x, newPosY))
        data->pos_y = newPosY;
    if (keyDown(data, KEY_RIGHT))
        hdl_r_rot(data);
    if (keyDown(data, KEY_LEFT))
        hdl_l_rot(data);
    if (keyDown(data, KEY_ESC))
        destroy(data);
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

static void init_N(myvar *var)
{
    var->data->dir_x = 0;
    var->data->dir_y = -1;
    var->data->plane_x = 0.66;
    var->data->plane_y = 0;
}

static void init_S(myvar *var)
{
    var->data->dir_x = 0;
    var->data->dir_y = 1;
    var->data->plane_x = -0.66;
    var->data->plane_y = 0;
}

static void init_E(myvar *var)
{
    var->data->dir_x = 1;
    var->data->dir_y = 0;
    var->data->plane_x = 0;
    var->data->plane_y = 0.66;
}

static void init_W(myvar *var)
{
    var->data->dir_x = -1;
    var->data->dir_y = 0;
    var->data->plane_x = 0;
    var->data->plane_y = -0.66;
}

static void set_direc_player(myvar *var, char direc)
{
	if (direc == 'N')
		init_N(var);
	else if (direc == 'S')
		init_S(var);
	else if (direc == 'E')
		init_E(var);
	else if (direc == 'W')
		init_W(var);
}

void detect_direc_player(myvar *var)
{
	int(i), (j);

	i = 0;
    while (var->s[i])
    {
        j = 0;
        while (var->s[i][j])
        {
            if (strchr("NSEW", var->s[i][j]))
			{
                var->player.x = j;
                var->player.y = i;
                set_direc_player(var, var->s[i][j]);
                var->s[i][j] = '0';
                return;
            }
            j++;
        }
        i++;
    }
}
int get_texture_color(int type_wall, int x, int y)
{

    char *pixel = textures[type_wall].addr + (y * textures[type_wall].line_length + x * 4);
    return *(unsigned int *)pixel;
}

void draw_v_line(t_data *data, int x, t_ray *ray, myvar *var,double ray_dir_x, double ray_dir_y)
{
    int y = ray->draw_start;
    int color;
    int i = -1;

    while (++i <  y)
			my_mlx_pixel_put(data, x, i, var->floor);

i = ray->draw_end;
  while (i < screen_height)
    {
        my_mlx_pixel_put(data, x, i, var->cel);
        i++;
    }
		double wall_x = 0;

    if (ray->map_y >= 0 && ray->map_y < var->data->map_rows && ray->map_x >= 0 && ray->map_x < var->data->map_cols && (size_t)ray->map_x < ft_strlen(var->s[ray->map_y]))
	{

    if (ray->side == 0)
			wall_x = data->pos_y +ray->perp_wall_dist * ray_dir_y;
		else
			wall_x = data->pos_x + ray->perp_wall_dist * ray_dir_x;

		 wall_x -= floor(wall_x);

		int tex_x = (int)(wall_x * textures[ray->wall_orientation].width);
        while (y < ray->draw_end)
		{
          int tex_y  = ((y - ray->draw_start)* textures[ray->wall_orientation].height ) / ray->line_height;
			 color = get_texture_color(ray->wall_orientation, tex_x, tex_y);
			my_mlx_pixel_put(data, x, y, color);
			y++;
        }

    }


}



static void calculate_step_direction(double ray_dir_x, double ray_dir_y, int *step_x, int *step_y)
{
    if (ray_dir_x < 0)
        *step_x = -1;
    else
        *step_x = 1;

    if (ray_dir_y < 0)
        *step_y = -1;
    else
        *step_y = 1;
}

static void calculate_side_distances(double ray_pos_x, double ray_pos_y,
                                   double delta_dist_x, double delta_dist_y,
                                   int step_x, int step_y,
                                   double *side_dist_x, double *side_dist_y)
{
    if (step_x < 0)
        *side_dist_x = (ray_pos_x - floor(ray_pos_x)) * delta_dist_x;
    else
        *side_dist_x = (ceil(ray_pos_x) - ray_pos_x) * delta_dist_x;

    if (step_y < 0)
        *side_dist_y = (ray_pos_y - floor(ray_pos_y)) * delta_dist_y;
    else
        *side_dist_y = (ceil(ray_pos_y) - ray_pos_y) * delta_dist_y;
}

static void draw_ray_pixel(t_data *data, double ray_pos_x, double ray_pos_y,
                          int tile_size, int color)
{
    int pixel_x;
	pixel_x = (int)(ray_pos_x * tile_size);
    int pixel_y;
	pixel_y = (int)(ray_pos_y * tile_size);

    if (pixel_x >= 0 && pixel_x < MAP_WIDTH &&
        pixel_y >= 0 && pixel_y < MAP_WIDTH)
        my_mlx_pixel_put(data, pixel_x, pixel_y, color);
}

static void update_ray_position(double *ray_pos_x, double *ray_pos_y,
                              double *side_dist_x, double *side_dist_y,
                              double delta_dist_x, double delta_dist_y,
                              int step_x, int step_y)
{
    if (*side_dist_x < *side_dist_y)
    {
        *side_dist_x += delta_dist_x;
        *ray_pos_x += step_x;
    }
    else
    {
        *side_dist_y += delta_dist_y;
        *ray_pos_y += step_y;
    }
}

void draw_ray(myvar *var, t_data *data, double ray_dir_x, double ray_dir_y, int color)
{
    int tile_size = MAP_WIDTH / 20;
    double ray_pos_x = data->pos_x;
    double ray_pos_y = data->pos_y;
    double delta_dist_x = fabs(1 / ray_dir_x);
    double delta_dist_y = fabs(1 / ray_dir_y);
    int step_x, step_y;
    calculate_step_direction(ray_dir_x, ray_dir_y, &step_x, &step_y);

    double side_dist_x, side_dist_y;
    calculate_side_distances(ray_pos_x, ray_pos_y,
                           delta_dist_x, delta_dist_y,
                           step_x, step_y,
                           &side_dist_x, &side_dist_y);
    int hit = 0;
    while (!hit)
    {
        draw_ray_pixel(data, ray_pos_x, ray_pos_y, tile_size, color);
        update_ray_position(&ray_pos_x, &ray_pos_y,
                          &side_dist_x, &side_dist_y,
                          delta_dist_x, delta_dist_y,
                          step_x, step_y);
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
    int i = 0;
    while(i < row)
    {
        int line_length = ft_strlen(var->s[i]);
        if (line_length > col)
            col = line_length;
        i++;
    }
	var->data->map_rows = row;
	var->data->map_cols = col;
}

int get_texture_hands_color(int x, int y) {
    if (x >= 0 && x < texture_hands.width && y >= 0 && y < texture_hands.height) {
        int offset = (y * texture_hands.line_length) + (x * (texture_hands.bits_per_pixel / 8));
        return *(unsigned int *)(texture_hands.addr + offset);
    } else {
        return 0xFF000000;
    }
}
    
void draw_hands(t_data *data)
{

        int vertical_offset = 0;
    if (1)
        vertical_offset = sin(get_time() * 0.01) * 10.0 ;


 int y = 0;
        while (y < 630) {
            int x = 0;
            while (x < 630) {
                unsigned int color = (unsigned int)get_texture_hands_color(x, y);
            if (color != 0xFF000000)
            {
                    my_mlx_pixel_put(data, (screen_width - 650 + vertical_offset) / 2 + x,
                                (screen_height - 370 + vertical_offset )+ y, color);
            }
                x++;
            }
            y++;
        }


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
		draw_v_line(data, x, &ray, var,ray_dir_x, ray_dir_y);
		x++;
	}

    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
        draw_hands(data);
    ft_draw_mini_map(var);
    handle_mouse(var);
	mlx_do_sync(data->mlx);
	return (0);
}

void destroy(t_data *data)
{
    mlx_destroy_image(data->mlx, data->img);
    mlx_destroy_window(data->mlx, data->win);
    mlx_loop_end(data->mlx);
    mlx_clear_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    free(data);
    exit(0);

}

void execute(myvar *var)
{

	t_data *data = var->data;
	data->pos_x = var->player.x + 0.5;
	data->pos_y = var->player.y + 0.5;
	memset(data->keys, 0, sizeof(data->keys));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, screen_width, screen_height, "CUB3D");
    	  load_textures(data->mlx,var);

         load_textures_hands(data->mlx);

	data->img = mlx_new_image(data->mlx, screen_width, screen_height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    setup_mouse(var);
	mlx_hook(data->win, 2, 1L<<0, key_press, data);
	mlx_hook(data->win, 3, 1L<<1, key_release, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, raycasting_loop, var);
	mlx_loop(data->mlx);
    destroy(data);
}
