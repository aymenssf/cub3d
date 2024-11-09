#include "../cub3d.h"

int create_rgb(int r , int g , int b)
{
	return (r << 16 | g << 8 | b );
}
int	check_s(char **s, list **list, myvar *var)
{
	int		i;
	char	**k;

	i = -1;
	while (s[++i] && (k = ft_split(s[i], ' ')))
	{
		add_to_listt(k, &var->list);
		mylist(k, &var->list);
		if (k)
		{
			if (!k[0])
				continue ;
			check_texture_floor(k[0], s[i], var, list);
		}
		if (var->count == 6)
			break ;
	}
	return (0);
}

int	count(char **s)
{
	int	i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}
