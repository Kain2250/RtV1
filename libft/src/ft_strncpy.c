/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 21:43:15 by bdrinkin          #+#    #+#             */
/*   Updated: 2019/11/04 23:09:12 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	lsrc;
	size_t	i;

	i = 0;
	lsrc = ft_strlen(src);
	while (i < len)
	{
		if (i < lsrc)
		{
			dst[i] = src[i];
			i++;
		}
		else
		{
			dst[i] = '\0';
			i++;
		}
	}
	return (dst);
}
