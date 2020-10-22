/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytraysing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 02:02:27 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/22 04:43:27 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		shading(t_rt *rt)
{
	t_point	pixel;
	t_vec3	dir;

	pixel.y = 0;
	while (pixel.y < WIN_HEIGHT)
	{
		rt->ray.y = (WIN_HEIGHT * 0.5) - pixel.y;
		pixel.x = 0;
		while (pixel.x < WIN_WIDTH)
		{
			rt->ray.x = pixel.x - (WIN_WIDTH * 0.5);
			dir = normalize(subtraction3(rt->ray, rt->cam));
			pixel_shader(rt, pixel, dir);
			pixel.x++;
		}
		pixel.y++;
	}
}