/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:00:01 by bdrinkin          #+#    #+#             */
/*   Updated: 2019/11/04 23:09:20 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*head;
	const char	*tmp;
	size_t		i;

	if (!*needle)
		return ((char *)haystack);
	tmp = needle;
	while (*haystack && len)
	{
		head = haystack;
		i = 0;
		while ((*haystack == *needle) && *needle && i < len)
		{
			++haystack;
			++needle;
			++i;
		}
		if (!*needle)
			return ((char *)head);
		needle = tmp;
		haystack = head + 1;
		--len;
	}
	return (0);
}
