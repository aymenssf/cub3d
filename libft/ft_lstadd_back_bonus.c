/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:41:55 by aassaf            #+#    #+#             */
/*   Updated: 2024/02/14 12:37:08 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lastone;

	if (!lst || !new)
		return ;
	lastone = ft_lstlast(*lst);
	if (lastone == NULL)
		*lst = new;
	else
		lastone->next = new;
}
