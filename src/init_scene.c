/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:10:40 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/09 17:41:35 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_shape		create_sphere(t_sub_parser data)
{
	t_shape	sphere;

	sphere.center = data.center;
	sphere.color = data.color;
	sphere.rad = clamp(data.rad, 0.1, INFINITY);
	sphere.specular = clamp(data.specular, 0, 10000);
	sphere.type = e_sphere;
	return (sphere);
}

t_shape		create_plane(t_sub_parser data)
{
	t_shape	plane;

	plane.center = data.center;
	plane.color = data.color;
	plane.rad = INFINITY;
	plane.specular = clamp(data.specular, 0, 10000);
	plane.norm = normalize(data.norm);
	plane.type = e_plane;
	return (plane);
}

t_shape		create_cone(t_sub_parser data)
{
	t_shape	cone;

	cone.center = data.center;
	cone.axis = normalize(data.axis);
	cone.color = data.color;
	cone.k = tan(M_PI_2 / clamp(data.angle, 2, 100));
	cone.pow_k = cone.k * cone.k;
	cone.specular = clamp(data.specular, 0, 10000);
	cone.type = e_conus;
	return (cone);
}

t_shape		create_cilinder(t_sub_parser data)
{
	t_shape	cil;

	cil.center = data.center;
	cil.axis = normalize(data.axis);
	cil.color = data.color; 
	cil.rad = clamp(data.rad, 0.1, INFINITY);
	cil.specular = clamp(data.specular, 0, 10000);
	cil.type = e_cilindr;
	return (cil);
}

t_light		create_light_point(t_sub_parser data, int max_light)
{
	t_light	light;

	light.dir = data.opoint;
	light.intens = clamp(data.intens, 0, 1);
	light.on = true;
	light.type = e_point;
	light.max_light = max_light;
	return (light);
}

t_light		create_light_ambient(t_sub_parser data, int max_light)
{
	t_light	light;

	light.type = e_ambient;
	light.intens = clamp(data.intens, 0, 1);
	light.on = true;
	light.max_light = max_light;
	return (light);
}

void		create_cam(t_rt *rt, t_sub_parser data)
{
	rt->rot.x = clamp(data.rot.x, 0, 360) * M_PI_180;
	rt->rot.y = clamp(data.rot.y, 0, 360) * M_PI_180;
	rt->rot.z = clamp(data.rot.z, 0, 360) * M_PI_180;
	rt->cam.opoint = data.opoint;
}

void		init_cam(t_rt *rt)
{
	int	i;

	i = 0;
	rt->max_shape = 17;
	rt->shapes = ft_memalloc(sizeof(t_shape) * rt->max_shape);
	rt->shapes[i++] = create_sphere((t_sub_parser){.center = (t_vec3){-6., -5., 0.}, .color = BROWN_COLOR, .rad = 1.5, .specular = 10.});
	rt->shapes[i++] = create_sphere((t_sub_parser){.center = (t_vec3){6., -5., 0.}, .color = BROWN_COLOR, .rad = 1.5, .specular = 10.});
	rt->shapes[i++] = create_sphere((t_sub_parser){.center = (t_vec3){-6., 5., 0.}, .color = BROWN_COLOR, .rad = 1.5, .specular = 10.});
	rt->shapes[i++] = create_sphere((t_sub_parser){.center = (t_vec3){6., 5., 0.}, .color = BROWN_COLOR, .rad = 1.5, .specular = 10.});
	rt->shapes[i++] = create_sphere((t_sub_parser){.center = (t_vec3){-6., -5., 18.}, .color = BROWN_COLOR, .rad = 1.5, .specular = 10.});
	rt->shapes[i++] = create_sphere((t_sub_parser){.center = (t_vec3){6., -5., 18.}, .color = BROWN_COLOR, .rad = 1.5, .specular = 10.});
	rt->shapes[i++] = create_sphere((t_sub_parser){.center = (t_vec3){-6., 5., 18.}, .color = BROWN_COLOR, .rad = 1.5, .specular = 10.});
	rt->shapes[i++] = create_sphere((t_sub_parser){.center = (t_vec3){6., 5., 18.}, .color = BROWN_COLOR, .rad = 1.5, .specular = 10.});
	rt->shapes[i++] = create_sphere((t_sub_parser){.center = (t_vec3){-2., 0., 0.}, .color = RED_COLOR, .rad = 1.5, .specular = 10.});
	rt->shapes[i++] = create_cilinder((t_sub_parser){.center = (t_vec3){6., 0., 18.}, .rad = 1., .axis = (t_vec3){0., 1., 0.}, .color = L_GREEN_COLOR, .specular = 10.});
	rt->shapes[i++] = create_cilinder((t_sub_parser){.center = (t_vec3){-6., 0., 18.}, .rad = 1., .axis = (t_vec3){0., 1., 0.}, .color = L_GREEN_COLOR, .specular = 10.});
	rt->shapes[i++] = create_cilinder((t_sub_parser){.center = (t_vec3){6., 0., 0.}, .rad = 1., .axis = (t_vec3){0., 1., 0.}, .color = L_GREEN_COLOR, .specular = 10.});
	rt->shapes[i++] = create_cilinder((t_sub_parser){.center = (t_vec3){-6., 0., 0.}, .rad = 1., .axis = (t_vec3){0., 1., 0.}, .color = L_GREEN_COLOR, .specular = 10.});
	rt->shapes[i++] = create_plane((t_sub_parser){.center = (t_vec3){0., 1., 29.}, .color = BLUE_COLOR, .norm = (t_vec3){0., 0., -1.}, .specular = 0});
	rt->shapes[i++] = create_plane((t_sub_parser){.center = (t_vec3){0., -5., 0.}, .color = PURPLE_COLOR, .norm = (t_vec3){0., 1., 0.}, .specular = 0});
	rt->shapes[i++] = create_plane((t_sub_parser){.center = (t_vec3){0., 5., 0.}, .color = YELLOW_COLOR, .norm = (t_vec3){0., -1., 0.}, .specular = 0});
	rt->shapes[i++] = create_cone((t_sub_parser){.center = (t_vec3){0., 0., 0.}, .angle = -1000, .axis = (t_vec3){0., 1., 0.}, .color = WHIGHT_COLOR, .specular = 10.});
	rt->max_light = 3;
	rt->light = ft_memalloc(sizeof(t_light) * rt->max_light);
	i = 0;
	rt->light[i++] = create_light_point((t_sub_parser){.opoint = (t_vec3){-20, 3, -20}, .intens = 0.4}, rt->max_light);
	rt->light[i++] = create_light_point((t_sub_parser){.opoint = (t_vec3){20, 3, -20}, .intens = 0.5}, rt->max_light);
	rt->light[i++] = create_light_ambient((t_sub_parser){.intens = 0.2}, rt->max_light);
	create_cam(rt, (t_sub_parser){.rot = (t_vec3){0, 0, 0}, .opoint = (t_vec3){0., 0., -20.}});
}
