#include "../cub3d.h"

int	check_texture(char *s, list **list, myvar *var)
{
	char	**ss;

	ss = ft_split(s, ' ');
	add_to_listt(ss, &(var->list));
	mylist(ss, &(var->list));
	if (count(ss) == 2)
	{
		if (open(ss[1], O_RDONLY) == -1 || !(check_extension(ss[1], ".xpm")))
			return (store_to_error(&var->error,"Error On file Textures"),1);
		store_to_textures(var, ss[1]);
		add_node_list(ss[0], list, &var->count, (var));
	}
	return (0);
}

void	check_texture_floor(char *c, char *s, myvar *var, list **listt)
{
	if ((!ft_strncmp(c, "NO", 2)) || (!ft_strncmp(c, "SO", 2)) || !ft_strncmp(c,
			"WE", 2) || !ft_strncmp(c, "EA", 2))
		check_texture(s, listt, var);
	else
		check_floor(s, listt, var);
}

int	check_sfloor(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if ((s[i] == ',' && s[i + 1] == s[i]) || s[0] == ',')
			return (1);
	}
	return (0);
}

int	check_floor(char *s, list **listo, myvar *var)
{
	char	*sss;
	int		i;
	char	**ss;

	if (process_s(&s, &sss, &(var->list)))
		return (store_to_error(&var->error,"Invalid Format"),1);
	i = -1;
	ss = ft_split(s, ',');
	add_to_listt(ss, &(var->list));
	mylist(ss, &(var->list));
	if (count(ss) != 3 || s[ft_strlen(s) - 1] == ',' || (check_sfloor(s)))
		return (store_to_error(&var->error,"Error On Syntax of Floor"),1);
	while (ss[++i])
	{
		if (check_ss(ss[i], &(var->list)) || ft_atoi(ss[i]) < 0
			|| ft_atoi(ss[i]) > 255)
			return (store_to_error(&var->error,"Invalid Value of FLoor"),1);
	}
	if (sss[0] == 'F')
		var->floor = create_rgb(ft_atoi(ss[0]), ft_atoi(ss[1]), ft_atoi(ss[2]));
	else
		var->cel = create_rgb(ft_atoi(ss[0]), ft_atoi(ss[1]), ft_atoi(ss[2]));
	add_node_list(sss, listo, &var->count, (var));
	return (0);
}

int	process_s(char **s, char **ss, listt **node)
{
	*s = ft_strtrim(*s, " ");
	mylist(*s, node);
	*ss = *s;
	if (!((**s == 'C' || **s == 'F') && s[0][1] == ' '))
		return (1);
	(*s)++;
	*s = ft_strtrim(*s, " ");
	mylist(*s, node);
	(*ss)[1] = 0;
	return (0);
}
