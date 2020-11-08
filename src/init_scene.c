/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:10:40 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/08 18:03:54 by bdrinkin         ###   ########.fr       */
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
	plane.norm = norm;
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

t_light		create_light_point()
{
	
}

void		init_cam(t_rt *rt)
{
	int	i;

	i = 0;
	rt->max_shape = 17;
	rt->shapes = ft_memalloc(sizeof(t_shape) * rt->max_shape);
	rt->shapes[i].center = (t_vec3){-6., -5., 0.};
	rt->shapes[i].color = (t_color){0, 77, 48};
	rt->shapes[i].rad = 1.5;
	rt->shapes[i].specular = 10.;
	rt->shapes[i++].type = e_sphere;
	
	rt->shapes[i].center = (t_vec3){6., -5., 0.};
	rt->shapes[i].color = (t_color){144, 77, 48};
	rt->shapes[i].rad = 1.5;
	rt->shapes[i].specular = 10.;
	rt->shapes[i++].type = e_sphere;
	
	rt->shapes[i].center = (t_vec3){-6., 5., 0.};
	rt->shapes[i].color = (t_color){144, 77, 48};
	rt->shapes[i].rad = 1.5;
	rt->shapes[i].specular = 10.;
	rt->shapes[i++].type = e_sphere;
	
	rt->shapes[i].center = (t_vec3){6., 5., 0.};
	rt->shapes[i].color = (t_color){144, 77, 48};
	rt->shapes[i].rad = 1.5;
	rt->shapes[i].specular = 10.;
	rt->shapes[i++].type = e_sphere;
	
	rt->shapes[i].center = (t_vec3){-6., -5., 18.};
	rt->shapes[i].color = (t_color){144, 77, 48};
	rt->shapes[i].rad = 1.5;
	rt->shapes[i].specular = 10.;
	rt->shapes[i++].type = e_sphere;
	
	rt->shapes[i].center = (t_vec3){6., -5., 18.};
	rt->shapes[i].color = (t_color){144, 77, 48};
	rt->shapes[i].rad = 1.5;
	rt->shapes[i].specular = 10.;
	rt->shapes[i++].type = e_sphere;
	
	rt->shapes[i].center = (t_vec3){-6., 5., 18.};
	rt->shapes[i].color = (t_color){144, 77, 48};
	rt->shapes[i].rad = 1.5;
	rt->shapes[i].specular = 10.;
	rt->shapes[i++].type = e_sphere;
	
	rt->shapes[i].center = (t_vec3){6., 5., 18.};
	rt->shapes[i].color = (t_color){144, 77, 48};
	rt->shapes[i].rad = 2.;
	rt->shapes[i].specular = 10.;
	rt->shapes[i++].type = e_sphere;
	
	rt->shapes[i].center = (t_vec3){0., -3., 0.};
	rt->shapes[i].color = (t_color){255, 77, 48};
	rt->shapes[i].rad = 0.5;
	rt->shapes[i].specular = 10.;
	rt->shapes[i++].type = e_sphere;
	
	rt->shapes[i].center = (t_vec3){6., 0., 18.};
	rt->shapes[i].axis = normalize((t_vec3){0., 1., 0.});
	rt->shapes[i].color = (t_color){25, 100, 5}; 
	rt->shapes[i].rad = 1.f;
	rt->shapes[i].specular = 10.;
	rt->shapes[i++].type = e_cilindr;
	
	rt->shapes[i].center = (t_vec3){-6., 0., 18.};
	rt->shapes[i].axis = normalize((t_vec3){0., 1., 0.});
	rt->shapes[i].color = (t_color){25, 100, 5}; 
	rt->shapes[i].rad = 1.f;
	rt->shapes[i].specular = 10.;
	rt->shapes[i++].type = e_cilindr;
	
	rt->shapes[i].center = (t_vec3){6., 0., 0.};
	rt->shapes[i].axis = normalize((t_vec3){0., 1., 0.});
	rt->shapes[i].color = (t_color){25, 100, 5}; 
	rt->shapes[i].rad = 1.f;
	rt->shapes[i].specular = 10.;
	rt->shapes[i++].type = e_cilindr;
	
	rt->shapes[i].center = (t_vec3){-6., 0., 0.};
	rt->shapes[i].axis = normalize((t_vec3){0., 1., 0.});
	rt->shapes[i].color = (t_color){25, 100, 5}; 
	rt->shapes[i].rad = 1.f;
	rt->shapes[i].specular = 10.;
	rt->shapes[i++].type = e_cilindr;
	
	rt->shapes[i].center = (t_vec3){0., 1., 29.};
	rt->shapes[i].color = (t_color){49, 127, 67};
	rt->shapes[i].rad = INFINITY;
	rt->shapes[i].specular = 0;
	rt->shapes[i].norm = (t_vec3){0., 0., -1.};
	rt->shapes[i++].type = e_plane;
	
	rt->shapes[i].center = (t_vec3){0., -5., 0.};
	rt->shapes[i].color = (t_color){121, 85, 61};
	rt->shapes[i].rad = INFINITY;
	rt->shapes[i].specular = 0;
	rt->shapes[i].norm = (t_vec3){0., 1., 0.};
	rt->shapes[i++].type = e_plane;
	
	rt->shapes[i].center = (t_vec3){0., 5., 0.};
	rt->shapes[i].color = (t_color){204, 204, 255};
	rt->shapes[i].rad = INFINITY;
	rt->shapes[i].specular = 0;
	rt->shapes[i].norm = (t_vec3){0., -1., 0.};
	rt->shapes[i++].type = e_plane;
	
	rt->shapes[i].center = (t_vec3){0., 0., 0.};
	rt->shapes[i].axis = normalize((t_vec3){0., 1., 0.});
	rt->shapes[i].color = (t_color){0, 100, 150};
	rt->shapes[i].k = tan(M_PI_2 / 6);
	rt->shapes[i].pow_k = rt->shapes[i].k * rt->shapes[i].k;
	rt->shapes[i].specular = 0;
	rt->shapes[i++].type = e_conus;

	rt->max_light = 3;
	rt->light = ft_memalloc(sizeof(t_light) * rt->max_light);
	i = 0;
	rt->light[i].dir = (t_vec3){-20., 3., -20.};
	rt->light[i].intens = 0.4;
	rt->light[i].on = true;
	rt->light[i].type = e_point;
	rt->light[i++].max_light = rt->max_light;
	rt->light[i].dir = (t_vec3){20., 3, -20};
	rt->light[i].intens = 0.5;
	rt->light[i].on = true;
	rt->light[i].type = e_point;
	rt->light[i++].max_light = rt->max_light;
	rt->light[i].type = e_ambient;
	rt->light[i].intens = 0.2;
	rt->light[i].on = true;
	rt->light[i++].max_light = rt->max_light;
	rt->rot[0] = 0. * M_PI_180;
	rt->rot[1] = 0. * M_PI_180;
	rt->rot[2] = 0. * M_PI_180;
	rt->cam.opoint = (t_vec3){0., 0., -20.};
}
