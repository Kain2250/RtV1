/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 21:06:46 by bdrinkin          #+#    #+#             */
/*   Updated: 2019/11/04 23:08:49 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*ft_strdup(const char *s1)
{
	char	*dst;

	dst = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (dst)
	{
		ft_strcpy(dst, s1);
		return (dst);
	}
	else
		return (NULL);
}
