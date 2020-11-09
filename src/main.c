/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:30:14 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/10 00:23:51 by ecelsa           ###   ########.fr       */
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

t_vec3		rotate_cam(t_vec3 dir, t_vec3 angle)
{
	double	x;
	double	y;

	if (angle.x != 0)
		dir = (t_vec3){dir.x, dir.y * cos(angle.x) + dir.z * sin(angle.x),
			-dir.y * sin(angle.x) + dir.z * cos(angle.x)};
	if (angle.y != 0)
		dir = (t_vec3){dir.x * cos(angle.y) + dir.z * sin(angle.y), dir.y,
			-dir.x * sin(angle.y) + dir.z * cos(angle.y)};
	if (angle.z != 0)
	{
		x = dir.x;
		y = dir.y;
		dir = (t_vec3){x * cos(angle.z) - y * sin(angle.z), x * sin(angle.z)
			+ y * cos(angle.z), dir.z};
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

int			main(int argc, char **argv)
{
	t_rt	*rt;

	(void)argv;
	if (argc == 2)
	{
		rt = ft_memalloc(sizeof(t_rt));
		init_lib_sdl(rt);
		// init_cam(rt);
		parse_fail(argv[1], rt);
		cache_cam(rt);
		while (rt->quit != true)
		{
			shading(rt);
			event_list(rt);
			SDL_RenderPresent(rt->sdl.screen);
		}
		rt_free(rt);
	}
	return (0);
}
