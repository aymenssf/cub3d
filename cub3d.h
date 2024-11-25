/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:47:45 by aassaf            #+#    #+#             */
/*   Updated: 2024/11/16 22:37:50 by aassaf           ###   ########.fr       */
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
# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 720
# define MAP_HEIGHT 24
# define MAP_WIDTH 240

typedef struct player
{
	int				x;
	int				y;
	int				visited;
}					t_player;

typedef struct my_map
{
	char			**texture;
	char			**floor;
	char			**map;
	int				tab[5];
}					t_map;

typedef struct list
{
	int				value;
	char			*name;
	struct list		*next;
}					t_liist;

typedef struct listt
{
	void			*node;
	struct listt	*next;
}					t_listt;

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
	int				color_mini;
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
	t_listt			*list;
	t_map			map;
	char			**s;
	int				count;
	int				map_offset;
	int				i;
	int				fd;
	char			*str;
	t_player		player;
	int				floor;
	int				cel;
	char			*error;
	char			*textures[4];
	t_texture		texturess[4];
	t_texture		texture_hands;
	int				radius;
	int				offset_x;
	int				offset_y;
	int				base_x;
	int				base_y;
}					t_myvar;

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
int					find_direction(t_myvar *var, t_player *player,
						char **mini_map);
char				**map_to_s(char *s, int count, t_myvar *var);
void				mylist(void *node, t_listt **nodee);
void				garbage_collector(t_myvar *var, void (*del)(void *));
void				add_to_listt(char **ss, t_listt **node);
int					simple_check(int i, int j, char **s, int check);
int					last_ind(char *str);
int					first_ind(char *str);
int					ft_listsize(t_liist *lst);
void				list_fill(t_liist **list, t_listt **node);
void				store_line(char **line, t_myvar *var, char **s);
void				fill_listt(t_liist **listo, t_listt **liste);
void				add_node_list(char *name, t_liist **listo, int *countt,
						t_myvar *var);
int					check_xy(int x, int y, char **s);
void				store_to_error(t_myvar *var, char **s, char *error);
int					check_map2(char **s, t_myvar *var);
int					check_floor(char *s, t_liist **listo, t_myvar *var);
void				check_texture_floor(char *c, char *s, t_myvar *var,
						t_liist **listt);
int					process_s(char **s, char **ss, t_listt **node);
int					count(char **s);
int					check_texture(char *s, t_liist **list, t_myvar *var);
int					check_ss(char *line, t_listt **node);
void				add_nodee(char *name, t_liist **listo, t_listt **liste);
int					check_s(char **s, t_liist **list, t_myvar *var);
void				detect_direc_player(t_myvar *var);
void				parse_s(char **s, int count);
int					check_extension(char *str, char *s);
void				execute(t_myvar *var);
void				calcul_map_dimens(t_myvar *var);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				store_to_textures(t_myvar *var, char *s);
int					create_rgb(int r, int g, int b);
void				ft_draw_mini_map(t_myvar *var);
void				setup_mouse(t_myvar *var);
int					handle_mouse(t_myvar *var);
void				destroy(t_data *data);
int					get_texture_color(t_myvar *var, int type_wall,
						int x, int y);
void				load_textures_hands(void *mlx, t_myvar *var);
void				load_textures(void *mlx, t_myvar *var);
void				draw_hands(t_data *data, t_myvar *var);
int					get_texture_hands_color(t_myvar *var, int x, int y);
void				destroy_image(t_myvar *var);
double				get_time(void);
int					key_press(int keycode, t_myvar *var);
int					key_release(int keycode, t_data *data);
int					key_down(t_data *data, int keycode);
void				read_keys(t_myvar *var);
int					is_valid_position(t_myvar *var, double x, double y);
int					close_window(t_myvar *data);
int					raycasting_loop(t_myvar *var);
void				init_ray(t_data *data, int x, t_ray *ray);
void				calcul_wall_dist(t_data *data, t_ray *ray, double ray_dir_x,
						double ray_dir_y);
void				calculate_dist(t_data *data, t_ray *ray, double ray_dir_x,
						double ray_dir_y);
void				dda_algo(t_ray *ray, t_myvar *var);
int					is_wall(t_myvar *var, int x, int y);
void				draw_v_line(t_data *data, int x, t_ray *ray, t_myvar *var);
void				calculate_step_direction(double ray_dir_x, double ray_dir_y,
						int *step_x, int *step_y);
void				update_frame_data(t_data *data);
void				update_display(t_data *data, t_myvar *var);
void				init_ray_calc(t_ray_calc *calc, t_data *data);
void				draw_filled_fov(t_myvar *var, double center_pos[2]);
int					get_map_color(char tile);
void				my_mlx_pixel_put_transparent(t_data *data, int x, int y,
						float alpha);
#endif
