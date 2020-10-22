/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:19:00 by bdrinkin          #+#    #+#             */
/*   Updated: 2019/11/16 19:07:11 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*ptr;

	if ((ptr = (t_list *)malloc(sizeof(t_list))))
	{
		if (!(ptr->content = malloc(sizeof(content) * (content_size))))
			return (NULL);
		if (content == NULL)
		{
			ptr->content = NULL;
			ptr->content_size = 0;
			ptr->next = NULL;
			return (ptr);
		}
		ft_memcpy(ptr->content, content, content_size);
		ptr->content_size = content_size;
		ptr->next = NULL;
		return (ptr);
	}
	return (NULL);
}
