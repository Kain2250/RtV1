/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 01:53:27 by bdrinkin          #+#    #+#             */
/*   Updated: 2019/11/04 23:06:41 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_push_back(t_list **alst,
		void const *content, size_t content_size)
{
	if (alst)
	{
		while (*alst)
			alst = &((*alst)->next);
		*alst = ft_lstnew(content, content_size);
	}
}
