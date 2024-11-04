#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define PIXEL 128
#define KEY_LEFT 65361
#define KEY_UP 65362
#define KEY_RIGHT 65363
#define KEY_DOWN 65364
#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100
#define KEY_ESC 65307
# include <X11/keysym.h>
# include <X11/X.h>
# include <sys/time.h>
# include <string.h>
# include <stdarg.h>
#include <math.h>
# include "mlx.h"

#define screen_width 1920
#define screen_height 1080
#define MAP_HEIGHT 24
#define MAP_WIDTH 240

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
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double move_speed;
	double old_time;
	double rot_speed;
	int keys[65536];
} t_data;

typedef struct myvar
{
	t_data			*data;
	listt			*list;
	my_map			map;
	char			**s;
	int				count;

	int				i;
	int				fd;
	char			*str;
	player			player;

}					myvar;


typedef struct s_ray
{
	double	camera_x;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
} t_ray;





char				*get_next_line(int fd);
int					find_direction(player *player, char **mini_map);
queue				*add_node(int x, int y);
void	add_quee(queue **queu, int x, int y, listt **node);
void				dequee(queue **queu);
char				**map_to_s(char *s, int count, listt **node);
void				mylist(void *node, listt **nodee);
void				garbage_collector(listt **lst, void (*del)(void *));
void				add_to_listt(char **ss, listt **node);
int					simple_check(int i, int j, char **s, int check);
int					last_ind(char *str);
int					first_ind(char *str);
int					ft_listsize(list *lst);
void				list_fill(list **list, listt **node);
void				store_line(char **line, myvar *var, char **s);
void				fill_listt(list **listo, listt **liste);
void				add_node_list(char *name, list **listo, int *countt,
						listt **node);
void				do_something(player p, char **s, queue **queue,
						listt **node);
int					check_xy(int x, int y, char **s);
int					check_map2(char **s);
int					check_floor(char *s, list **listo, int *countt,
						listt **node);
void	check_texture_floor(char *c, char *s,myvar *var ,list **listt);
int					process_s(char **s, char **ss, listt **node);
int					count(char **s);
int	check_texture(char *s, list **list, int *countt, listt **nodee);
int					check_ss(char *line, listt **node);
void				add_nodee(char *name, list **listo, listt **liste);
int					check_s(char **s, list **list, myvar *var);
int					process_s(char **s, char **ss, listt **node);
void	parse_s(char **s, int count);
int check_extension(char *str ,char *s);
void execute(myvar var);
void print_map(char **s);

#endif
