/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 13:22:16 by bdrinkin          #+#    #+#             */
/*   Updated: 2019/11/04 23:06:39 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbr_del(int n)
{
	int		d;

	d = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		++d;
	}
	return (d);
}

static char	*ft_plus_int(int n, int len)
{
	char	*ss;

	if ((ss = (char *)malloc(sizeof(*ss) * (len + 1))))
	{
		ss[len] = '\0';
		len--;
		while (len >= 0)
		{
			ss[len] = ((n % 10) + '0');
			n = n / 10;
			len--;
		}
		return (ss);
	}
	return (NULL);
}

static char	*ft_mius_int(int n, int len)
{
	char	*ss;

	if ((ss = (char *)malloc(sizeof(*ss) * (len + 2))))
	{
		len++;
		ss[len] = '\0';
		len--;
		ss[0] = '-';
		while (len > 0)
		{
			ss[len] = ((n % 10) + '0');
			n = n / 10;
			len--;
		}
		return (ss);
	}
	return (NULL);
}

char		*ft_itoa(int n)
{
	char	*ss;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_nbr_del(n);
	if (n >= 0)
		return (ss = ft_plus_int(n, len));
	return (ss = ft_mius_int((n * -1), len));
}
