/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:00:31 by ecelsa            #+#    #+#             */
/*   Updated: 2020/11/10 02:35:40 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			blocks_count(char *file_name, int *shapes, int *lights)
{
	char		*line;
	char		*sub_line;
	int			fd;

	if ((fd = open(file_name, O_RDONLY)))
	{
		while ((get_next_line(fd, &line)))
		{
			sub_line = ft_strtrim(line);
			ft_strdel(&line);
			if ((ft_strncmp(sub_line, SPHERE_T, ft_strlen(SPHERE_T)) == 0) ||
				(ft_strncmp(sub_line, CYLINDER_T, ft_strlen(CYLINDER_T)) == 0)
				|| (ft_strncmp(sub_line, CONE_T, ft_strlen(CONE_T)) == 0) ||
					(ft_strncmp(sub_line, PLANE_T, ft_strlen(PLANE_T))) == 0)
				(*shapes)++;
			if ((ft_strncmp(sub_line, LIGHT_T, ft_strlen(LIGHT_T))) == 0)
				(*lights)++;
			ft_strdel(&sub_line);
		}
		ft_strdel(&sub_line);
		ft_strdel(&line);
		close(fd);
	}
	return (1);
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

void		fill_block(int block, t_rt *rt, t_sub_parser sub)
{
	int		i;

	i = iter_block(block, rt);
	if (block == CAM)
		create_cam(rt, sub);
	else if (block == LIGHT)
	{
		if (sub.type == 1)
			rt->light[i] = create_light_ambient(sub, rt->max_light);
		else
			rt->light[i] = create_light_point(sub, rt->max_light);
	}
	else if (block && block < 5)
	{
		if (block == CYLINDER)
			rt->shapes[i] = create_cilinder(sub);
		else if (block == SPHERE)
			rt->shapes[i] = create_sphere(sub);
		else if (block == CONE)
			rt->shapes[i] = create_cone(sub);
		else if (block == PLANE)
			rt->shapes[i] = create_plane(sub);
	}
}

t_vec3		charsplit_to_tvec(char *str, char split)
{
	char	**arr;
	t_vec3	sub;

	ft_bzero(&sub, sizeof(t_vec3));
	arr = ft_strsplit(str, split);
	if (ft_arrlen((void **)arr) == 3)
		sub = (t_vec3){.x = atof(arr[0]), .y = atof(arr[1]), .z = atof(arr[2])};
	ft_free_split(arr);
	return (sub);
}

t_color		charsplit_to_tcolor(char *str, char split)
{
	char	**arr;
	t_color	sub;

	ft_bzero(&sub, sizeof(t_color));
	arr = ft_strsplit(str, split);
	if (ft_arrlen((void **)arr) == 3)
		sub = (t_color){.red = atof(arr[0]), .green = atof(arr[1]),
														.blue = atof(arr[2])};
	ft_free_split(arr);
	return (sub);
}

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
		sub->rad = atof(param);
	else if (ft_strequ(line, "specular"))
		sub->specular = atof(param);
	else if (ft_strequ(line, "type"))
		sub->type = atof(param);
	else if (ft_strequ(line, "intens"))
		sub->intens = atof(param);
	else if (ft_strequ(line, "on"))
		sub->on = atoi(param);
	else if (ft_strequ(line, "angle"))
		sub->angle = atof(param);
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

	fd = open(file_name, O_RDONLY);
	rt->max_light = 0;
	rt->max_shape = 0;
	blocks_count(file_name, &rt->max_shape, &rt->max_light);
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
	return (0);
}
