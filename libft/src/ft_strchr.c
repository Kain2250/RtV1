/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:52:56 by bdrinkin          #+#    #+#             */
/*   Updated: 2019/11/04 23:07:46 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char		*ft_strchr(const char *s, int c)
{
	char	*s1;

	s1 = (char*)s;
	if (c == '\0' && ft_strlen(s1) == 2)
		return ((char *)s);
	while (s1)
	{
		if (((char *)s1)[0] == (char)c)
		{
			break ;
		}
		if (s1[0] == '\0')
			return (NULL);
		++s1;
	}
	return (s1);
}
