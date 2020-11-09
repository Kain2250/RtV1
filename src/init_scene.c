/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:10:40 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/08 22:57:09 by kain2250         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_shape		create_sphere(t_vec3 center, t_color color,
				double rad, double specular)
{
	t_shape	sphere;

	sphere.center = center;
	sphere.color = color;
	sphere.rad = rad;
	sphere.specular = specular;
	sphere.type = e_sphere;
	return (sphere);
}

t_shape		create_plane(t_vec3 center, t_color color,
				t_vec3 norm, double specular)
{
	t_shape	plane;

	plane.center = center;
	plane.color = color;
	plane.rad = INFINITY;
	plane.specular = specular;
	plane.norm = normalize(norm);
	plane.type = e_plane;
	return (plane);
}

t_shape		create_cone(t_vec3 center, t_con_ax a,
				t_color color, double specular)
{
	t_shape	cone;

	cone.center = center;
	cone.axis = normalize(a.axis);
	cone.color = color;
	cone.k = tan(M_PI_2 / a.angle);
	cone.pow_k = cone.k * cone.k;
	cone.specular = specular;
	cone.type = e_conus;
	return (cone);
}

t_shape		create_cilinder(t_vec3 center, t_cil_ax a,
				t_color color, double specular)
{
	t_shape	cil;

	cil.center = center;
	cil.axis = normalize(a.axis);
	cil.color = color; 
	cil.rad = a.rad;
	cil.specular = specular;
	cil.type = e_cilindr;
	return (cil);
}

t_light		create_light_point(t_vec3 point, double intens, int max_light)
{
	t_light	light;

	light.dir = point;
	light.intens = clamp(intens, 0, 1);
	light.on = true;
	light.type = e_point;
	light.max_light = max_light;
	return (light);
}

t_light		create_light_ambient(double intens, int max_light)
{
	t_light	light;

	light.type = e_ambient;
	light.intens = clamp(intens, 0, 1);
	light.on = true;
	light.max_light = max_light;
	return (light);
}

void		create_cam(t_rt *rt, t_vec3 angle_rot, t_vec3 opoint)
{
	rt->rot[0] = clamp(angle_rot.x, 0, 360) * M_PI_180;
	rt->rot[1] = clamp(angle_rot.y, 0, 360) * M_PI_180;
	rt->rot[2] = clamp(angle_rot.z, 0, 360) * M_PI_180;
	rt->cam.opoint = opoint;
}

void		init_cam(t_rt *rt)
{
	int	i;

	i = 0;
	create_cam(rt, (t_vec3){0, 0, 0}, (t_vec3){0., 0., -20.});
	rt->max_shape = 17;
	rt->shapes = ft_memalloc(sizeof(t_shape) * rt->max_shape);
	rt->shapes[i++] = create_sphere((t_vec3){-6., -5., 0.},
		BROWN_COLOR, 1.5, 10.);
	rt->shapes[i++] = create_sphere((t_vec3){6., -5., 0.},
		BROWN_COLOR, 1.5, 10.);
	rt->shapes[i++] = create_sphere((t_vec3){-6., 5., 0.},
		BROWN_COLOR, 1.5, 10.);
	rt->shapes[i++] = create_sphere((t_vec3){6., 5., 0.},
		BROWN_COLOR, 1.5, 10.);
	rt->shapes[i++] = create_sphere((t_vec3){-6., -5., 18.},
		BROWN_COLOR, 1.5, 10.);
	rt->shapes[i++] = create_sphere((t_vec3){-6., -5., 18.},
		BROWN_COLOR, 1.5, 10.);
	rt->shapes[i++] = create_sphere((t_vec3){-6., 5., 18.},
		BROWN_COLOR, 1.5, 10.);
	rt->shapes[i++] = create_sphere((t_vec3){6., 5., 18.},
		BROWN_COLOR, 2., 10.);
	rt->shapes[i++] = create_sphere((t_vec3){0., -3., 0.},
		RED_COLOR, 0.5, 10.);
	rt->shapes[i++] = create_cilinder((t_vec3){6., 0., 18.},
		(t_cil_ax){1., (t_vec3){0., 1., 0.}}, L_GREEN_COLOR, 10.);
	rt->shapes[i++] = create_cilinder((t_vec3){-6., 0., 18.},
		(t_cil_ax){1., (t_vec3){0., 1., 0.}}, L_GREEN_COLOR, 10.);
	rt->shapes[i++] = create_cilinder((t_vec3){6., 0., 0.},
		(t_cil_ax){1., (t_vec3){0., 1., 0.}}, L_GREEN_COLOR, 10.);
	rt->shapes[i++] = create_cilinder((t_vec3){-6., 0., 0.},
		(t_cil_ax){1., (t_vec3){0., 1., 0.}}, L_GREEN_COLOR, 10.);
	rt->shapes[i++] = create_plane((t_vec3){0., 0., 29.},
		WHIGHT_COLOR, (t_vec3){0., 0., -1.}, 0);
	rt->shapes[i++] = create_plane((t_vec3){0., -5., 0.},
		PURPLE_COLOR, (t_vec3){0., 1., 0.}, 0);
	rt->shapes[i++] = create_plane((t_vec3){0., 5., 0.},
		YELLOW_COLOR, (t_vec3){0., -1., 0.}, 0);
	rt->shapes[i++] = create_cone((t_vec3){0., 0., 0.},
		(t_con_ax){6, (t_vec3){0., 1., 0.}}, YELLOW_COLOR, 10.);
	rt->max_light = 3;
	rt->light = ft_memalloc(sizeof(t_light) * rt->max_light);
	i = 0;
	rt->light[i++] = create_light_point((t_vec3){-20, 3, -20},
		0.4, rt->max_light);
	rt->light[i++] = create_light_point((t_vec3){20, 3, -20},
		0.5, rt->max_light);
	rt->light[i++] = create_light_ambient(0.2, rt->max_light);
}
