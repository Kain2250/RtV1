/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:30:14 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/23 04:17:47 by kain2250         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <GL/gl.h>

void	rt_free(t_rt *rt)
{
	SDL_DestroyRenderer(rt->sdl.screen);
	SDL_DestroyWindow(rt->sdl.window);
	free(rt);
}

void	init_cam(t_rt *rt)
{
	rt->sphere = ft_memalloc(sizeof(t_sphere) * 2);
	rt->sphere[0].center = (t_vec3){.x = -1., .y = 0., .z = 4.};
	rt->sphere[0].color = (t_color){.red = 100, .green = 55, .blue = 100};
	rt->sphere[0].rad = 1.f;
	rt->sphere[0].type = e_sphere;

	rt->sphere[1].center = (t_vec3){.x = 1., .y = 0., .z = 4.};
	rt->sphere[1].color = (t_color){.red = 100, .green = 200, .blue = 50};
	rt->sphere[1].rad = 1.f;
	rt->sphere[1].type = e_sphere;


	rt->light = ft_memalloc(sizeof(t_light) * 2);
	rt->light[0].dir = (t_vec3){.x = 0., .y = 0., .z = 0.};
	rt->light[0].intens = 0.08;
	rt->light[0].type = e_point;

	rt->light[1].type = e_ambient;
	rt->light[1].intens = 0.2;
	
	rt->cam.opoint = (t_vec3){.x = 0., .y = 0., .z = 1.};
	rt->cam.ray.z = 400;
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