/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:57:09 by yaboulan          #+#    #+#             */
/*   Updated: 2023/11/07 00:31:15 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cal(int n)
{
	int	l;

	l = 0;
	if (n < 0)
		l = 1;
	while (n)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		l;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	l = cal(n);
	p = malloc(l + 1);
	if (!p)
		return (0);
	if (n < 0)
	{
		n *= -1;
		p[0] = '-';
	}
	p[l--] = '\0';
	while (n)
	{
		p[l] = (n % 10) + 48;
		n = n / 10;
		l--;
	}
	return (p);
}

// int	main (void)
// {
// 	printf("%s", ft_itoa(0));
// }