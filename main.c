#include "cub3d.h"

int	duplicate(list *listt)
{
	while (listt)
	{
		if ((listt)->value == 0 || (listt)->value > 1)
			return (1);
		(listt) = (listt)->next;
	}
	return (0);
}

int	parse_map(myvar *var)
{
	list	*listt;
	char	*line;
	char	*s;
	char	**ss;

	list_fill(&listt, &(var->list));
	s = ft_strdup("");
	mylist(s, &(var->list));
	line = get_next_line(var->fd);
	if (!line)
		return (1);
	while ((line))
		store_line(&line, var, &s);
	var->str = s;
	ss = ft_split(s, '\n');
	mylist(ss, &(var->list));
	add_to_listt(ss, &(var->list));
	if (check_s(ss, &listt, var) || duplicate(listt) || var->count != 6)
		return (1);
	var->s = map_to_s(var->str, var->count, &(var->list));
	return (0);
}

int	check_extension(char *str, char *s)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	while (str[++i])
		if (str[i] == '.')
			check = 1;
	i = ft_strlen(str) - 4;
	if (check && !ft_strncmp(str + i, s, ft_strlen(s)))
		return (1);
	else
		return (0);
}

void	init(myvar *var, int argc, char **argv)
{
	int	i;


	memset(var->texturess,0,4*4);
	i = -1;
	while (++i < 4)
		var->textures[i] = NULL;
	var->data = (t_data *)malloc(sizeof(t_data));
	if (!(var->data))
		return ;
	var->s = NULL;
	var->cel = 0;
	var->floor = 0;
	var->fd = 0;
	var->list = NULL;
	var->str = NULL;
	var->count = 0;
	var->map.texture = malloc(sizeof(var->map) * 4);
	if (!(var->map.texture))
		return ;
	mylist(var->map.texture, &(var->list));
	var->fd = open(argv[1], O_RDONLY);
	if (var->fd == -1 || (!(check_extension(argv[1], ".cub"))) || argc != 2)
		var->fd = 0;
}

int	main(int argc, char **argv)
{
	myvar	*var;

	var = malloc(sizeof(myvar));
	init(var, argc, argv);
	if (!var->fd)
		return (printf("error"), 1);
	if (parse_map(var) || find_direction(&var->player, var->s)
		|| check_map2(var->s))
	{
		printf("error ");
		return (garbage_collector(&var->list, free), 1);
	}
	else
	{
		calcul_map_dimens(var);
		detect_direc_player(var);
		execute(var);
	}
	return (garbage_collector(&var->list, free), 1);
}
