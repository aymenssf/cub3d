/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:15:51 by yaboulan          #+#    #+#             */
/*   Updated: 2023/11/06 23:53:04 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	i;
	char	*sa;

	i = 0;
	sa = (char *)malloc(ft_strlen(src) * sizeof(char) + 1);
	if (!sa)
		return (NULL);
	while (i < ft_strlen(src))
	{
		sa[i] = src[i];
		i++;
	}
	sa[ft_strlen(src)] = 0;
	return (sa);
}
