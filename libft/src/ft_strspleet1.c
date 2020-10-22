/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspleet1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 06:20:49 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/02/10 06:25:16 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strsplit_words(char const *s, char c)
{
	int		i;
	int		n;
	int		m;

	i = 0;
	n = 0;
	m = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == c) && (m == 1))
			m = 0;
		if ((m == 0) && (s[i] != c))
		{
			m = 1;
			n++;
		}
		i++;
	}
	return (n);
}

int			ft_strsplit_len(char const *s, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while ((s[i] != c) && (s[i] != '\0'))
	{
		i++;
		len++;
	}
	return (len);
}

char		**ft_strsplit1(char const *s, char c)
{
	int		m;
	int		words;
	char	**finish;

	m = 0;
	words = ft_strsplit_words(s, c);
	finish = (char **)malloc((words + 1) * sizeof(char *));
	if (finish == NULL)
		return (NULL);
	while (words--)
	{
		while ((*s == c) && (*s != '\0'))
			s++;
		finish[m] = ft_strsub(s, 0, ft_strsplit_len(s, c));
		if (finish[m] == NULL)
			return (NULL);
		s = s + ft_strsplit_len(s, c);
		m++;
	}
	finish[m] = NULL;
	return (finish);
}
