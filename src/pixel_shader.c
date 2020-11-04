/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_shader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 20:24:57 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/04 19:25:46 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		disk_of_shapes(t_vec3 dir, t_vec3 opoint, t_shape shape)
{
	double	point;

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

double			equal_min(double min[2], int i, t_intersect *param)
{
	if (min[1] < min[0])
	{
		param->iter = i;
		return (min[1]);
	}
	return (min[0]);
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
		// if (min[1] < min[0])
		// {
		// 	param.iter = i;
		// 	min[0] = min[1];
		// }
	}
	if (min[0] != INFINITY)
	{
		param.intersect = addition3(opoint, cross_scalar(dir, min[0]));
		param.point = min[0];
		param.shine = shape[param.iter].specular;
		color_fill(&param.color, shape[param.iter].color);
	}
	else
		param.color = (t_color){0, 0, 0};
	return (param);
}

t_vec3		plane_limiter(t_vec3 intersect, t_shape shape)
{
	if (!(mod3(subtraction3(intersect, shape.center)) <= shape.rad))
		return ((t_vec3){INFINITY, INFINITY, INFINITY});
	return (intersect);
}

t_color		lighting_calculation(t_intersect param, t_light *light,
				t_vec3 norm, t_vec3 dir, t_rt *rt)
{
	t_color	color;
	int		i;
	double	proj;
	t_vec3	lvec;
	double	temp;
	t_vec3	a;
	t_vec3	r;
	int		i_temp;
	t_vec3	n_p;
	t_intersect	itr;

	i_temp = -1;
	if (param.color.red == 0 && param.color.green == 0 && param.color.blue == 0)
		return ((t_color){0, 0, 0});
	i = -1;
	color = mix_color(param.color, find_intensity(param.intersect, light, norm, light->max_light));
	while (++i < light->max_light)
	{
		if (light[i].type == e_point && light[i].on == true)
		{
			lvec = normalize(subtraction3(light[i].dir, param.intersect));
			if (dot3(lvec, norm) < 0.)
				continue ;
			n_p = addition3(param.intersect, cross_scalar(norm, 1e-4));
			itr = ray_intersect(lvec, n_p, rt->shapes, rt->max_shape);
			if (itr.point >= 0. && itr.point <= mod3(subtraction3(light[i].dir, n_p)))
			{
				color = mix_color(color, 1 - light[i].intens);
				continue ;
			}
			temp = 0;
			if (param.shine != 0.)
			{
				proj = dot3(lvec, norm);
				a = addition3(cross_scalar(norm, proj), cross_scalar(lvec, -1));
				r = addition3(cross_scalar(norm, proj), a);
				temp = dot3(r, normalize(cross_scalar(dir, -1.)));
				temp = pow(temp, param.shine) * light[i].intens;
			}
			if (temp >= 0.)
			{
				a = (t_vec3){color.red, color.green, color.blue};
				t_vec3 b = (t_vec3){255, 255, 255};
				a = cross_scalar(a, 1. - temp);
				b = cross_scalar(b, temp);
				t_vec3 c = addition3(a, b);
				color = (t_color){c.x, c.y, c.z};
			}
		}
	}
	return (color);
}

t_color		pixel_shader(t_vec3 dir, t_vec3 opoint, t_rt *rt)
{
	t_intersect	param;
	t_vec3		norm;
	t_color		color;

	param = ray_intersect(dir, opoint, rt->shapes, rt->max_shape);
	norm = surface_norm(param, rt->shapes[param.iter], opoint, dir);
	color = lighting_calculation(param, rt->light, norm, dir, rt);
	return (color);
}
