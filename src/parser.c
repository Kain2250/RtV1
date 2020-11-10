/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:00:31 by ecelsa            #+#    #+#             */
/*   Updated: 2020/11/10 17:55:53 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "parser.h"

void		fill_parse_var(t_sub_parser *sub, char *line, char *param)
{
	if (ft_strequ(line, "opoint"))
		sub->opoint = charsplit_to_tvec(param, ',');
	else if (ft_strequ(line, "rot"))
		sub->rot = charsplit_to_tvec(param, ',');
	else if (ft_strequ(line, "center"))
		sub->center = charsplit_to_tvec(param, ',');
	else if (ft_strequ(line, "axis"))
		sub->axis = charsplit_to_tvec(param, ',');
	else if (ft_strequ(line, "norm"))
		sub->norm = charsplit_to_tvec(param, ',');
	else if (ft_strequ(line, "color"))
		sub->color = charsplit_to_tcolor(param, ',');
	else if (ft_strequ(line, "rad"))
		sub->rad = ft_atof(param);
	else if (ft_strequ(line, "specular"))
		sub->specular = ft_atof(param);
	else if (ft_strequ(line, "type"))
		sub->type = type_of_light(param);
	else if (ft_strequ(line, "intens"))
		sub->intens = ft_atof(param);
	else if (ft_strequ(line, "on"))
		sub->on = true_or_false(param);
	else if (ft_strequ(line, "angle"))
		sub->angle = ft_atof(param);
}

void		parse_block(int fd, int block, char **line, t_rt *rt)
{
	char			*sub_line;
	char			**arr;
	t_sub_parser	sub;

	ft_bzero((void **)&sub, sizeof(t_sub_parser));
	sub.fr = -1;
	sub_line = ft_strtrim(*line);
	ft_strdel(line);
	while ((sub_line && sub_line[0] != '[') && sub.fr != 0)
	{
		arr = ft_strsplit(sub_line, '=');
		ft_strdel(&sub_line);
		if ((ft_arrlen((void **)arr) == 2))
		{
			ft_strdel(line);
			*line = ft_strtrim(arr[0]);
			fill_parse_var(&sub, *line, arr[1]);
		}
		ft_free_split(arr);
		ft_strdel(line);
		sub.fr = get_next_line(fd, line);
		sub_line = ft_strtrim(*line);
	}
	ft_strdel(&sub_line);
	fill_block(block, rt, sub);
}

int			parse_change_block(char *line)
{
	char	*sub_line;
	int		block;

	block = 0;
	if ((sub_line = ft_strtrim(line)))
	{
		if (ft_strncmp(line, SPHERE_T, ft_strlen(SPHERE_T)) == 0)
			block = SPHERE;
		else if (ft_strncmp(line, CYLINDER_T, ft_strlen(CYLINDER_T)) == 0)
			block = CYLINDER;
		else if (ft_strncmp(line, CONE_T, ft_strlen(CONE_T)) == 0)
			block = CONE;
		else if (ft_strncmp(line, PLANE_T, ft_strlen(PLANE_T)) == 0)
			block = PLANE;
		else if (ft_strncmp(line, LIGHT_T, ft_strlen(LIGHT_T)) == 0)
			block = LIGHT;
		else if (ft_strncmp(line, CAM_T, ft_strlen(CAM_T)) == 0)
			block = CAM;
		ft_strdel(&sub_line);
	}
	return (block);
}

int			parse_fail(char *file_name, t_rt *rt)
{
	int		fd;
	char	*line;
	int		block;

	if (!(blocks_count(file_name, &rt->max_shape, &rt->max_light)))
		return (0);
	if ((fd = open(file_name, O_RDONLY)) > 0)
	{
		rt->shapes = (t_shape*)malloc(sizeof(t_shape) * rt->max_shape);
		rt->light = (t_light*)malloc(sizeof(t_light) * rt->max_light);
		ft_bzero(rt->shapes, sizeof(t_shape) * rt->max_shape);
		ft_bzero(rt->light, sizeof(t_light) * rt->max_light);
		block = 0;
		while (get_next_line(fd, &line))
		{
			if (block != 0)
				parse_block(fd, block, &line, rt);
			block = parse_change_block(line);
			ft_strdel(&line);
		}
		close(fd);
		return (1);
	}
	return (0);
}
