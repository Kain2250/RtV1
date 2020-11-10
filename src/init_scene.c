/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:10:40 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/10 17:57:19 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_shape		create_sphere(t_sub_parser data)
{
	t_shape	sphere;

	ft_bzero(&sphere, sizeof(t_shape));
	sphere.center = data.center;
	sphere.color = data.color;
	sphere.rad = clamp(data.rad, 0.1, INFINITY);
	sphere.specular = clamp(data.specular, 0, 10000);
	sphere.type = e_sphere;
	sphere.fil = 1;
	return (sphere);
}

t_shape		create_plane(t_sub_parser data)
{
	t_shape	plane;

	ft_bzero(&plane, sizeof(t_shape));
	plane.center = data.center;
	plane.color = data.color;
	plane.rad = INFINITY;
	plane.specular = clamp(data.specular, 0, 10000);
	plane.norm = normalize(data.norm);
	plane.type = e_plane;
	plane.fil = 1;
	return (plane);
}

t_shape		create_cone(t_sub_parser data)
{
	t_shape	cone;

	ft_bzero(&cone, sizeof(t_shape));
	cone.center = data.center;
	cone.axis = normalize(data.axis);
	cone.color = data.color;
	cone.k = tan(M_PI_2 / clamp(data.angle, 2, 100));
	cone.pow_k = cone.k * cone.k;
	cone.specular = clamp(data.specular, 0, 10000);
	cone.type = e_conus;
	cone.fil = 1;
	return (cone);
}

t_shape		create_cilinder(t_sub_parser data)
{
	t_shape	cil;

	ft_bzero(&cil, sizeof(t_shape));
	cil.center = data.center;
	cil.axis = normalize(data.axis);
	cil.color = data.color;
	cil.rad = clamp(data.rad, 0.1, INFINITY);
	cil.specular = clamp(data.specular, 0, 10000);
	cil.type = e_cilindr;
	cil.fil = 1;
	return (cil);
}
