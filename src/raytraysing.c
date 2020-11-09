/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytraysing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 02:02:27 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/05 18:03:52 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3		surface_norm(t_intersect param, t_shape shape,
				t_vec3 opoint, t_vec3 dir)
{
	t_vec3	norm;
	double	m;

	norm = shape.norm;
	if (shape.type == e_cilindr || shape.type == e_conus)
		m = dot3(dir, shape.axis) * param.point +
		dot3(subtraction3(opoint, shape.center), shape.axis);
	if (shape.type == e_sphere)
		norm = parallel_transfer3(param.intersect, shape.center);
	else if (shape.type == e_cilindr)
		norm = parallel_transfer3(subtraction3(param.intersect,
			shape.center), cross_scalar(shape.axis, m));
	else if (shape.type == e_conus)
		norm = parallel_transfer3(subtraction3(param.intersect,
			shape.center), cross_scalar(shape.axis, m * (1 + shape.pow_k)));
	return (norm);
}

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
			color = pixel_shader(rt->cam.dir[y][x], rt->cam.opoint, rt);
			SDL_SetRenderDrawColor(rt->sdl.screen, color.red,
				color.green, color.blue, 1);
			SDL_RenderDrawPoint(rt->sdl.screen, x, y);
			x++;
		}
		y++;
	}
}
