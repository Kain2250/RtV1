/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 15:33:32 by bdrinkin          #+#    #+#             */
/*   Updated: 2019/11/04 23:09:27 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strstr(const char *haystack, const char *needle)
{
	const char	*ret;
	const char	*temp;

	if (!*needle)
		return ((char *)haystack);
	temp = needle;
	while (*haystack)
	{
		ret = haystack;
		while ((*haystack == *needle) && *needle)
		{
			++haystack;
			++needle;
		}
		if (!*needle)
			return ((char *)ret);
		needle = temp;
		haystack = ret + 1;
	}
	return (NULL);
}
