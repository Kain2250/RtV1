/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:30:14 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/08 17:07:40 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		equal_min(double min[2], int i, t_intersect *param)
{
	if (min[1] < min[0])
	{
		param->iter = i;
		return (min[1]);
	}
	return (min[0]);
}

t_vec3		rotate_cam(t_vec3 dir, double angle[3])
{
	double	x;
	double	y;

	if (angle[0] != 0)
		dir = (t_vec3){dir.x, dir.y * cos(angle[0]) + dir.z * sin(angle[0]),
			-dir.y * sin(angle[0]) + dir.z * cos(angle[0])};
	if (angle[1] != 0)
		dir = (t_vec3){dir.x * cos(angle[1]) + dir.z * sin(angle[1]), dir.y,
			-dir.x * sin(angle[1]) + dir.z * cos(angle[1])};
	if (angle[2] != 0)
	{
		x = dir.x;
		y = dir.y;
		dir = (t_vec3){x * cos(angle[2]) - y * sin(angle[2]), x * sin(angle[2])
			+ y * cos(angle[2]), dir.z};
	}
	return (dir);
}

t_vec3		basis_rotate(t_vec3 dir, t_vec3 x, t_vec3 y, t_vec3 z)
{
	t_vec3	i;
	t_vec3	j;
	t_vec3	k;
	t_vec3	ret;

	i = normalize(x);
	j = normalize(y);
	k = normalize(z);
	ret = addition3(addition3(cross_scalar(i, dir.x), cross_scalar(j, dir.y)),
		cross_scalar(k, dir.z));
	return (ret);
}

void		cache_cam(t_rt *rt)
{
	int		y;
	int		x;
	t_vec3	ray;

	ray.z = rt->cam.opoint.z + 1;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		ray.y = (WIN_HEIGHT * 0.5 - y) / WIN_HEIGHT;
		while (x < WIN_WIDTH)
		{
			ray.x = (x - (WIN_WIDTH * 0.5)) / WIN_HEIGHT;
			rt->cam.dir[y][x] = parallel_transfer3(ray, rt->cam.opoint);
			rt->cam.dir[y][x] = rotate_cam(rt->cam.dir[y][x], rt->rot);
			x++;
		}
		y++;
	}
}

int			main(void)
{
	t_rt	*rt;

	rt = ft_memalloc(sizeof(t_rt));
	init_lib_sdl(rt);
	init_cam(rt);
	cache_cam(rt);
	while (rt->quit != true)
	{
		shading(rt);
		event_list(rt);
		SDL_RenderPresent(rt->sdl.screen);
	}
	rt_free(rt);
	return (0);
}
