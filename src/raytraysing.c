/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytraysing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kain2250 <kain2250@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 02:02:27 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/23 02:41:56 by kain2250         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		shading(t_rt *rt)
{
	t_point	pixel;
	// t_vec3	dir;
	t_color	color;

	pixel.y = 0;
	while (pixel.y < WIN_HEIGHT)
	{
		rt->cam.ray.y = (WIN_HEIGHT * 0.5) - pixel.y;
		pixel.x = 0;
		while (pixel.x < WIN_WIDTH)
		{
			rt->cam.ray.x = pixel.x - (WIN_WIDTH * 0.5);
			rt->cam.dir = normalize(subtraction3(rt->cam.ray, rt->cam.opoint));
			color = trace_ray(rt->cam, (t_point){.x = 0, .y = 1000}, rt->sphere, rt->light);
			SDL_SetRenderDrawColor(rt->sdl.screen, color.red, color.green, color.blue, 0);
			SDL_RenderDrawPoint(rt->sdl.screen, pixel.x, pixel.y);
			// coleidoscope(rt, pixel, dir);
			// pixel_shader(rt, pixel, dir);
			pixel.x++;
		}
		pixel.y++;
	}
}