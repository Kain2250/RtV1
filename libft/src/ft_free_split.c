/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 22:39:19 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/10 01:22:54 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split != NULL)
	{
		while (split[i])
		{
			ft_strdel(&split[i]);
			i++;
		}
		free(split);
		split = NULL;
	}
}
