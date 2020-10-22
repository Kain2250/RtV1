/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 21:52:59 by bdrinkin          #+#    #+#             */
/*   Updated: 2019/11/04 23:07:07 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;

	i = 0;
	if (n == 0 || (n + 1 < n))
		return (NULL);
	while (n != 0)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)&(s)[i]);
		n--;
		i++;
	}
	return (NULL);
}
