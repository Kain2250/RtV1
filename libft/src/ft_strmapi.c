/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 04:07:34 by bdrinkin          #+#    #+#             */
/*   Updated: 2019/11/04 23:09:06 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ss;
	size_t	i;

	i = 0;
	if (s == 0)
		return (NULL);
	if (!(ss = (char *)malloc(sizeof(*ss) * (ft_strlen(s) + 1))))
		return (NULL);
	else
	{
		while (s[i])
		{
			ss[i] = f(i, s[i]);
			++i;
		}
		ss[i] = '\0';
	}
	return (ss);
}
