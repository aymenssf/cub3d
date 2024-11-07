#include "../cub3d.h"

int	check_texture(char *s, list **list, int *countt, listt **nodee)
{
	char	**ss;

	ss = ft_split(s, ' ');
	add_to_listt(ss, nodee);
	mylist(ss, nodee);
	if (count(ss) == 2)
	{
		if (open(ss[1], O_RDONLY) == -1 || !(check_extension(ss[1], ".xpm")))
			return (printf("there is an error on textures"), 1);
		add_node_list(ss[0], list, countt, nodee);
	}
	return (0);
}
void	check_texture_floor(char *c, char *s, myvar *var, list **listt)
{
	if ((!ft_strncmp(c, "NO", 2)) || (!ft_strncmp(c, "SO", 2)) || !ft_strncmp(c,
			"WE", 2) || !ft_strncmp(c, "EA", 2))
		check_texture(s, listt, &var->count, &var->list);
	else
		check_floor(s, listt, &var->count, &var->list);
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

int	check_floor(char *s, list **listo, int *countt, listt **node)
{
	char	*sss;
	int		i;
	char	**ss;

	if (process_s(&s, &sss, node))
		return (1);
	i = -1;
	ss = ft_split(s, ',');
	add_to_listt(ss, node);
	mylist(ss, node);
	// TO DO
	if (count(ss) != 3 || s[ft_strlen(s) - 1] == ',' || (check_sfloor(s)))
		return (1);
	while (ss[++i])
		if (check_ss(ss[i], node) || ft_atoi(ss[i]) < 0 || ft_atoi(ss[i]) > 255)
			return (1);
	add_node_list(sss, listo, countt, node);
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
