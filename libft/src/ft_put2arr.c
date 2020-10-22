/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put2arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 19:26:17 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/07/10 19:31:44 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put2arr(int count, char **arr)
{
	int	index;

	index = 0;
	while (index != count)
	{
		ft_putstrlen(arr[index++]);
		ft_putchar('\n');
	}
}
