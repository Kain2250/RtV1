/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytraysing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 02:02:27 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/25 20:43:51 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		shading(t_rt *rt)
{
	t_point	pixel;
	t_color	color;

	pixel.y = 0;
	while (pixel.y < rt->sdl.win_hight)
	{
		rt->cam.ray.y = (rt->sdl.win_hight * 0.5 - pixel.y) / rt->sdl.win_hight + rt->y;
		pixel.x = 0;
		while (pixel.x < rt->sdl.win_width)
		{
			rt->cam.ray.x = (pixel.x - (rt->sdl.win_width * 0.5)) / rt->sdl.win_hight + rt->x;
			rt->cam.dir = normalize(subtraction3(rt->cam.ray, rt->cam.opoint));
			color = trace_ray(rt->cam, rt, rt->shapes, rt->light);
			SDL_SetRenderDrawColor(rt->sdl.screen, color.red, color.green, color.blue, 1);
			SDL_RenderDrawPoint(rt->sdl.screen, pixel.x, pixel.y);
			pixel.x++;
		}
		pixel.y++;
	}
}
