/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 13:21:28 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/02/10 21:54:23 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_chr(char const *s, char c)
{
	int		i;

	i = 0;
	while (*s != '\0')
	{
		while (*s && *s != c)
			s++;
		i++;
		while (*s && *s == c)
			s++;
	}
	return (i);
}

static char	**free_words(char **word, int size)
{
	int		i;

	i = 0;
	while (i < size)
		free(word[i++]);
	free(word);
	return (NULL);
}

static int	ft_word_length(char const *s, char c)
{
	int		i;

	while (*s)
	{
		if (*s != c)
			break ;
		s++;
	}
	i = 0;
	while (*s)
	{
		if (*s == c)
			break ;
		i++;
		s++;
	}
	return (i);
}

static char	**loop_strplit(char const *s, char **word,
		char separator, int nbr_words)
{
	int		i;
	int		size;

	i = 0;
	while (i < nbr_words)
	{
		size = ft_word_length(s, separator);
		if (!(word[i] = (char *)malloc(sizeof(char) * (size + 1))))
			return (free_words(word, i));
		ft_strncpy(word[i], s, size);
		word[i][size] = 0;
		s += size;
		while (*s == separator)
			++s;
		++i;
	}
	word[i] = 0;
	return (word);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**word;
	int		nbr_words;

	if (s == 0)
		return (0);
	while (*s == c)
		++s;
	nbr_words = ft_word_chr(s, c);
	if (!(word = (char **)ft_memalloc(sizeof(char *) * (nbr_words + 1))))
		return (0);
	return (loop_strplit(s, word, c, nbr_words));
}
