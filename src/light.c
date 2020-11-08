/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:02:44 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/08 17:07:09 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		find_intensity(t_vec3 intersect, t_light *is_light,
				t_vec3 norm, int max_light)
{
	double	intensity;
	int		i;

	intensity = 0;
	i = -1;
	while (++i < max_light)
	{
		if (is_light[i].on == false)
			continue ;
		if (is_light[i].type == e_ambient)
			intensity += is_light[i].intens;
		else if (is_light[i].type == e_point)
		{
			intensity += light(intersect, is_light[i].dir,
				norm, is_light[i].intens);
		}
		else
			intensity += is_light[i].intens;
	}
	return (clamp(intensity, 0., 1.));
}

t_color		lighting_calculation(t_intersect param, t_light *light,
				t_d_norm dn, t_rt *rt)
{
	t_color	color;
	int		i;
	t_vec3	lvec;
	t_vec3	n_p;

	i = -1;
	color = mix_color(param.color, find_intensity(param.intersect, light,
		dn.norm, light->max_light));
	while (++i < light->max_light)
	{
		if (light[i].type == e_point && light[i].on == true)
		{
			lvec = parallel_transfer3(light[i].dir, param.intersect);
			if (dot3(lvec, dn.norm) < 0.)
				continue ;
			n_p = addition3(param.intersect, cross_scalar(dn.norm, 1e-4));
			if (shadow_calc(light[i], ray_intersect(lvec, n_p, rt->shapes,
				rt->max_shape), n_p, &color))
				continue ;
			color = (param.shine != 0.) ? shine_calc((t_shine){lvec, dn.norm,
				color, light[i], dn.dir, param.shine}) : color;
		}
	}
	return (color);
}
