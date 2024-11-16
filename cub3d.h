/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:47:45 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/15 23:11:40 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define MINI_MAP_SIZE 5
# define TILE_SIZE 16
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define PIXEL 128
# define KEY_RIGHT 65361
# define KEY_UP 65362
# define KEY_LEFT 65363
# define KEY_DOWN 65364
# define KEY_W 119
# define KEY_S 115
# define KEY_D 97
# define KEY_A 100
# define KEY_ESC 65307
// # include <X11/keysym.h>
// # include <X11/X.h>
# include "mlx_linux/mlx.h"
# include <math.h>
# include <stdarg.h>
# include <string.h>
# include <sys/time.h>

# define MINI_MAP_SIZE 5
# define TILE_SIZE 16
# define screen_width 1200
# define screen_height 720
# define MAP_HEIGHT 24
# define MAP_WIDTH 240

typedef struct player
{
	int				x;
	int				y;
	int				visited;
}					player;

typedef struct queue
{
	int				x;
	int				y;
	int				visited;
	struct queue	*next;
}					queue;

typedef struct my_map
{
	char			**texture;
	char			**floor;
	char			**map;
	int				tab[5];
}					my_map;

typedef struct list
{
	int				value;
	char			*name;
	struct list		*next;
}					list;

typedef struct listt
{
	void			*node;
	struct listt	*next;
}					listt;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			old_time;
	double			rot_speed;
	int				map_rows;
	int				map_cols;
	int				keys[65536];
	unsigned int	*dst;
	int				color;
	int				mouse_x;
	int				mouse_y;
	double			ray_dir_x;
	double			ray_dir_y;
}					t_data;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_texture;

typedef struct myvar
{
	t_data			*data;
	listt			*list;
	my_map			map;
	char			**s;
	int				count;
	int				map_offset;
	int				i;
	int				fd;
	char			*str;
	player			player;
	int				floor;
	int				cel;
	char			*error;
	char			*textures[4];
	t_texture		texturess[4];
	t_texture		texture_hands;

}					myvar;

typedef struct s_ray_calc
{
	double			ray_pos_x;
	double			ray_pos_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
}					t_ray_calc;

typedef struct s_ray
{
	double			camera_x;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				wall_orientation;
	int				draw_end;
}					t_ray;

char				*get_next_line(int fd);
int	find_direction(myvar *var ,player *player, char **mini_map);
char				**map_to_s(char *s, int count, myvar *var);
void				mylist(void *node, listt **nodee);
void				garbage_collector(myvar *var, void (*del)(void *));
void				add_to_listt(char **ss, listt **node);
int					simple_check(int i, int j, char **s, int check);
int					last_ind(char *str);
int					first_ind(char *str);
int					ft_listsize(list *lst);
void				list_fill(list **list, listt **node);
void				store_line(char **line, myvar *var, char **s);
void				fill_listt(list **listo, listt **liste);
void				add_node_list(char *name, list **listo, int *countt,
						myvar *var);
int					check_xy(int x, int y, char **s);
void store_to_error(char **s , char *error);
int	check_map2(char **s , myvar *var);
int					check_floor(char *s, list **listo, myvar *var);
void				check_texture_floor(char *c, char *s, myvar *var,
						list **listt);
int					process_s(char **s, char **ss, listt **node);
int					count(char **s);
int					check_texture(char *s, list **list, myvar *var);
int					check_ss(char *line, listt **node);
void				add_nodee(char *name, list **listo, listt **liste);
int					check_s(char **s, list **list, myvar *var);
int					process_s(char **s, char **ss, listt **node);
void				detect_direc_player(myvar *var);
void				parse_s(char **s, int count);
int					check_extension(char *str, char *s);
void				execute(myvar *var);
void				calcul_map_dimens(myvar *var);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				store_to_textures(myvar *var, char *s);
int					create_rgb(int r, int g, int b);
void				ft_draw_mini_map(myvar *var);
void				setup_mouse(myvar *var);
int					handle_mouse(myvar *var);
void				destroy(t_data *data);
int					get_texture_color(myvar *var, int type_wall, int x, int y);
void				load_textures_hands(void *mlx, myvar *var);
void				load_textures(void *mlx, myvar *var);
void				draw_hands(t_data *data, myvar *var);
int					get_texture_hands_color(myvar *var, int x, int y);
void				destroy_image(myvar *var);
double				get_time(void);
int					key_press(int keycode, myvar *var);
int					key_release(int keycode, t_data *data);
int					key_down(t_data *data, int keycode);
void				read_keys(myvar *var);
int					is_valid_position(myvar *var, double x, double y);
int					close_window(myvar *data);
int					raycasting_loop(myvar *var);
void				init_ray(t_data *data, int x, t_ray *ray);
void				calcul_wall_dist(t_data *data, t_ray *ray, double ray_dir_x,
						double ray_dir_y);
void				calculate_dist(t_data *data, t_ray *ray, double ray_dir_x,
						double ray_dir_y);
void				dda_algo(t_ray *ray, myvar *var);
int					is_wall(myvar *var, int x, int y);
void				draw_v_line(t_data *data, int x, t_ray *ray, myvar *var);
void				calculate_step_direction(double ray_dir_x, double ray_dir_y,
						int *step_x, int *step_y);
void				update_frame_data(t_data *data);
void				update_display(t_data *data, myvar *var);
void				init_ray_calc(t_ray_calc *calc, t_data *data);

#endif
