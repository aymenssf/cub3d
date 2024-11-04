/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:16:30 by yaboulan          #+#    #+#             */
/*   Updated: 2023/11/03 21:16:41 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*chaine;
	size_t	length;
	size_t	i;

	length = ft_strlen(s);
	i = 0;
	if (s == NULL || start >= length)
		return (ft_strdup(""));
	if (len > (length - start))
		len = length - start;
	chaine = (char *)malloc((len) + 1);
	if (!chaine)
		return (NULL);
	while ((i + start) < length && i < len)
	{
		chaine[i] = s[i + start];
		i++;
	}
	chaine[i] = 0;
	return (chaine);
}
// int main(int argc, char const *argv[])
// {
// 	const char *test = "ahmed";
// 	printf("%ld",(long)SIZE_MAX);
// 	printf("%s \n", ft_substr(test,2,(long)SIZE_MAX));

// 	return (0);
// }
