/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:30:14 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/05 21:33:01 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_cam(t_rt *rt)
{
	int	i;

	i = 0;
	rt->max_shape = 17;
	rt->shapes = ft_memalloc(sizeof(t_shape) * rt->max_shape);
	// rt->shapes[i].center = (t_vec3){0., 0., 0.};
	// rt->shapes[i].color = (t_color){250, 77, 48};
	// rt->shapes[i].rad = 1.;
	// rt->shapes[i].specular = 50.;
	// rt->shapes[i++].type = e_sphere;
	// rt->shapes[i].center = (t_vec3){0., -5., 0.};
	// rt->shapes[i].color = (t_color){49, 127, 67};
	// rt->shapes[i].rad = INFINITY;
	// rt->shapes[i].specular = 0;
	// rt->shapes[i].norm = (t_vec3){0., 1., 0.};
	// rt->shapes[i++].type = e_plane;
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

t_vec3		rotate_cam(t_vec3 dir, double angle[3])
{
	double	x;
	double	y;

	if (angle[0] != 0)
		dir = (t_vec3){dir.x, dir.y * cos(angle[0]) + dir.z * sin(angle[0]),
			-dir.y * sin(angle[0]) + dir.z * cos(angle[0])};
	if (angle[1] != 0)
		dir = (t_vec3){dir.x * cos(angle[1]) + dir.z * sin(angle[1]), dir.y,
			-dir.x * sin(angle[1]) + dir.z * cos(angle[1])};
	if (angle[2] != 0)
	{
		x = dir.x;
		y = dir.y;
		dir = (t_vec3){x * cos(angle[2]) - y * sin(angle[2]), x * sin(angle[2])
			+ y * cos(angle[2]), dir.z};
	}
	return (dir);
}

t_vec3		basis_rotate(t_vec3 dir, t_vec3 x, t_vec3 y, t_vec3 z)
{
	t_vec3	i;
	t_vec3	j;
	t_vec3	k;
	t_vec3	ret;

	i = normalize(x);
	j = normalize(y);
	k = normalize(z);
	ret = addition3(addition3(cross_scalar(i, dir.x), cross_scalar(j, dir.y)),
		cross_scalar(k, dir.z));
	return (ret);
}

void		cache_cam(t_rt *rt)
{
	int		y;
	int		x;
	t_vec3	ray;

	ray.z = rt->cam.opoint.z + 1;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		ray.y = (WIN_HEIGHT * 0.5 - y) / WIN_HEIGHT;
		while (x < WIN_WIDTH)
		{
			ray.x = (x - (WIN_WIDTH * 0.5)) / WIN_HEIGHT;
			rt->cam.dir[y][x] = parallel_transfer3(ray, rt->cam.opoint);
			rt->cam.dir[y][x] = rotate_cam(rt->cam.dir[y][x], rt->rot);
			x++;
		}
		y++;
	}
}

int			main(void)
{
	t_rt	*rt;

	rt = ft_memalloc(sizeof(t_rt));
	init_lib_sdl(rt);
	init_cam(rt);
	cache_cam(rt);
	while (rt->quit != true)
	{
		shading(rt);
		event_list(rt);
		SDL_RenderPresent(rt->sdl.screen);
	}
	rt_free(rt);
	return (0);
}
