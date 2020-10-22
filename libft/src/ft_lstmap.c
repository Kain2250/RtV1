/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 21:22:59 by bdrinkin          #+#    #+#             */
/*   Updated: 2019/11/04 23:06:53 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*null;
	t_list	**fin;
	t_list	**new;

	null = NULL;
	new = &null;
	fin = new;
	while (lst != NULL)
	{
		*new = f(lst);
		new = &(*new)->next;
		lst = lst->next;
	}
	return (*fin);
}
