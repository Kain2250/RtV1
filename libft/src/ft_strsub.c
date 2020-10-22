/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 04:55:04 by bdrinkin          #+#    #+#             */
/*   Updated: 2019/11/16 18:48:12 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char	*cpy;
	size_t	i;
	size_t	j;

	if (s == 0)
		return (NULL);
	if ((cpy = (char *)malloc(sizeof(char) * (len + 1))) == 0)
		return (NULL);
	i = start;
	j = 0;
	while (i < start + len)
	{
		cpy[j] = s[i];
		++j;
		++i;
	}
	cpy[j] = 0;
	return (cpy);
}
