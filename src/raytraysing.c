/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytraysing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 02:02:27 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/26 16:14:17 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		shading(t_rt *rt)
{
	int		x;
	int		y;
	t_color	color;

	y = 0;
	while (y < rt->sdl.win_hight)
	{
		x = 0;
		while (x < rt->sdl.win_width)
		{
			color = trace_ray(rt->cam.dir[y][x], rt->cam.opoint, rt, rt->shapes, rt->light);
			SDL_SetRenderDrawColor(rt->sdl.screen, color.red, color.green, color.blue, 1);
			SDL_RenderDrawPoint(rt->sdl.screen, x, y);
			x++;
		}
		y++;
	}
}
