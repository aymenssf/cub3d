/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:50:16 by yaboulan          #+#    #+#             */
/*   Updated: 2023/11/13 01:42:46 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;
	int		i;
	int		l;

	if (!s)
		return (0);
	i = 0;
	l = ft_strlen(s);
	p = malloc(l + 1);
	if (!p)
		return (0);
	while (i < l)
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
// void sampleFunction(unsigned int index, char *c)
// {

//     (*c)++;
// }

// int main(void)
// {

//     char testString[] = "Hello, World!";

//     printf("Before: %s\n", testString);

//     ft_striteri(testString, sampleFunction);

//     printf("After: %s\n", testString);

//     return 0;
// }
