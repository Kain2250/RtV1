/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:30:14 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/30 20:16:46 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_cam(t_rt *rt)
{
	rt->limit = (t_point){0, 1000};
	int	i = 0;

	rt->max_shape = 5 + 11;
	//Сфера
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
	//Цилиндр
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
	//Плоскость
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
	// Конус
	// rt->shapes[i].center = (t_vec3){0., 0., 0.};
	// rt->shapes[i].axis = normalize((t_vec3){0., 1., 0.});
	// rt->shapes[i].color = (t_color){0, 100, 150};
	// rt->shapes[i].k = tan(M_PI_2 / 6);
	// rt->shapes[i].pow_k = rt->shapes[i].k * rt->shapes[i].k;
	// rt->shapes[i].specular = 0;
	// rt->shapes[i++].type = e_conus;
	
	//Свет
	rt->max_light = 3;
	rt->light = ft_memalloc(sizeof(t_light) * rt->max_light);
	//Направленый свет
	rt->light[0].dir = (t_vec3){-20., 3., -20.};
	rt->light[0].intens = 0.4;
	rt->light[0].on = true;
	rt->light[0].type = e_point;
	rt->light[0].max_light = rt->max_light;
	//Направленый свет
	rt->light[2].dir = (t_vec3){20., 3, -20};
	rt->light[2].intens = 0.5;
	rt->light[2].on = true;
	rt->light[2].type = e_point;
	rt->light[2].max_light = rt->max_light;
	//Эмбиент
	rt->light[1].type = e_ambient;
	rt->light[1].intens = 0.2;
	rt->light[1].on = true;
	rt->light[1].max_light = rt->max_light;
	rt->rot[0] = 0. * M_PI_180;
	rt->rot[1] = 0. * M_PI_180;
	rt->rot[2] = 0. * M_PI_180;
	rt->cam.opoint = (t_vec3){0., 0., -20.};
}

t_vec3	rotate_cam(t_vec3 dir, double angle[3])
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

void	cache_cam(t_rt *rt)
{
	int y;
	int x;
	t_vec3 ray;
	
	ray.z = rt->cam.opoint.z + 1;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		ray.y = (WIN_HEIGHT * 0.5 - y) / WIN_HEIGHT;
		while (x < WIN_WIDTH)
		{
			ray.x = (x - (WIN_WIDTH * 0.5)) / WIN_HEIGHT;
			rt->cam.dir[y][x] = normalize(subtraction3(ray, rt->cam.opoint));
			//Поворот базиса
			// t_vec3 i = normalize((t_vec3){0.99, 0., 0.16});
			// t_vec3 j = (t_vec3){0, 1, 0};
			// t_vec3 k = normalize((t_vec3){0.16, 0., -0.99});
			// rt->cam.dir[y][x] = addition3(addition3(cross_scalar(i, rt->cam.dir[y][x].x),
			// 	cross_scalar(j, rt->cam.dir[y][x].y)), cross_scalar(k, rt->cam.dir[y][x].z));
			rt->cam.dir[y][x] = rotate_cam(rt->cam.dir[y][x], rt->rot);
			x++;
		}
		y++;
	}
}

int		main(void)
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