/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sub2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:50:31 by ecelsa            #+#    #+#             */
/*   Updated: 2020/11/10 17:56:23 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "parser.h"

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
		sub = (t_vec3){.x = ft_atof(arr[0]), .y = ft_atof(arr[1]),
														.z = ft_atof(arr[2])};
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
		sub = (t_color){.red = ft_atof(arr[0]), .green = ft_atof(arr[1]),
													.blue = ft_atof(arr[2])};
	ft_free_split(arr);
	return (sub);
}

bool		true_or_false(char *str)
{
	bool ret;
	char *sub_line;

	ret = 0;
	sub_line = ft_strtrim(str);
	if (ft_memcmp(ft_strlowcase(sub_line), "true", 4) == 0)
		ret = true;
	else if (ft_memcmp(ft_strlowcase(sub_line), "false", 5) == 0)
		ret = false;
	else
		ret = ft_atoi(sub_line);
	free(sub_line);
	return (ret);
}

int			type_of_light(char *str)
{
	int		ret;
	char	*sub_line;

	ret = 0;
	sub_line = ft_strtrim(str);
	if (ft_memcmp(ft_strlowcase(sub_line), "ambient", 7) == 0)
		ret = 1;
	else if (ft_memcmp(ft_strlowcase(sub_line), "point", 5) == 0)
		ret = 2;
	else
		ret = ft_atoi(sub_line);
	free(sub_line);
	return (ret);
}
