/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboulan <yaboulan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:44:41 by yaboulan          #+#    #+#             */
/*   Updated: 2023/11/13 02:06:08 by yaboulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*head;
	t_list	*node;

	head = lst;
	new_lst = NULL;
	while (head)
	{
		node = ft_lstnew(f(head->content));
		if (!node)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, node);
		head = head->next;
	}
	return (new_lst);
}
// void *f(void *ptr)
// {
// 	ptr = (char *)"hh";
// 	return ptr;
// }
// void print(void *ptr)
// {
// 	printf("%s",(char *)ptr);
// }

// int main(int argc, char const *argv[])
// {
// 	t_list *node = ft_lstnew("ali");
// 	t_list *node1 = ft_lstnew("ana");
// 	ft_lstadd_back(&node, node1);

// 	// ft_lstiter(node,f);
// 	t_list *newList = ft_lstmap(node, f, free);
// 	ft_lstiter(newList,print);

// 	return 0;
// }