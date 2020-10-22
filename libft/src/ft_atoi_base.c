/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 23:13:18 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/01/22 18:59:27 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_spaces_base(const char *str, int base)
{
	char	*res;
	int		i;

	i = 0;
	while ((str[i] == '\t') || (str[i] == '\n') || (str[i] == '\v') ||
		(str[i] == '\f') || (str[i] == '\r') || (str[i] == ' '))
		i++;
	if (base == 16)
	{
		if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
			i += 2;
	}
	res = &((char *)str)[i];
	return (res);
}

static int	ft_atoi_others(const char *str, int base)
{
	int		i;
	int		res;
	char	*nstr;
	int		nbr;

	nstr = ft_spaces_base(str, base);
	i = 0;
	res = 0;
	while (nstr[i] >= '0' && nstr[i] <= (base + '0'))
	{
		nbr = nstr[i] - '0';
		res = res * base + nbr;
		i++;
	}
	return (res);
}

static int	ft_atoi_hexadec(const char *str)
{
	int		i;
	long	res;
	char	*nstr;
	int		nbr;

	i = 0;
	res = 0;
	nstr = ft_spaces_base(str, 16);
	while (nstr[i] != '\0')
	{
		nstr[i] = ft_toupper(nstr[i]);
		i++;
	}
	i = 0;
	while ((nstr[i] >= '0' && nstr[i] <= '9') || (nstr[i] >= 'A'
		&& nstr[i] <= 'F'))
	{
		nbr = nstr[i] <= '9' ? nstr[i] - '0' : nstr[i] - 55;
		res = res * 16 + nbr;
		i++;
	}
	return (res);
}

int			ft_atoi_base(const char *str, int base)
{
	if (base == 10)
		return (ft_atoi(str));
	if (base == 16)
		return (ft_atoi_hexadec(str));
	else
		return (ft_atoi_others(str, base));
}
