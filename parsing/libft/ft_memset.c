/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:15:41 by yaboulan          #+#    #+#             */
/*   Updated: 2023/11/06 23:41:31 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*i;
	size_t			j;

	i = (unsigned char *)s;
	j = 0;
	while (j < n)
	{
		i[j] = (unsigned char)c;
		j++;
	}
	return (i);
}
