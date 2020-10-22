/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 23:45:53 by bdrinkin          #+#    #+#             */
/*   Updated: 2019/11/04 23:09:21 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ss;

	ss = (char*)(s);
	i = ft_strlen(ss);
	while (i >= 0)
	{
		if (ss[i] == c)
			return (&ss[i]);
		--i;
	}
	return (NULL);
}
