/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:48:23 by yaboulan          #+#    #+#             */
/*   Updated: 2023/11/13 02:05:31 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;
	int	l;

	i = 0;
	if (!s)
		return ;
	l = ft_strlen(s);
	while (i < l)
	{
		f(i, s++);
		i++;
	}
}
