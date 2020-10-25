/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:30:14 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/25 20:53:11 by bdrinkin         ###   ########.fr       */
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

	rt->max_shape = 9;
	//Сфера
	rt->shapes = ft_memalloc(sizeof(t_shape) * rt->max_shape);
	rt->shapes[0].center = (t_vec3){-3., -3., 6.};
	rt->shapes[0].color = (t_color){255, 55, 100};
	rt->shapes[0].rad = 1.f;
	rt->shapes[0].specular = 200.;
	rt->shapes[0].type = e_sphere;

	rt->shapes[4].center = (t_vec3){-2., -2., 6.};
	rt->shapes[4].color = (t_color){255, 55, 100};
	rt->shapes[4].rad = 1.f;
	rt->shapes[4].specular = 200.;
	rt->shapes[4].type = e_sphere;

	rt->shapes[5].center = (t_vec3){-1., -1., 6.};
	rt->shapes[5].color = (t_color){255, 55, 100};
	rt->shapes[5].rad = 1.f;
	rt->shapes[5].specular = 200.;
	rt->shapes[5].type = e_sphere;

	rt->shapes[6].center = (t_vec3){-0., 0., 6.};
	rt->shapes[6].color = (t_color){255, 55, 100};
	rt->shapes[6].rad = 1.f;
	rt->shapes[6].specular = 200.;
	rt->shapes[6].type = e_sphere;

	rt->shapes[7].center = (t_vec3){1., 1., 6.};
	rt->shapes[7].color = (t_color){255, 55, 100};
	rt->shapes[7].rad = 1.f;
	rt->shapes[7].specular = 200.;
	rt->shapes[7].type = e_sphere;

	rt->shapes[8].center = (t_vec3){2., 2., 6.};
	rt->shapes[8].color = (t_color){255, 55, 100};
	rt->shapes[8].rad = 1.f;
	rt->shapes[8].specular = 200.;
	rt->shapes[8].type = e_sphere;


	//Плоскость
	rt->shapes[2].center = (t_vec3){0, 2, 0};
	rt->shapes[2].color = (t_color){255, 255, 255};
	rt->shapes[2].rad = 100;
	rt->shapes[2].specular = 0;
	rt->shapes[2].norm = (t_vec3){0, -1, 0};
	rt->shapes[2].type = e_plane;

	rt->shapes[3].center = (t_vec3){0, -2, 0};
	rt->shapes[3].color = (t_color){255, 255, 0};
	rt->shapes[3].rad = 100;
	rt->shapes[3].specular = 0;
	rt->shapes[3].norm = (t_vec3){0, 1, 0};
	rt->shapes[3].type = e_plane;

	//Цилиндр
	rt->shapes[1].center = (t_vec3){0., 0., 4.};
	rt->shapes[1].axis = (t_vec3){0., 1., 0.};
	rt->shapes[1].color = (t_color){25, 100, 5};
	rt->shapes[1].rad = 1.f;
	rt->shapes[1].specular = 0;
	rt->shapes[1].type = e_cilindr;
	
	rt->max_light = 3;
	rt->light = ft_memalloc(sizeof(t_light) * rt->max_light);
	//Направтеный свет
	rt->light[1].dir = (t_vec3){-0.5, -0.5, 0.5};
	rt->light[1].intens = 0.5;
	rt->light[1].on = true;
	rt->light[1].type = e_point;

	rt->light[2].dir = (t_vec3){0., -0.5, 0.5};
	rt->light[2].intens = 0.2;
	rt->light[2].on = true;
	rt->light[2].type = e_point;

	//Эмбиент
	rt->light[0].type = e_ambient;
	rt->light[0].intens = 0.08;
	rt->light[0].on = true;
	
	rt->cam.opoint = (t_vec3){0., 0., -2.};
	rt->cam.ray.z = 1;
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