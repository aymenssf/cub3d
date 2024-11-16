/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 04:48:24 by yaboulan          #+#    #+#             */
/*   Updated: 2024/11/16 22:25:08 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*some(int *i, char *line)
{
	if (*i == 0)
		return (NULL);
	return (ft_strdup(line));
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		line[70000];
	static int	buffer_readed;
	static int	buffer_pos;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_readed)
		{
			buffer_readed = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_readed <= 0)
				break ;
		}
		line[i++] = buffer[buffer_pos++];
		if (line[i - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	return (some(&i, line));
}

int	find_direction(t_myvar *var, t_player *player, char **mini_map)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = -1;
	while (mini_map[++i])
	{
		j = -1;
		while (mini_map[i][++j])
		{
			if (ft_strchr("NESW", mini_map[i][j]))
			{
				flag++;
				player->x = i;
				player->y = j;
			}
			else if (mini_map[i][j] != ' ' && mini_map[i][j] != '0'
					&& mini_map[i][j] != '1')
				return (store_to_error(&var->error, "Wrong caracter"), 1);
		}
	}
	if (flag != 1)
		return (store_to_error(&var->error, "On Player"), 1);
	return (0);
}

void	parse_ss(char **s, int *check, int *countt, int *i)
{
	*i = 0;
	if ((**s != '\n' && **s != ' ') && *check == 0)
		*check = 1;
	else if (**s == '\n' && *check == 1)
	{
		*check = 0;
		(*countt)++;
	}
}

void	parse_s(char **s, int count)
{
	int	check;
	int	countt;
	int	i;

	check = 0;
	countt = 0;
	while (**s)
	{
		parse_ss(s, &check, &countt, &i);
		if (countt == count)
			break ;
		(*s)++;
	}
	while (s[0][i])
		if (s[0][i] == '\n' || s[0][i] == ' ')
			i++;
	else
		break ;
	if (s[0][i - 1] == ' ')
		i--;
	while (s[0][i] == ' '
			&& i--);
	*s += (i);
}
