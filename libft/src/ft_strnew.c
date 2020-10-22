/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 23:34:47 by bdrinkin          #+#    #+#             */
/*   Updated: 2019/11/04 23:09:19 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	if ((str = (char *)malloc(sizeof(*str) * (size + 1))) == 0)
		return (NULL);
	i = 0;
	while (i <= size)
		str[i++] = 0;
	return (str);
}
