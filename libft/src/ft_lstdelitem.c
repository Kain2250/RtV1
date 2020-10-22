/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelitem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwing <cwing@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 22:30:55 by kain2250          #+#    #+#             */
/*   Updated: 2020/02/09 00:37:51 by cwing            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelitem(t_list **alst, t_list *item)
{
	t_list		*list;
	t_list		*prev_item;

	list = *alst;
	prev_item = *alst;
	if (prev_item == item)
	{
		*alst = prev_item->next;
		free(item);
		item = NULL;
		return ;
	}
	list = list->next;
	while (list)
	{
		if (list == item)
		{
			prev_item->next = list->next;
			free(item);
			item = NULL;
			return ;
		}
		prev_item = list;
		list = list->next;
	}
}
