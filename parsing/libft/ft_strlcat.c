/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:15:58 by yaboulan          #+#    #+#             */
/*   Updated: 2023/11/07 02:17:36 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest;
	size_t	srcc;
	size_t	i;

	dest = ft_strlen(dst);
	srcc = ft_strlen(src);
	i = 0;
	if (size <= dest)
		return (size + srcc);
	while (src[i] && (i + dest) < size - 1)
	{
		dst[dest + i] = src[i];
		i++;
	}
	dst[dest + i] = 0;
	return (dest + srcc);
}
