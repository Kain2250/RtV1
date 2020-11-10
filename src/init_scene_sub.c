/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecelsa <ecelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:10:40 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/11/10 17:57:33 by ecelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light		create_light_point(t_sub_parser data, int max_light)
{
	t_light	light;

	ft_bzero(&light, sizeof(t_light));
	light.dir = data.opoint;
	light.intens = clamp(data.intens, 0, 1);
	light.on = data.on;
	light.type = e_point;
	light.max_light = max_light;
	light.fil = 1;
	return (light);
}

t_light		create_light_ambient(t_sub_parser data, int max_light)
{
	t_light	light;

	ft_bzero(&light, sizeof(t_light));
	light.type = e_ambient;
	light.intens = clamp(data.intens, 0, 1);
	light.on = data.on;
	light.max_light = max_light;
	light.fil = 1;
	return (light);
}

void		create_cam(t_rt *rt, t_sub_parser data)
{
	rt->rot.x = clamp(data.rot.x, 0, 360) * M_PI_180;
	rt->rot.y = clamp(data.rot.y, 0, 360) * M_PI_180;
	rt->rot.z = clamp(data.rot.z, 0, 360) * M_PI_180;
	rt->cam.opoint = data.opoint;
}
