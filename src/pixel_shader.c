/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 20:24:57 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/08 20:41:55 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			disk_of_shapes(t_vec3 dir, t_vec3 opoint, t_shape shape)
{
	double		point;

	if (shape.type == e_sphere)
		point = sphere_intersect(shape, opoint, dir);
	else if (shape.type == e_conus)
		point = conus_intersect(shape, opoint, dir);
	else if (shape.type == e_cilindr)
		point = cylinder_intersect(shape, opoint, dir);
	else
		point = plane_intersect(opoint, dir, shape.center, shape.norm);
	if (point <= 0)
		point = INFINITY;
	return (point);
}

t_intersect		ray_intersect(t_vec3 dir, t_vec3 opoint,
					t_shape *shape, int count_shape)
{
	int			i;
	double		min[2];
	t_intersect	param;

	i = -1;
	min[0] = INFINITY;
	param.point = INFINITY;
	param.iter = 0;
	while (++i < count_shape)
	{
		min[1] = disk_of_shapes(dir, opoint, shape[i]);
		min[0] = equal_min(min, i, &param);
	}
	if (min[0] != INFINITY)
	{
		param.intersect = addition3(opoint, cross_scalar(dir, min[0]));
		param.point = min[0];
		param.shine = shape[param.iter].specular;
		color_fill(&param.color, shape[param.iter].color);
	}
	else
		param.color = BLACK_COLOR;
	return (param);
}

t_color			shine_calc(t_shine s)
{
	t_4vec3		vec;
	double		temp;
	double		proj;
	t_vec3		scalar;

	proj = dot3(s.lvec, s.norm);
	scalar = cross_scalar(s.norm, proj);
	vec.a = addition3(scalar, cross_scalar(s.lvec, -1));
	vec.r = addition3(scalar, vec.a);
	temp = dot3(vec.r, normalize(cross_scalar(s.dir, -1.)));
	temp = pow(temp, s.shine) * s.light.intens;
	if (temp >= 0.)
	{
		vec.a = (t_vec3){s.color.red, s.color.green, s.color.blue};
		vec.b = (t_vec3){255, 255, 255};
		vec.a = cross_scalar(vec.a, 1. - temp);
		vec.b = cross_scalar(vec.b, temp);
		vec.c = addition3(vec.a, vec.b);
		s.color = (t_color){vec.c.x, vec.c.y, vec.c.z};
	}
	return (s.color);
}

bool			shadow_calc(t_light light, t_intersect itr,
					t_vec3 n_p, t_color *color)
{
	if (itr.point >= 0. && itr.point <= mod3(subtraction3(light.dir, n_p)))
	{
		*color = mix_color(*color, 1 - light.intens);
		return (true);
	}
	return (false);
}

t_color			pixel_shader(t_vec3 dir, t_vec3 opoint, t_rt *rt)
{
	t_intersect	param;
	t_vec3		norm;
	t_color		color;

	param = ray_intersect(dir, opoint, rt->shapes, rt->max_shape);
	if (param.color.red == 0 && param.color.green == 0 && param.color.blue == 0)
		return (BLACK_COLOR);
	norm = surface_norm(param, rt->shapes[param.iter], opoint, dir);
	color = lighting_calculation(param, rt->light, (t_d_norm){dir, norm}, rt);
	return (color);
}
