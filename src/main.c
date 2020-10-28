/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:30:14 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/28 11:45:41 by kain2250         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rt_free(t_rt *rt)
{
	SDL_DestroyRenderer(rt->sdl.screen);
	SDL_DestroyWindow(rt->sdl.window);
	free(rt);
}

void	init_cam(t_rt *rt)
{
	rt->limit = (t_point){0, 1000};

	rt->max_shape = 8;
	//Сфера
	rt->shapes = ft_memalloc(sizeof(t_shape) * rt->max_shape);
	rt->shapes[0].center = (t_vec3){-3., 0., 0.};
	rt->shapes[0].color = (t_color){255, 55, 100};
	rt->shapes[0].rad = 1.f;
	rt->shapes[0].specular = 200.;
	rt->shapes[0].type = e_sphere;
	//Цилиндр
	rt->shapes[1].center = (t_vec3){3., 0., 6.};
	rt->shapes[1].axis = normalize((t_vec3){0.5, 0.5, 0.});
	rt->shapes[1].color = (t_color){25, 100, 5};
	rt->shapes[1].rad = 1.f;
	rt->shapes[1].specular = 0;
	rt->shapes[1].type = e_cilindr;
	//Плоскость
	rt->shapes[2].center = (t_vec3){0., 0., 9.};
	rt->shapes[2].color = (t_color){255, 255, 255};
	rt->shapes[2].rad = INFINITY;
	rt->shapes[2].specular = 0;
	rt->shapes[2].norm = (t_vec3){0., 0., -1.};
	rt->shapes[2].type = e_plane;
		//Плоскость
	rt->shapes[3].center = (t_vec3){0., -9., 0.};
	rt->shapes[3].color = (t_color){255, 255, 255};
	rt->shapes[3].rad = INFINITY;
	rt->shapes[3].specular = 0;
	rt->shapes[3].norm = (t_vec3){0., 1., 0.};
	rt->shapes[3].type = e_plane;
	//Плоскость
	rt->shapes[4].center = (t_vec3){0., 9., 0.};
	rt->shapes[4].color = (t_color){255, 255, 255};
	rt->shapes[4].rad = INFINITY;
	rt->shapes[4].specular = 0;
	rt->shapes[4].norm = (t_vec3){0., -1., 0.};
	rt->shapes[4].type = e_plane;
	//Плоскость
	rt->shapes[5].center = (t_vec3){-9, 0, 0};
	rt->shapes[5].color = (t_color){255, 255, 0};
	rt->shapes[5].rad = INFINITY;
	rt->shapes[5].specular = 0;
	rt->shapes[5].norm = (t_vec3){1, 0, 0};
	rt->shapes[5].type = e_plane;
	//Плоскость
	rt->shapes[6].center = (t_vec3){9, 0, 0};
	rt->shapes[6].color = (t_color){255, 255, 0};
	rt->shapes[6].rad = INFINITY;
	rt->shapes[6].specular = 0;
	rt->shapes[6].norm = (t_vec3){-1, 0, 0};
	rt->shapes[6].type = e_plane;
	//Конус
	rt->shapes[7].center = (t_vec3){0., 0., 0.};
	rt->shapes[7].axis = normalize((t_vec3){0., 1., 0.});
	rt->shapes[7].color = (t_color){0, 100, 150};
	rt->shapes[7].k = tan(M_PI / 4);
	rt->shapes[7].pow_k = rt->shapes[4].k * rt->shapes[4].k;
	rt->shapes[7].specular = 0;
	rt->shapes[7].type = e_conus;
	
	//Свет
	rt->max_light = 3;
	rt->light = ft_memalloc(sizeof(t_light) * rt->max_light);
	//Направленый свет
	rt->light[0].dir = (t_vec3){0.5, 0.5, 0.};
	rt->light[0].intens = 0.5;
	rt->light[0].on = true;
	rt->light[0].type = e_point;
	// Направленый свет
	rt->light[2].dir = (t_vec3){0., 0.5, -0.5};
	rt->light[2].intens = 0.2;
	rt->light[2].on = true;
	rt->light[2].type = e_point;
	//Эмбиент
	rt->light[1].type = e_ambient;
	rt->light[1].intens = 0.08;
	rt->light[1].on = true;
	
	rt->cam.opoint = (t_vec3){0., 0., -10.};
	t_vec3 ray;
	ray.z = rt->cam.opoint.z + 1;
	rt->x = 750;
	// rt->cam.ray.y = 0;
	
	rt->cam.dir = (t_vec3 **)ft_memalloc(sizeof(t_vec3 *) * rt->sdl.win_hight);
	int y = 0;
	while (y < rt->sdl.win_hight)
	{
		int x = 0;
		ray.y = (rt->sdl.win_hight * 0.5 - y) / rt->sdl.win_hight;
		rt->cam.dir[y] = (t_vec3 *)ft_memalloc(sizeof(t_vec3) * rt->sdl.win_width);
		while (x < rt->sdl.win_width)
		{
			ray.x = (x - (rt->sdl.win_width * 0.5)) / rt->sdl.win_hight;
			rt->cam.dir[y][x] = normalize(subtraction3(ray, rt->cam.opoint));
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
	while (rt->quit != true)
	{
		shading(rt);
		event_list(rt);
		SDL_RenderPresent(rt->sdl.screen);
		SDL_SetRenderDrawColor(rt->sdl.screen, 0, 0, 0, 0);
		SDL_RenderClear(rt->sdl.screen);
	}	
	rt_free(rt);
	return (0);
}