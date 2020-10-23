/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:30:14 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/23 22:38:08 by bdrinkin         ###   ########.fr       */
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

	rt->max_shape = 2;
	//Сфера
	rt->shapes = ft_memalloc(sizeof(t_shape) * rt->max_shape);
	rt->shapes[0].center = (t_vec3){0., 0., 6.};
	rt->shapes[0].color = (t_color){255, 55, 100};
	rt->shapes[0].rad = 1.f;
	rt->shapes[0].type = e_sphere;

	//Плоскость
	rt->shapes[1].center = (t_vec3){0, -7, 0};
	rt->shapes[1].color = (t_color){255, 255, 255};
	rt->shapes[1].rad = INFINITY;
	rt->shapes[1].norm = (t_vec3){0, 1, -0.9};
	rt->shapes[1].type = e_plane;
	//Цилиндр
	// rt->shapes[2].center = (t_vec3){2., 0., 6.};
	// rt->shapes[2].color = (t_color){25, 100, 5};
	// rt->shapes[2].rad = 2.f;
	// rt->shapes[2].type = e_cilindr;
	
	rt->max_light = 2;
	rt->light = ft_memalloc(sizeof(t_light) * rt->max_light);
	//Направтеный свет
	rt->light[0].dir = (t_vec3){-0.5, -0.5, 0.5};
	rt->light[0].intens = 0.5;
	rt->light[0].type = e_point;
	//Эмбиент
	rt->light[1].type = e_ambient;
	rt->light[1].intens = 0.08;
	
	rt->cam.opoint = (t_vec3){0., 0., -2.};
	rt->cam.ray.z = rt->cam.opoint.z + 1;
	rt->cam.ray.x = 0;
	rt->cam.ray.y = 0;

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