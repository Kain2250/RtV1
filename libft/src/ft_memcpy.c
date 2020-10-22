/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 22:57:33 by bdrinkin          #+#    #+#             */
/*   Updated: 2019/11/04 23:07:17 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (n + 1 > n)
	{
		i = 0;
		while (n != 0)
		{
			if (dst == NULL && src == NULL)
				break ;
			((char*)dst)[i] = ((char*)src)[i];
			i++;
			n--;
		}
	}
	return (dst);
}
