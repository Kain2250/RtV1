/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:50:31 by ecelsa            #+#    #+#             */
/*   Updated: 2020/11/10 17:51:03 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "parser.h"

int			line_is_text_block(char *sub_line)
{
	if ((ft_strncmp(sub_line, SPHERE_T, ft_strlen(SPHERE_T)) == 0) ||
				(ft_strncmp(sub_line, CYLINDER_T, ft_strlen(CYLINDER_T)) == 0)
				|| (ft_strncmp(sub_line, CONE_T, ft_strlen(CONE_T)) == 0) ||
					(ft_strncmp(sub_line, PLANE_T, ft_strlen(PLANE_T))) == 0)
		return (1);
	return (0);
}

int			is_file_valid(char *file_name)
{
	int		fd;
	char	buf[2];
	int		fr;

	if ((fd = open(file_name, O_RDONLY)))
	{
		if ((fr = read(fd, &buf, 1)) > 0)
		{
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int			blocks_count(char *file_name, int *shapes, int *lights)
{
	char		*line;
	char		*sub_line;
	int			fd;

	if (!(is_file_valid(file_name)))
		return (0);
	(*shapes) = 0;
	(*lights) = 0;
	if ((fd = open(file_name, O_RDONLY)))
	{
		while ((get_next_line(fd, &line)))
		{
			sub_line = ft_strtrim(line);
			ft_strdel(&line);
			if (line_is_text_block(sub_line))
				(*shapes)++;
			if ((ft_strncmp(sub_line, LIGHT_T, ft_strlen(LIGHT_T))) == 0)
				(*lights)++;
			ft_strdel(&sub_line);
		}
		ft_strdel(&sub_line);
		ft_strdel(&line);
		close(fd);
	}
	return ((*shapes < 1 || *lights < 1) ? 0 : 1);
}

int			ft_arrlen(void **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

int			iter_block(int block, t_rt *rt)
{
	int		i;

	i = 0;
	if (block == LIGHT)
		while (i < rt->max_light && rt->light[i].fil != 0)
			i++;
	else if (block && block < 5)
		while (i < rt->max_shape && rt->shapes[i].fil != 0)
			i++;
	return (i);
}
