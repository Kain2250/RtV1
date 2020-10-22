/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:30:14 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/22 04:26:36 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rt_free(t_rt *rt)
{
	SDL_FreeSurface(rt->sdl.screen);
	SDL_DestroyWindow(rt->sdl.window);
	free(rt);
}

void	init_cam(t_rt *rt)
{
	rt->sphere.center = (t_vec3){.x = 0, .y = 0, .z = 20};
	rt->sphere.color = (t_color){.red = 200, .green = 100, .blue = 50};
	rt->sphere.rad = 10.f;
	rt->sphere.type = SPHERE;

	rt->light = (t_vec3){.x = 500, .y = 200, .z = 0};
	
	rt->cam = (t_vec3){.x = 0., .y = 0., .z = 10.};
	rt->ray.z = 100;
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
		SDL_UpdateWindowSurface(rt->sdl.window);
		clear_surface(rt->sdl.screen, 0);
	}	
	rt_free(rt);
	return (0);
}