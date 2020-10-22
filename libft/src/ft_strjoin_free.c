/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 00:45:22 by kain2250          #+#    #+#             */
/*   Updated: 2020/01/19 14:21:52 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin_free(char *s1, char *s2)
{
	char	*temp;

	if (!s1 || !s2)
		return (NULL);
	temp = ft_strjoin(s1, s2);
	if (!(temp))
		return (NULL);
	free(s1);
	free(s2);
	return (temp);
}
